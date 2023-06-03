#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "lib/robot/_robot_config.h"
#include "lib/robot/drive.h"
#include "lib/robot/globals.h"
#include "lib/robot/helpers.h"

#include "lib/utils/drive_control.h"
#include "lib/utils/utils.h"

float linefollow_get_kp(int speed);
float linefollow_get_kd(int speed);
float linefollow_control(float kp, float kd);

void linefollow_intersection_custom(int speed, float kp, float kd, bool brake);
void linefollow_intersection(int speed, bool brake);
void linefollow_smooth_custom(int start_speed, int end_speed, int max_speed, int deg, bool brake);
void linefollow_smooth(int end_speed, int deg, bool brake);
void linefollow_deg_custom(int speed, int deg, float kp, float kd, bool brake);
void linefollow_deg(int speed, int deg, bool brake);
void linefollow_col_1(int speed, int ref_light_s1, bool lower, bool brake);
