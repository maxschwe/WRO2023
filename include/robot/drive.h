#ifndef DRIVE_H
#define DRIVE_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../core/color_sensor.h"
#include "../core/helpers.h"
#include "../core/motor.h"
#include "ev3api.h"

#define ACC_PER_100_DEG 50
#define DEACC_PER_100_DEG 50

void on(int speed, int steering);
void off(bool brake);
void drive_deg(int speed, int target_speed, int steering, int deg, bool brake);
void drive_col(int speed, int steering, ColorSensor sensor, char col, bool brake);
void drive_smooth(int target_speed, int deg, bool brake);
void move_up(bool block);
void move_down(bool block);
char scan(int output_y);
void turn_line(bool turn_left, bool brake);
void turn_90(bool turn_left, bool brake);

#endif