#pragma once

#include "ev3api.h"

#include "lib/robot/_robot_config.h"

#include "lib/robot/actuator.h"
#include "lib/robot/color_sensor.h"
#include "lib/robot/motor.h"
#include "lib/robot/scan.h"

extern Motor a;
extern Motor b;
extern Motor c;
extern Motor d;

extern ColorSensor s1;
extern ColorSensor s2;
extern ColorSensor s3;
extern ColorSensor s4;

extern Actuator lifter;
extern Actuator dropper;

void init_robot();
