#include "motor.h"

void m_init(Motor m)
{
    ev3_motor_config(m.port, m.type);
}

void m_on(Motor m, int speed)
{
    ev3_motor_set_power(m.port, m.counterclockwise ? -speed : speed);
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