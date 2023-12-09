#pragma once

#include "lib/includes.h"

// normal program
void start_backward_and_scan();
void drive_to_white_containers();
void collect_white_container();
void collect_and_scan_coloured_containers();
void collect_big_ship();
void collect_small_ship();
void drive_to_open_sea_and_drop_red_container();
void place_ships();
void place_containers_on_ships();

// helper functions
void drive_to_ship_position(int target_pos);
int get_free_pos_ship(bool big_ship);
void drop_off(bool lift_end, int pos);

// second day
void drive_and_drop_off_second_red_container();
void collect_blocks_start();
void collect_blocks_end();
void collect_containers_on_block_position();
void place_containers_big_ship(bool boat_front, bool flag_left);
void place_containers_small_ship(bool boat_front, bool flag_left);
void collect_containers(bool standing_at_white);
void collect_and_scan_coloured_containers_in_order();
void place_containers_in_order();
