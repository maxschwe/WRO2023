#include "../../include/robot/linefollow.h"
#include "../../include/config.h"

float linefollow_get_kp(int speed)
{
    if (speed <= 10) {
        return 0.3;
    } else if (speed <= 25) {
        return 0.3;
    } else if (speed <= 50) {
        return 0.2;
    } else if (speed <= 75) {
        return 0.25;
    } else {
        return 0.35;
    }
}

float linefollow_get_kd(int speed)
{
    if (speed <= 10) {
        return 20;
    } else if (speed <= 25) {
        return 20;
    } else if (speed <= 50) {
        return 10;
    } else if (speed <= 75) {
        return 10;
    } else {
        return 15;
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

void linefollow_intersection(int speed, bool brake)
{
    float kp = linefollow_get_kp(speed);
    float kd = linefollow_get_kd(speed);
    int initial_b = m_get_deg(b);
    while (col_get_ref(s1) > 15 || abs(m_get_deg(b) - initial_b) < 100) {
    // while (col_get_ref(s2) + col_get_ref(s3) > 90 || abs(m_get_deg(b) - initial_b) < 100) {
        on(speed, linefollow_control(kp, kd));
    }
    current_speed = speed;
    if (brake) {
        linefollow_deg(30, 100, true);
        current_speed = 0;
    }
}

void linefollow_intersection_custom(int speed, float kp, float kd, bool brake)
{
    int initial_b = m_get_deg(b);
    
    while (col_get_ref(s2) + col_get_ref(s3) > 30 || abs(m_get_deg(b) - initial_b) < 100) {
        on(speed, linefollow_control(kp, kd));
    }
    current_speed = speed;
    if (brake) {
        linefollow_deg(30, 100, true);
        current_speed = 0;
    }
}

void linefollow_deg(int speed, int deg, bool brake)
{
    float kp = linefollow_get_kp(speed);
    float kd = linefollow_get_kd(speed);
    int initial_b = m_get_deg(b);
    while (abs(m_get_deg(b) - initial_b) < deg) {
        on(speed, linefollow_control(kp, kd));
        tslp_tsk(1);
    }
    current_speed = speed;
    if (brake) {
        off(true);
        current_speed = 0;
    }
}

void linefollow_smooth(int end_speed, int deg, bool brake)
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
    init_smooth_speed(start_speed, end_speed, MAX_SPEED_LINEFOLLOW, LINEFOLLOW_ACC, LINEFOLLOW_DEACC, deg);

    int initial_b = m_get_deg(b);
    int taken_deg;
    long counter = 0;
    while ((taken_deg = abs(m_get_deg(b) - initial_b)) < deg) {
        current_speed = get_smooth_speed(taken_deg);
        // display_set_spot(2, "sp", current_speed);
        float kp = linefollow_get_kp(current_speed);
        float kd = linefollow_get_kd(current_speed);
        float current_steering = linefollow_control(kp, kd);
        on(current_speed, current_steering);
        ++counter;
    }
    current_speed = end_speed;
    if (brake) {
        off(true);
        current_speed = 0;
    }
}

void linefollow_deg_custom(int speed, int deg, float kp, float kd, bool brake)
{
    int initial_b = m_get_deg(b);
    while (abs(m_get_deg(b) - initial_b) < deg) {
        on(speed, linefollow_control(kp, kd));
    }
    current_speed = speed;
    if (brake) {
        off(true);
        current_speed = 0;
    }
}

void linefollow_col_1(int speed, int ref_light_s1, bool brake)
{
    float kp = linefollow_get_kp(speed);
    float kd = linefollow_get_kd(speed);
    while (col_get_ref(s1) < ref_light_s1) {
        on(speed, linefollow_control(kp, kd));
    }
    current_speed = speed;
    if (brake) {
        off(true);
        current_speed = 0;
    }
}

void linefollow_col_1_greater(int speed, int ref_light_s1, bool brake)
{
    float kp = linefollow_get_kp(speed);
    float kd = linefollow_get_kd(speed);
    while (col_get_ref(s1) > ref_light_s1) {
        on(speed, linefollow_control(kp, kd));
    }
    current_speed = speed;
    if (brake) {
        off(true);
        current_speed = 0;
    }
}