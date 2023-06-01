#pragma once

#include <stdbool.h>

#include "ev3api.h"

#include "lib/robot/_robot_config.h"

typedef rgb_raw_t rgb_t;

typedef struct {
    sensor_port_t port;
} ColorSensor;

void col_init(ColorSensor s);
int col_get_ref(ColorSensor s);
rgb_t col_get_rgb(ColorSensor s);
int col_get_amb(ColorSensor s);
bool col_check_ref(ColorSensor s, int compare_value, bool check_lower);
void col_wait_ref(ColorSensor s, int compare_value, bool check_lower);
float col_get_rel_rgb(ColorSensor s, char col);
