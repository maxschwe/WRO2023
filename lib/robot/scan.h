#pragma once

#include <stdlib.h>

#include "lib/robot/_robot_config.h"
#include "lib/robot/color_sensor.h"
#include "lib/robot/globals.h"
#include "lib/robot/helpers.h"

#include "lib/utils/float_array.h"

char simple_scan();
void init_complex_scan();
void complex_scan();
char* evaluate_complex_scan(int maxima_count, char* output_path);
