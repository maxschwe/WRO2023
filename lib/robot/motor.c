#include "lib/robot/motor.h"

void m_init(Motor m)
{
    ev3_motor_config(m.port, m.is_large_motor ? LARGE_MOTOR : MEDIUM_MOTOR);
}

void m_on(Motor m, int speed)
{
    ev3_motor_set_power(m.port, m.counterclockwise ? -speed : speed);
}

void m_on_deg(Motor m, int speed, int deg, bool brake, bool block)
{
    ev3_motor_rotate(m.port, m.counterclockwise ? -deg : deg, abs(speed), block);
}

void m_off(Motor m, bool brake)
{
    ev3_motor_stop(m.port, brake);
}

int m_get_deg(Motor m)
{
    int deg = ev3_motor_get_counts(m.port);
    return m.counterclockwise ? -deg : deg;
}

void m_reset(Motor m)
{
    ev3_motor_reset_counts(m.port);
}

void m_wait_deg(Motor m, int deg)
{
    m_reset(m);
    while (abs(m_get_deg(m)) < deg) {
    }
}

int m_get_speed(Motor m)
{
    int speed = ev3_motor_get_power(m.port);
    return m.counterclockwise ? -speed : speed;
}

void m_reset_stall(Motor m)
{
    m.stall_detection->is_currently_stalled = 0;
}

bool m_check_stall(Motor m)
{
    bool is_currently_stalled = m_get_speed(m) < 6;
    if (is_currently_stalled) {
        if (!(m.stall_detection->is_currently_stalled)) {
            m.stall_detection->is_currently_stalled = true;
            m.stall_detection->stall_detection_count = 0;
        } else if (m.stall_detection->stall_detection_count > m.stall_detection->stall_detection_count_max) {
            return true;
        }
        m.stall_detection->stall_detection_count++;
    } else {
        m.stall_detection->is_currently_stalled = false;
    }
    return false;
}
