#include "lib/robot/linefollow.h"

float linefollow_get_kp(int speed)
{
    if (speed <= 10) {
        return KP_10;
    } else if (speed <= 25) {
        return KP_25;
    } else if (speed <= 50) {
        return KP_50;
    } else if (speed <= 75) {
        return KP_75;
    } else {
        return KP_100;
    }
}

float linefollow_get_kd(int speed)
{
    if (speed <= 10) {
        return KD_10;
    } else if (speed <= 25) {
        return KD_25;
    } else if (speed <= 50) {
        return KD_50;
    } else if (speed <= 75) {
        return KD_75;
    } else {
        return KD_100;
    }
}

float linefollow_control(float kp, float kd)
{
    static int last_error = 0;
    int error = col_get_ref(s2) - col_get_ref(s3);
    float pid_value = error * kp + (error - last_error) * kd;
    if (pid_value >= 0) {
        pid_value = MIN(100, pid_value);
    } else {
        pid_value = MAX(-100, pid_value);
    }
    last_error = error;
    display_set_spot(11, "St", pid_value);
    return pid_value;
}

void linefollow_intersection_custom(int speed, float kp, float kd, bool brake)
{
    int initial_b = m_get_deg(b);

    while (col_get_ref(s2) + col_get_ref(s3) > LINEFOLLOW_INTERSECTION_VALUE || abs(m_get_deg(b) - initial_b) < LINEFOLLOW_INTERSECTION_INITIAL_DEG) {
        on(speed, linefollow_control(kp, kd));
    }
    if (brake) {
        linefollow_deg(30, 100, true);
    }
}

void linefollow_intersection(int speed, bool brake)
{
    float kp = linefollow_get_kp(speed);
    float kd = linefollow_get_kd(speed);
    linefollow_intersection_custom(speed, kp, kd, brake);
}

void linefollow_smooth_custom(int start_speed, int end_speed, int max_speed, int deg, bool brake)
{
    int speed;
    init_smooth_speed_controller(start_speed, end_speed, max_speed, LINEFOLLOW_ACC, LINEFOLLOW_DEACC, deg);

    int initial_b = m_get_deg(b);
    int taken_deg;
    long counter = 0;
    while ((taken_deg = abs(m_get_deg(b) - initial_b)) < deg) {
        speed = get_smooth_speed(taken_deg);
        // display_set_spot(2, "sp", speed);
        float kp = linefollow_get_kp(speed);
        float kd = linefollow_get_kd(speed);
        float steering = linefollow_control(kp, kd);
        on(speed, steering);
        ++counter;
    }
    if (brake) {
        off();
    }
}

void linefollow_smooth(int end_speed, int deg, bool brake) {
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
    linefollow_smooth_custom(start_speed, end_speed, LINEFOLLOW_MAX_SPEED, deg, brake);
}


void linefollow_deg_custom(int speed, int deg, float kp, float kd, bool brake)
{
    int initial_b = m_get_deg(b);
    while (abs(m_get_deg(b) - initial_b) < deg) {
        on(speed, linefollow_control(kp, kd));
    }
    if (brake) {
        off();
    }
}

void linefollow_deg(int speed, int deg, bool brake)
{
    float kp = linefollow_get_kp(speed);
    float kd = linefollow_get_kd(speed);
    linefollow_deg_custom(speed, deg, kp, kd, brake);
}

void linefollow_col_1(int speed, int ref_light_s1, bool lower, bool brake)
{
    float kp = linefollow_get_kp(speed);
    float kd = linefollow_get_kd(speed);
    while (col_check_ref(s1, ref_light_s1, lower)) {
        on(speed, linefollow_control(kp, kd));
    }
    if (brake) {
        off();
    }
}
