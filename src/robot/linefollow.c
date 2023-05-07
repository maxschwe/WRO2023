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
        return 40;
    } else if (speed <= 25) {
        return 40;
    } else if (speed <= 50) {
        return 60;
    } else if (speed <= 75) {
        return 80;
    } else {
        return 75;
    }
}

float linefollow_control(float kp, float kd)
{
    static int last_error = 0;
    int error = col_get_ref(s2) - col_get_ref(s3);
    float pid_value = error * kp + (error - last_error) * kd;
    last_error = error;
    return pid_value;
}

void linefollow_intersection(int speed, bool brake)
{
    float kp = linefollow_get_kp(speed);
    float kd = linefollow_get_kd(speed);
    int initial_b = m_get_deg(b);
    while (col_get_ref(s2) + col_get_ref(s3) > 30 || abs(m_get_deg(b) - initial_b) < 100) {
        on(speed, linefollow_control(kp, kd));
    }
    current_speed = speed;
    if (brake) {
        linefollow_deg(30, 90, true);
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
        linefollow_deg(30, 90, true);
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
    }
    current_speed = speed;
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