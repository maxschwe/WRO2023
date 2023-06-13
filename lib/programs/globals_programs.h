#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "lib/programs/_programs_config.h"

void init_programs_globals();

// extern char* scans_blocks;
extern char scans_blocks[BLOCKS_COUNT];
// extern char* scans_containers;
extern char scans_containers[COLOURED_CONTAINER_COUNT];
extern int blocks_col_counts[BLOCK_COLORS_COUNT];
extern bool occupied_ship_pos[SHIP_POS_COUNT];
extern int pos_ship_values[SHIP_POS_COUNT + ADDITIONAL_POS_COUNT];
extern char needed_for_big_ship[BIG_SHIP_POS_COUNT];
extern char needed_for_small_ship[SMALL_SHIP_POS_COUNT];
extern char colors_in_slider[6];
