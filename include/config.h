#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "core/color_sensor.h"
#include "core/helpers.h"
#include "core/motor.h"
#include "robot/actuator.h"

#include "ev3api.h"

#define A_COUNTERCLOCKWISE false
#define B_COUNTERCLOCKWISE true
#define C_COUNTERCLOCKWISE false
#define D_COUNTERCLOCKWISE true

#define BLACK_REF 30
#define WHITE_REF 60
#define GREY_REF 45

#define BLACK 'b'
#define WHITE 'w'
#define GREY 'g'

// LIFTER Positions
#define LIFTER_INIT 0
#define LIFTER_GRABBED 40
#define LIFTER_BACK_BOAT_GRABBED 75
#define LIFTER_UP 135

// DROPPER Positions
#define DROPPER_INIT 0
#define DROPPER_NORMAL 30
#define DROPPER_DROPPED 140

#define PRINT_DRIVE_DEBUG false

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

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

void init();

#endif