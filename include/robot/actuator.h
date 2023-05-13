#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../core/color_sensor.h"
#include "../core/helpers.h"
#include "../core/motor.h"
#include "ev3api.h"

typedef struct {
    Motor motor;
    int max_pos_speed;
    int max_neg_speed;
} Actuator;

void act_init(Actuator act);
void act_move(Actuator act, int new_position, bool block);
void act_move_speed(Actuator act, int speed, int new_position, bool block);
void move_lifter_up(bool block);
void move_lifter_down(bool block);

#endif