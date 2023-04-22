#ifndef LINEFOLLOW_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../core/color_sensor.h"
#include "../core/helpers.h"
#include "../core/motor.h"
#include "../robot/drive.h"
#include "ev3api.h"

void linefollow_slow(int speed, int deg, bool brake);
void linefollow_intersection(int speed, bool brake);
void linefollow_col_1(int speed, int ref_light_s1, bool brake);
void linefollow_col_1_greater(int speed, int ref_light_s1, bool brake);
void linefollow_deg(int speed, int deg, bool brake);

#endif