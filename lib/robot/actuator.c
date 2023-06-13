#include "lib/robot/actuator.h"

void act_init(Actuator act)
{
    m_reset(*act.motor);
}
void act_move(Actuator act, int new_position, bool block)
{
    act_move_speed(act, 0, new_position, block);
}
void act_move_speed(Actuator act, int speed, int new_position, bool block)
{
    speed = abs(speed);
    int rel_deg = new_position - m_get_deg(*act.motor);
    if (speed == 0) {
        if (rel_deg < 0) {
            speed = act.max_neg_speed;
        } else {
            speed = act.max_pos_speed;
        }
    }
    if (block) {
        m_reset_stall(*act.motor);
        int initial_motor = m_get_deg(*act.motor);
        if (rel_deg < 0) {
            speed = -speed;
        }
        rel_deg = abs(rel_deg);
        m_on(*act.motor, speed);
        while (abs(m_get_deg(*act.motor) - initial_motor) < rel_deg) {
            if (m_check_stall(*act.motor)) {
                m_off(*act.motor, true);
                error_beep2();
                break;
            }
        }
        m_off(*act.motor, true);
    } else {
        m_on_deg(*act.motor, speed, rel_deg, true, block);
    }
}
