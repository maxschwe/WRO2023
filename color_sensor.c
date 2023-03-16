#include "color_sensor.h"

void col_init(ColorSensor s)
{
    ev3_sensor_config(s.port, COLOR_SENSOR);
}
int col_get_ref(ColorSensor s)
{
    return ev3_color_sensor_get_reflect(s.port);
}
rgb col_get_rgb(ColorSensor s)
{
    rgb rgb_val;
    ev3_color_sensor_get_rgb_raw(s.port, &rgb_val);
    return rgb_val;
}
int col_get_amb(ColorSensor s)
{
    return ev3_color_sensor_get_ambient(s.port);
}

int col_get_col(ColorSensor s)
{
    // TODO: calculate every color from rgb val
    return 0;
}