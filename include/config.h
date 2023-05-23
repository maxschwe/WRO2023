#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/color_sensor.h"
#include "core/helpers.h"
#include "core/motor.h"
#include "ev3api.h"
#include "robot/actuator.h"

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

// Run Config
#define BLOCK_COL_COUNT 2
#define COLOURED_CONTAINER_COUNT 4
#define SCAN_COUNT 20
#define BLUE_GREEN_SWITCH_VALUE 0.48

// SCAN Config
#define SCAN_MAXIMA_COUNT 4

#define MOVING_AVERAGE_COUNT 200
#define HIGH_PASS_THRESHOLD 0.1
#define MAXIMA_THRESHOLD 0.3
#define MAXIMA_COUNT 4
#define COLOR_THRESHOLD 0.48
#define OUTPUT_PATH "scan1.txt"

// DRIVE Config
#define ACC_FACTOR 5 // 1 Speed change per x degree
#define DEACC_FACTOR 8 // 1 Speed change per x degree
#define MAX_SPEED_LIMIT 100
#define DRIVE_START_SPEED 10

#define MAX_SPEED_LINEFOLLOW 100
#define LINEFOLLOW_ACC 4 // 1 Speed change per x degree
#define LINEFOLLOW_DEACC 5 // 1 Speed change per x degree

// LIFTER Positions
#define LIFTER_INIT 5
#define LIFTER_GRABBED -36
#define LIFTER_BACK_BOAT_GRABBED -90
#define LIFTER_UP -125

// DROPPER Positions
#define DROPPER_INIT 0
#define DROPPER_NORMAL 30
#define DROPPER_DROPPED 145
#define DROPPER_BODEN 140

// Ship Drop off positions
#define POS_COUNT 6
#define POS_SMALL_BOAT_COUNT 2
#define POS_BIG_BOAT_COUNT 4

// change to 6 if you also want last position on big ship to be placed
#define BIG_SHIP_LAST_POSITION_TO_CHECK 5

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

extern int current_speed;
extern int smooth_deg_acc_end;
extern int smooth_deg_deacc_start;
extern int smooth_current_max_speed;
extern float smooth_current_acc_factor;
extern float smooth_current_deacc_factor;
extern int smooth_start_speed;
extern int pos_ship_values[POS_COUNT + 2];

void init();

#endif