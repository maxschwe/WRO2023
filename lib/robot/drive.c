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
    m_on(b, speed_b);
    m_on(c, speed_c);
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

void drive_smooth_custom(int start_speed, int end_speed, int max_speed_limit, int steering, int deg, bool brake, bool scan)
{
    int start_deg_b = m_get_deg(b);
    int start_deg_c = m_get_deg(c);
    int current_deg_b = start_deg_b;
    int current_deg_c = start_deg_c;

    deg = abs(deg);
    init_smooth_speed_controller(start_speed, end_speed, max_speed_limit, DRIVE_ACC_FACTOR, DRIVE_DEACC_FACTOR, deg);
    init_steering_controller(steering, deg, start_deg_b, start_deg_c);
    m_reset_stall(b);
    m_reset_stall(c);

    int speed, current_steering;
    int loop_count = 0;
    bool is_b_used_for_speed_control = steering > 0;

    while (abs(current_deg_b - start_deg_b) < deg && abs(current_deg_c - start_deg_c) < deg) {
        speed = get_smooth_speed(is_b_used_for_speed_control ? current_deg_b - start_deg_b : current_deg_c - start_deg_c);
        get_steering(current_deg_b, current_deg_c, &speed, &current_steering);

        on(speed, current_steering);
        current_deg_b = m_get_deg(b);
        current_deg_c = m_get_deg(c);
        loop_count++;

        // scan if wanted
        if (scan) {
            complex_scan();
        }

        // check if stall
        if (m_check_stall(b) && m_check_stall(c)) {
            error_beep();
            break;
        }

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
    drive_smooth_custom(start_speed, end_speed, DRIVE_MAX_SPEED, steering, deg, brake, false);
}

void drive_deg(int speed, int steering, int deg, bool brake)
{
    drive_smooth_custom(speed, speed, speed, steering, deg, brake, false);
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
            // display_set_spot(11, "val", 0.0);
        }
        // check if stall
        if (m_check_stall(b) && m_check_stall(c)) {
            error_beep();
            break;
        }
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
    drive_smooth(30, steering, 100, false);
    drive_col(30, steering, sensor, COL_WHITE_REF, false, false);
    drive_smooth(30, steering, 30, false);
    drive_col(30, steering, sensor, COL_BLACK_REF, true, false);
    drive_smooth(10, steering, 75, true);
}

void turn_90(bool turn_left)
{
    wait_stand();
    int steering = turn_left ? -100 : 100;
    drive_smooth(10, steering, TURN_90_DEG, true);
}

void turn_180(bool turn_left)
{
    wait_stand();
    int steering = turn_left ? -100 : 100;
    drive_smooth(10, steering, TURN_180_DEG, true);
}

void turnsing_90(bool turn_left, bool drive_forward)
{
    wait_stand();
    int steering = turn_left ? -50 : 50;
    drive_smooth(15, steering, TURNSING_90_DEG, true);
}

void turnsing_180(bool turn_left, bool drive_forward)
{
    wait_stand();
    int steering = turn_left ? -50 : 50;
    drive_smooth(15, steering, TURNSING_180_DEG, true);
}
