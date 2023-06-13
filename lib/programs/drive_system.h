#pragma once

#define COORD_SIZE 3

#include "lib/includes.h"

void drive_to(char start[COORD_SIZE], char start_dir, char dest[COORD_SIZE], char dest_dir);
void drive_to_custom(char start[COORD_SIZE], char start_dir, char dest[COORD_SIZE], char dest_dir, bool brake);
void init_drive_position();
void init_drive_position_with_deg(int deg);
void drive_position(int target_deg);
void drive_position_custom(int target_deg, int max_speed);
