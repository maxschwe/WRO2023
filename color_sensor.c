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

void col_wait_until_block()
{
    rgb rgb_val = col_get_rgb(s4);
    float rgb_rel;
    int i = 0;
    int count = 0;
    while (true) {
        rgb_val = col_get_rgb(s4);
        rgb_rel = 1.0 * rgb_val.b / (rgb_val.r + rgb_val.g + rgb_val.b + 1);
        if (rgb_rel < 0.3) {
            if (++count >= 20) {
                break;
            }
        } else {
            count = 0;
        }
    }
}

void col_wait_ref(ColorSensor s, char col)
{
    int compare_val;
    bool compare_lower;
    switch (col) {
    case BLACK:
        compare_val = BLACK_REF;
        compare_lower = true;
        break;
    case WHITE:
        compare_val = WHITE_REF;
        compare_lower = false;
        break;
    case GREY:
        compare_val = GREY_REF;
        compare_lower = true;
    default:
        compare_val = BLACK_REF;
        compare_lower = true;
    }
    if (compare_lower) {
        while (col_get_ref(s) > compare_val) { }
    } else {
        while (col_get_ref(s) < compare_val) { }
    }
}