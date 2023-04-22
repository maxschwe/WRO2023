#ifndef RUN_PARTS_H
#define RUN_PARTS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../core/color_sensor.h"
#include "../core/helpers.h"
#include "../core/motor.h"
#include "../robot/drive.h"
#include "ev3api.h"

void place_containers_on_ships(int* scans_blocks, char* scans_containers);
void drive_to_ship_position(int target_pos);
void drop_off(bool lift_end, int pos, bool* occupied);
int get_free_pos_ship(bool big_ship, bool* occupied);

#endif