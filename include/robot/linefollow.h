#ifndef LINEFOLLOW_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../core/color_sensor.h"
#include "../core/helpers.h"
#include "../core/motor.h"
#include "../robot/drive.h"
#include "ev3api.h"

float linefollow_get_kp(int speed);
float linefollow_get_kd(int speed);
void linefollow_intersection(int speed, bool brake);
void linefollow_intersection_custom(int speed, float kp, float kd, bool brake);
void linefollow_col_1(int speed, int ref_light_s1, bool brake);
void linefollow_col_1_greater(int speed, int ref_light_s1, bool brake);
void linefollow_deg(int speed, int deg, bool brake);
void linefollow_deg_custom(int speed, int deg, float kp, float kd, bool brake);
void linefollow_smooth(int end_speed, int deg, bool brake);

#endif