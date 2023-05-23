#include "../../include/robot/drive.h"
#include "../../include/config.h"

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

void off(bool brake)
{
    if (brake) {
        m_off(b, true);
        m_off(c, true);
    }
    current_speed = 0;
}

void init_smooth_speed(int start_speed, int end_speed, int max_speed_limit, int deg)
{
    deg = abs(deg);
    if (end_speed < 0) {
        deg = -deg;
    }
    // throw error: changing drive direction not supported
    if (start_speed >= 0 != end_speed >= 0) {
        error_beep();
        exit(1);
        return;
    }
    // calc max speed (with using limit)
    smooth_current_max_speed = (deg + current_speed * ACC_FACTOR + end_speed * DEACC_FACTOR) / (ACC_FACTOR + DEACC_FACTOR);
    if (end_speed >= 0) {
        smooth_current_max_speed = MIN(smooth_current_max_speed, max_speed_limit);
    } else {
        smooth_current_max_speed = MAX(smooth_current_max_speed, -max_speed_limit);
    }

    smooth_deg_acc_end = ACC_FACTOR * (smooth_current_max_speed - current_speed);
    smooth_deg_deacc_start = deg - DEACC_FACTOR * (smooth_current_max_speed - end_speed);
    smooth_start_speed = start_speed;
}

int get_smooth_speed(int deg)
{
    int cur_speed;
    if (abs(deg) < abs(smooth_deg_acc_end)) {
        cur_speed = deg / ACC_FACTOR + smooth_start_speed;
    } else if (abs(deg) < abs(smooth_deg_deacc_start)) {
        cur_speed = smooth_current_max_speed;
    } else {
        cur_speed = -(deg - smooth_deg_deacc_start) / DEACC_FACTOR + smooth_current_max_speed;
    }
    return cur_speed;
}

void drive_col(int speed, int steering, ColorSensor sensor, char col, bool brake)
{
    on(speed, steering);
    col_wait_ref(sensor, col);
    current_speed = speed;
    if (brake) {
        off(brake);
        current_speed = 0;
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
    drive_smooth_custom(start_speed, end_speed, MAX_SPEED_LIMIT, steering, deg, brake, NULL);
}

void drive_smooth_custom(int start_speed, int end_speed, int max_speed_limit, int steering, int deg, bool brake, float_array* data)
{
    init_smooth_speed(start_speed, end_speed, max_speed_limit, deg);
    int current_deg_b, current_deg_c, target_deg_b, target_deg_c;
    float current_steering;
    int taken_deg_b = 0;
    int taken_deg_c = 0;
    int b_left_deg, c_left_deg;
    int start_deg_b = m_get_deg(b);
    int start_deg_c = m_get_deg(c);
    int loop_count = 0;
    current_deg_b = start_deg_b;
    current_deg_c = start_deg_c;
    deg = abs(deg);
    bool is_b_used;
    bool is_b_main;
    if (steering > 0) {
        target_deg_b = deg;
        target_deg_c = deg * (1 - steering / 50.0);
        is_b_used = true;
    } else {
        target_deg_b = deg * (1 + steering / 50.0);
        target_deg_c = deg;
        is_b_used = false;
    }
    deg = abs(deg);
    while (taken_deg_b < deg && taken_deg_c < deg) {
        b_left_deg = target_deg_b - current_deg_b + start_deg_b;
        c_left_deg = target_deg_c - current_deg_c + start_deg_c;
        current_speed = get_smooth_speed(is_b_used ? current_deg_b - start_deg_b : current_deg_c - start_deg_c);

        float zaehler = b_left_deg - c_left_deg;
        int abs_b_left = abs(b_left_deg);
        int abs_c_left = abs(c_left_deg);
        float nenner = MAX(abs_b_left, abs_c_left);
        current_steering = (zaehler / nenner) * 50.0;
        is_b_main = abs_b_left > abs_c_left;
        if ((is_b_main ? b_left_deg : c_left_deg) < 0) {
            current_speed = -current_speed;
            current_steering = -current_steering;
        }

        on(current_speed, current_steering);
        current_deg_b = m_get_deg(b);
        current_deg_c = m_get_deg(c);
        taken_deg_b = abs(current_deg_b - start_deg_b);
        taken_deg_c = abs(current_deg_c - start_deg_c);
        loop_count++;
        if (data != NULL) {
            // append_array(data, col_get_rel_rgb(s4, 'b'));
            wait(0.0001);
        }
    }
    if (brake) {
        off(brake);
    } else {
        on(current_speed, steering);
    }

    if (PRINT_DRIVE_DEBUG) {
        display_set_spot(2, "b-c", current_deg_b);
        display_set_spot(3, "c-c", current_deg_c);
        display_set_spot(4, "b-l", b_left_deg);
        display_set_spot(5, "c-l", c_left_deg);
        display_set_spot(6, "sp", current_speed);
        display_set_spot(7, "st", current_steering);
        display_set_spot(8, "", loop_count);
    }
}

void drive_deg(int speed, int target_speed, int steering, int deg, bool brake)
{
    int current_deg_b, current_deg_c, target_deg_b, target_deg_c;
    float current_steering;
    int taken_deg_b = 0;
    int taken_deg_c = 0;
    int b_left_deg, c_left_deg;
    int start_deg_b = m_get_deg(b);
    int start_deg_c = m_get_deg(c);
    int speed_diff = target_speed - speed;
    int loop_count = 0;
    current_deg_b = start_deg_b;
    current_deg_c = start_deg_c;
    deg = abs(deg);
    bool is_b_used;
    bool is_b_main;
    if (speed < 0) {
        deg = -deg;
        speed = -speed;
        speed_diff = -speed_diff;
    }
    if (steering > 0) {
        target_deg_b = deg;
        target_deg_c = deg * (1 - steering / 50.0);
        is_b_used = true;
    } else {
        target_deg_b = deg * (1 + steering / 50.0);
        target_deg_c = deg;
        is_b_used = false;
    }
    deg = abs(deg);
    if (PRINT_DRIVE_DEBUG) {
        display_set_spot(0, "b-t", target_deg_b);
        display_set_spot(1, "c-t", target_deg_c);
    }
    while (taken_deg_b < deg && taken_deg_c < deg) {
        b_left_deg = target_deg_b - current_deg_b + start_deg_b;
        c_left_deg = target_deg_c - current_deg_c + start_deg_c;
        // TODO: make speed curve x^3, not linear
        current_speed = (1.0 * abs(is_b_used ? taken_deg_b : taken_deg_c) / deg) * speed_diff + speed;
        float zaehler = b_left_deg - c_left_deg;
        int abs_b_left = abs(b_left_deg);
        int abs_c_left = abs(c_left_deg);
        float nenner = MAX(abs_b_left, abs_c_left);
        current_steering = (zaehler / nenner) * 50.0;
        is_b_main = abs_b_left > abs_c_left;
        if ((is_b_main ? b_left_deg : c_left_deg) < 0) {
            current_speed = -current_speed;
            current_steering = -current_steering;
        }

        on(current_speed, current_steering);
        current_deg_b = m_get_deg(b);
        current_deg_c = m_get_deg(c);
        taken_deg_b = abs(current_deg_b - start_deg_b);
        taken_deg_c = abs(current_deg_c - start_deg_c);
        loop_count++;
    }
    current_speed = target_speed;
    if (brake) {
        off(brake);
        current_speed = 0;
    }

    if (PRINT_DRIVE_DEBUG) {
        display_set_spot(2, "b-c", current_deg_b);
        display_set_spot(3, "c-c", current_deg_c);
        display_set_spot(4, "b-l", b_left_deg);
        display_set_spot(5, "c-l", c_left_deg);
        display_set_spot(6, "sp", current_speed);
        display_set_spot(7, "st", current_steering);
        display_set_spot(8, "", loop_count);
    }
}

void turn_line(bool turn_left, bool brake)
{
    int steering = turn_left ? -100 : 100;
    ColorSensor sensor = turn_left ? s2 : s3;
    drive_smooth(30, steering, 100, false);
    drive_col(30, steering, sensor, WHITE, false);
    drive_smooth(30, steering, 30, false);
    drive_col(30, steering, sensor, BLACK, false);
    drive_smooth(10, steering, 75, true);
}

void turn_90(bool turn_left, bool brake)
{
    int steering = turn_left ? -100 : 100;
    drive_smooth(10, steering, 312, true);
}
