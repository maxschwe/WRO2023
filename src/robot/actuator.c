#include "../../include/robot/actuator.h"
#include "../../include/config.h"

void act_init(Actuator act)
{
    m_reset(act.motor);
}
void act_move(Actuator act, int new_position, bool block)
{
    act_move_speed(act, 0, new_position, block);
}
void act_move_speed(Actuator act, int speed, int new_position, bool block)
{
    speed = abs(speed);
    int rel_deg = new_position - m_get_deg(act.motor);
    int cur_deg = 0;
    if (speed == 0) {
        if (rel_deg < 0) {
            speed = act.max_neg_speed;
        } else {
            speed = act.max_pos_speed;
        }
    }
    while (abs(new_position - (cur_deg = m_get_deg(act.motor))) > 5 && abs(m_get_speed(act.motor)) > 5) {
        }
}
