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
void linefollow_slow(int speed, int deg, bool brake);
void linefollow_test(int speed, int deg, float kp, float kd, bool brake);
void linefollow_intersection(int speed, bool brake);
void drive_deg(int speed, int target_speed, int steering, int deg, bool brake);
void drive_col(int speed, int steering, ColorSensor sensor, char col, bool brake);
void drive_smooth(int target_speed, int deg, bool brake);
void linefollow_col_1(int speed, int ref_light_s1, bool_t brake);
void linefollow_col_1_greater(int speed, int ref_light_s1, bool_t brake);
void move_up(bool_t block);
void move_down(bool_t block);
char scan(int output_y);
void turn_line(bool turn_left, bool brake);
void turn_90(bool turn_left, bool brake);

#endif