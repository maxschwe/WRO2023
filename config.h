#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "color_sensor.h"
#include "drive.h"
#include "ev3api.h"
#include "helpers.h"
#include "motor.h"

#define A_COUNTERCLOCKWISE false
#define B_COUNTERCLOCKWISE true
#define C_COUNTERCLOCKWISE false
#define D_COUNTERCLOCKWISE false

#define BLACK_REF 30
#define WHITE_REF 60
#define GREY_REF 50

#define BLACK 'b'
#define WHITE 'w'
#define GREY 'g'

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

void init();

#endif