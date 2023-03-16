#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include "ev3api.h"

typedef struct {
    sensor_port_t port;
} ColorSensor;

typedef rgb_raw_t rgb;

void col_init(ColorSensor s);
int col_get_ref(ColorSensor s);
rgb_raw_t col_get_rgb(ColorSensor s);
int col_get_amb(ColorSensor s);

#endif