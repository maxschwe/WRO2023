#include "../../include/robot/linefollow.h"
#include "../../include/config.h"

float linefollow_control(float kp, float kd)
{
    static int last_error = 0;
    int error = col_get_ref(s2) - col_get_ref(s3);
    float pid_value = error * kp + (error - last_error) * kd;
    last_error = error;
    return pid_value;
}

void linefollow_slow(int speed, int deg, bool brake)
{
    float kp = 0.3;
    float kd = 50;
    int initial_b = m_get_deg(b);
    while (abs(m_get_deg(b) - initial_b) < deg) {
        on(speed, linefollow_control(kp, kd));
    }
    current_speed = speed;
    if (brake) {
        off(brake);
        current_speed = 0;
    }
}

void linefollow_intersection(int speed, bool brake)
{
    float kp = 0.3;
    if (speed < 40) {
        kp = 0.4;
    }
    float kd = 50;
    int initial_b = m_get_deg(b);
    while (col_get_ref(s2) + col_get_ref(s3) > 30 || abs(m_get_deg(b) - initial_b) < 100) {
        on(speed, linefollow_control(kp, kd));
    }
    current_speed = speed;
    if (brake) {
        linefollow_slow(40, 90, true);
        current_speed = 0;
    }
}

void linefollow_deg(int speed, int deg, bool brake)
{
    float kp = 0.4;
    float kd = 30;
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
    float kp = 0.3;
    float kd = 50;
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
    float kp = 0.3;
    float kd = 50;
    while (col_get_ref(s1) > ref_light_s1) {
        on(speed, linefollow_control(kp, kd));
    }
    current_speed = speed;
    if (brake) {
        off(true);
        current_speed = 0;
    }
}