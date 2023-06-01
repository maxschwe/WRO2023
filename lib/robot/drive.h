#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "lib/robot/motor.h"
#include "lib/robot/color_sensor.h"
#include "lib/robot/helpers.h"
#include "lib/robot/globals.h"
#include "lib/robot/scan.h"

#include "lib/utils/float_array.h"
#include "lib/utils/drive_control.h"

void on(int speed, int steering);
void off();
void wait_stand();

void drive_smooth_custom(int start_speed, int end_speed, int max_speed_limit, int steering, int deg, bool brake, bool scan);
void drive_smooth(int end_speed, int steering, int deg, bool brake);
void drive_deg(int speed, int steering, int deg, bool brake);
void drive_col(int speed, int steering, ColorSensor sensor, int compare_value, bool check_lower, bool brake);
void drive_time(int speed, int steering, float seconds, bool brake);

void turn_line(bool turn_left, bool brake);
void turn_90(bool turn_left);
void turn_180(bool turn_left);
void turnsing_90(bool turn_left, bool turn_forward);
void turnsing_180(bool turn_left, bool turn_forward);

extern int current_speed;
