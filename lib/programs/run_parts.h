#pragma once

#include "lib/includes.h"

void place_containers_on_ships();
void drive_to_ship_position(int target_pos);
int get_free_pos_ship(bool big_ship);
void drop_off(bool lift_end, int pos);
