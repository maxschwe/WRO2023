#pragma once

#include <stdbool.h>

#include "lib/robot/motor.h"

typedef struct {
    Motor* motor;
    int max_pos_speed;
    int max_neg_speed;
} Actuator;

void act_init(Actuator act);
void act_move(Actuator act, int new_position, bool block);
void act_move_speed(Actuator act, int speed, int new_position, bool block);
