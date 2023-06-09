#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "lib/robot/_robot_config.h"
#include "lib/utils/utils.h"

void init_smooth_speed_controller(int start_speed, int end_speed, int max_speed_limit, float acc_factor, float deacc_factor, int deg);
int get_smooth_speed(int deg);
void init_steering_controller(int steering, int deg, int start_b, int start_c);
void get_steering(int current_deg_b, int current_deg_c, int* speed, int* steering);
