#include "lib/robot/drive.h"

int current_speed = 0;

void on(int speed, int steering)
{
    int speed_b, speed_c;
    if (steering > 0) {
        speed_b = speed;
        speed_c = speed * (1 - steering / 50.0);
    } else {
        speed_b = speed * (1 + steering / 50.0);
        speed_c = speed;
    }
    m_on(c, speed_c);
    m_on(b, speed_b);
    current_speed = speed;
}

void off()
{
    m_off(b, true);
    m_off(c, true);
    current_speed = 0;
}

void wait_stand()
{
    while (m_get_speed(b) != 0 || m_get_speed(c) != 0) {
    }
    wait(0.1);
}

void drive_smooth_custom(int start_speed, int end_speed, int max_speed_limit, int steering, int deg, float drive_acc_factor, float drive_deacc_factor, bool brake, bool scan, bool new_steering)
{
    int start_deg_b = m_get_deg(b);
    int start_deg_c = m_get_deg(c);
    int current_deg_b = start_deg_b;
    int current_deg_c = start_deg_c;

    bool is_b_main = steering > 0;

    deg = abs(deg);
    if (steering == 0) {
        steering = STEERING_CORRECTION;
    }
    init_smooth_speed_controller(start_speed, end_speed, abs(max_speed_limit), drive_acc_factor, drive_deacc_factor, deg);
    init_steering_controller(steering, deg, start_deg_b, start_deg_c, is_b_main);
    m_reset_stall(b);
    m_reset_stall(c);

    int speed, current_steering;
    int loop_count = 0;

    while (abs(current_deg_b - start_deg_b) < deg && abs(current_deg_c - start_deg_c) < deg) {
        speed = get_smooth_speed(is_b_main ? current_deg_b - start_deg_b : current_deg_c - start_deg_c);
        if (new_steering) {
            get_steering(current_deg_b, current_deg_c, &speed, &current_steering);
        } else {
            get_steering_old(current_deg_b, current_deg_c, &speed, &current_steering);
        }

        on(speed, current_steering);

        // check if stall : needs to be saved in seperate vars so there is no lazy evaluation
        bool b_stalled = m_check_stall(b);
        bool c_stalled = m_check_stall(c);
        if (b_stalled && c_stalled) {
            error_beep();
            break;
        }

        // scan if wanted and only when currently not stalled
        if (scan && !b.stall_detection->is_currently_stalled && !c.stall_detection->is_currently_stalled) {
            complex_scan();
        }
        current_deg_b = m_get_deg(b);
        current_deg_c = m_get_deg(c);
        loop_count++;

#if DRIVE_SMOOTH_PRINT_DEBUG
        display_set_spot(2, "b-s", start_deg_b);
        display_set_spot(3, "c-s", start_deg_c);
        display_set_spot(4, "b-c", current_deg_b);
        display_set_spot(5, "c-c", current_deg_c);

        display_set_spot(6, "sp", speed);
        display_set_spot(7, "st", current_steering);
        display_set_spot(8, "", loop_count);
#endif
    }
    if (brake) {
        off();
    } else {
        on(speed, steering);
    }
}

void drive_smooth(int end_speed, int steering, int deg, bool brake)
{
    int start_speed;
    if (abs(current_speed) < DRIVE_START_SPEED) {
        if (end_speed >= 0) {
            start_speed = DRIVE_START_SPEED;
        } else {
            start_speed = -DRIVE_START_SPEED;
        }
    } else {
        start_speed = current_speed;
    }
    drive_smooth_custom(start_speed, end_speed, DRIVE_MAX_SPEED, steering, deg, DRIVE_ACC_FACTOR, DRIVE_DEACC_FACTOR, brake, false, true);
}

void drive_deg(int speed, int steering, int deg, bool brake)
{
    drive_smooth_custom(speed, speed, abs(speed), steering, deg, DRIVE_ACC_FACTOR, DRIVE_DEACC_FACTOR, brake, false, true);
}

void drive_col(int speed, int steering, ColorSensor sensor, int compare_value, bool check_lower, bool brake)
{
    drive_col_custom(speed, steering, sensor, compare_value, check_lower, brake, false);
}

void drive_col_custom(int speed, int steering, ColorSensor sensor, int compare_value, bool check_lower, bool brake, bool scan)
{
    // TODO: with steering control
    m_reset_stall(b);
    m_reset_stall(c);
    on(speed, steering);
    while (!col_check_ref(sensor, compare_value, check_lower)) {
        if (scan) {
            complex_scan();
        }
        // // check if stall: needs to be saved in seperate vars so there is no lazy evaluation
        // STALL_DETECTION_TIMEOUT must be increased to work for this
        // bool b_stalled = m_check_stall(b);
        // bool c_stalled = m_check_stall(c);
        // if (b_stalled && c_stalled) {
        //     error_beep();
        //     break;
        // }
    }
    if (brake) {
        off();
    } else {
        on(speed, steering);
    }
}

void drive_time(int speed, int steering, float seconds, bool brake)
{
    on(speed, steering);
    wait(seconds);
    if (brake) {
        off();
    } else {
        on(speed, steering);
    }
}

void turn_line(bool turn_left, bool brake)
{
    int steering = turn_left ? -100 : 100;
    ColorSensor sensor = turn_left ? s2 : s3;
    drive_smooth_custom(10, 30, 40, steering, 100, TURN_ACC_FACTOR, TURN_DEACC_FACTOR, false, false, false);
    drive_col(30, steering, sensor, COL_WHITE_REF, false, false);
    drive_smooth_custom(30, 30, 40, steering, 30, TURN_ACC_FACTOR, TURN_DEACC_FACTOR, false, false, false);
    drive_col(30, steering, sensor, COL_BLACK_REF, true, false);
    drive_smooth_custom(30, 10, 50, steering, 95, TURN_ACC_FACTOR, TURN_DEACC_FACTOR, true, false, false);
}

void turn_90(bool turn_left)
{
    wait_stand();
    int steering = turn_left ? -100 : 100;
    drive_smooth_custom(TURN_START_SPEED, TURN_END_SPEED, TURN_MAX_SPEED, steering, TURN_90_DEG, TURN_ACC_FACTOR, TURN_DEACC_FACTOR, true, false, false);
}

void turn_180(bool turn_left)
{
    wait_stand();
    int steering = turn_left ? -100 : 100;
    drive_smooth_custom(TURN_START_SPEED, TURN_END_SPEED, TURN_MAX_SPEED, steering, TURN_180_DEG, TURN_ACC_FACTOR, TURN_DEACC_FACTOR, true, false, false);
}

void turnsing_90(bool turn_left, bool drive_forward)
{
    wait_stand();
    int steering = turn_left ? -50 : 50;
    int start_speed = TURNSING_START_SPEED;
    int end_speed = TURNSING_END_SPEED;
    if (!drive_forward) {
        start_speed = -start_speed;
        end_speed = -end_speed;
        steering = -steering;
    }
    drive_smooth_custom(start_speed, end_speed, TURNSING_MAX_SPEED, steering, TURNSING_90_DEG, TURNSING_ACC_FACTOR, TURNSING_DEACC_FACTOR, true, false, false);
}

void turnsing_180(bool turn_left, bool drive_forward)
{
    wait_stand();
    int steering = turn_left ? -50 : 50;
    int start_speed = TURNSING_START_SPEED;
    int end_speed = TURNSING_END_SPEED;
    if (!drive_forward) {
        start_speed = -start_speed;
        end_speed = -end_speed;
        steering = -steering;
    }
    drive_smooth_custom(start_speed, end_speed, TURNSING_MAX_SPEED, steering, TURNSING_180_DEG, TURNSING_ACC_FACTOR, TURNSING_DEACC_FACTOR, true, false, false);
}

void drive_line(int speed, bool brake) {
    drive_col(speed, 0, s2, COL_WHITE_REF, false, false);
    drive_deg(speed, 0, 30, false);
    drive_col(speed, 0, s2, COL_BLACK_REF, true, true);
    drive_smooth(10, 0, 120, brake);
}
