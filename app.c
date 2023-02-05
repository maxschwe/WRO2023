#include "ev3api.h"
#include "config.h"
#include "app.h"

void main_task(intptr_t unused)
{
    ev3_motor_config(EV3_PORT_D, LARGE_MOTOR);
    ev3_motor_rotate(EV3_PORT_D, 180, 10000, true);
}