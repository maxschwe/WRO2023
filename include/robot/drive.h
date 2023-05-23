#ifndef DRIVE_H
#define DRIVE_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../core/color_sensor.h"
#include "../core/float_array.h"
#include "../core/helpers.h"
#include "../core/motor.h"
#include "ev3api.h"

void on(int speed, int steering);
void off(bool brake);
void drive_deg(int speed, int target_speed, int steering, int deg, bool brake);
void drive_col(int speed, int steering, ColorSensor sensor, char col, bool brake);
void turn_line(bool turn_left, bool brake);
void turn_90(bool turn_left, bool brake);
void drive_smooth(int end_speed, int steering, int deg, bool brake);
void drive_smooth_custom(int start_speed, int end_speed, int max_speed_limit, int steering, int deg, bool brake, float_array* data);

#endif