#include "../../include/core/color_sensor.h"
#include "../../include/config.h"

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

double col_get_rel_rgb(ColorSensor s, char col)
{
    rgb_t rgb_value = col_get_rgb(s);
    long sum = rgb_value.r + rgb_value.b + rgb_value.g + 1;
    if (col == 'b') {
        if (rgb_value.b < 3) {
            rgb_value.b = 0;
        }
        return (1.0 * rgb_value.b) / sum;
    } else if (col == 'g') {
        if (rgb_value.g < 3) {
            rgb_value.g = 0;
        }
        return (1.0 * rgb_value.g) / sum;
    } else {
        if (rgb_value.r < 3) {
            rgb_value.r = 0;
        }
        return (1.0 * rgb_value.r) / sum;
    }
}

char scan(int output_y)
{
    char output[100];
    rgb_t val = col_get_rgb(s4);
    float lowest_r = 0.0;
    float lowest_g = 0.0;
    float lowest_b = 0.0;
    for (int i = 0; i < SCAN_COUNT; ++i) {
        val = col_get_rgb(s4);
        lowest_r += val.r;
        lowest_g += val.g;
        lowest_b += val.b;
    }
    lowest_r /= SCAN_COUNT;
    lowest_g /= SCAN_COUNT;
    lowest_b /= SCAN_COUNT;
    // sprintf(output, "R: %f", lowest_r);
    // ev3_lcd_draw_string(output, 10, 30);
    // sprintf(output, "G: %f", lowest_g);
    // ev3_lcd_draw_string(output, 10, 50);
    // sprintf(output, "B: %f", lowest_b);
    // ev3_lcd_draw_string(output, 10, 70);
    float blue_rel = lowest_b / (lowest_b + lowest_r + lowest_g + 1);
    sprintf(output, "%f, %c", blue_rel, (blue_rel < BLUE_GREEN_SWITCH_VALUE) ? 'g' : 'b');
    ev3_lcd_draw_string(output, 10, output_y);
    return (blue_rel < BLUE_GREEN_SWITCH_VALUE) ? 'g' : 'b';
}