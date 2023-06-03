#include "lib/robot/color_sensor.h"

void col_init(ColorSensor s)
{
    ev3_sensor_config(s.port, COLOR_SENSOR);
}
int col_get_ref(ColorSensor s)
{
    return ev3_color_sensor_get_reflect(s.port);
}
rgb_t col_get_rgb(ColorSensor s)
{
    rgb_t rgb_val;
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

bool col_check_ref(ColorSensor s, int compare_value, bool check_lower)
{
    if (check_lower) {
        return col_get_ref(s) < compare_value;
    } else {
        return col_get_ref(s) > compare_value;
    }
}

void col_wait_ref(ColorSensor s, int compare_value, bool check_lower)
{
    while (!col_check_ref(s, compare_value, check_lower)) { }
}

float col_get_rel_rgb(ColorSensor s, char col)
{
    rgb_t rgb_value = col_get_rgb(s);
    int sum = rgb_value.r + rgb_value.b + rgb_value.g + 1;

    // blue relative
    if (col == 'b') {
        if (rgb_value.b <= COL_REL_RGB_THRESHOLD) {
            rgb_value.b = 0;
        }
        return (1.0 * rgb_value.b) / sum;
        // green relative
    } else if (col == 'g') {
        if (rgb_value.g <= COL_REL_RGB_THRESHOLD) {
            rgb_value.g = 0;
        }
        return (1.0 * rgb_value.g) / sum;
        // red relative
    } else {
        if (rgb_value.r <= COL_REL_RGB_THRESHOLD) {
            rgb_value.r = 0;
        }
        return (1.0 * rgb_value.r) / sum;
    }
}
