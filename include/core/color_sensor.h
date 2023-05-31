#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ev3api.h"

#include "helpers.h"

typedef rgb_raw_t rgb_t;

typedef struct {
    sensor_port_t port;
} ColorSensor;

void col_init(ColorSensor s);
int col_get_ref(ColorSensor s);
rgb_t col_get_rgb(ColorSensor s);
int col_get_amb(ColorSensor s);
void col_wait_ref(ColorSensor s, char col);
double col_get_rel_rgb(ColorSensor s, char col);
char scan(int output_y);

#endif