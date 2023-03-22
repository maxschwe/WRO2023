#ifndef DRIVE_H
#define DRIVE_H

#include <config.h>
#include <stdio.h>
#include <stdlib.h>

void on(int speed, int steering);
void off(bool brake);
void linefollow(int speed, int deg);
void linefollow_intersection(int speed, bool_t brake);
void drive_deg2(int initial_speed, int target_speed, int steering, int deg, bool_t brake);
void drive_deg(int speed, int target_speed, int steering, int deg, bool brake);
void linefollow_intersection(int speed, bool_t brake);
void linefollow_deg(int speed, int deg, bool_t brake);
void linefollow_col_1(int speed, int ref_light_s1, bool_t brake);
void move_up(bool_t block);
void move_down(bool_t block);
char scan(int output_y);

#endif