#include "config.h"

void init()
{
    ev3_motor_config(A, LARGE_MOTOR);
    ev3_motor_config(B, MEDIUM_MOTOR);
    ev3_motor_config(C, MEDIUM_MOTOR);
    ev3_motor_config(D, LARGE_MOTOR);
    ev3_sensor_config(S1, COLOR_SENSOR);
    ev3_sensor_config(S2, COLOR_SENSOR);
    ev3_sensor_config(S3, COLOR_SENSOR);
    ev3_sensor_config(S4, COLOR_SENSOR);

    ev3_lcd_set_font(EV3_FONT_MEDIUM);
}