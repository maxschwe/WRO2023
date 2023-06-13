#include "lib/programs/globals_programs.h"

// char* scans_blocks
char scans_blocks[BLOCKS_COUNT];
// char* scans_containers;
char scans_containers[COLOURED_CONTAINER_COUNT];

int blocks_col_counts[BLOCK_COLORS_COUNT];
bool occupied_ship_pos[SHIP_POS_COUNT];

int pos_ship_values[SHIP_POS_COUNT + ADDITIONAL_POS_COUNT] = { SHIP_POS1, SHIP_POS2, SHIP_POS3, SHIP_POS4, SHIP_POS5, SHIP_POS6, SHIP_POS_FINISH, SHIP_POS_DRIVE_BACK };

char needed_for_big_ship[BIG_SHIP_POS_COUNT];
char needed_for_small_ship[SMALL_SHIP_POS_COUNT];
char colors_in_slider[6];

void init_programs_globals()
{
    for (int i = 0; i < BLOCK_COLORS_COUNT; ++i) {
        blocks_col_counts[i] = 0;
    }
    for (int i = 0; i < SHIP_POS_COUNT; ++i) {
        occupied_ship_pos[i] = false;
    }
    for (int i = 0; i < BIG_SHIP_POS_COUNT; ++i) {
        needed_for_big_ship[i] = 'x';
    }
    for (int i = 0; i < SMALL_SHIP_POS_COUNT; ++i) {
        needed_for_small_ship[i] = 'x';
    }
    for (int i = 0; i < 6; ++i) {
        colors_in_slider[i] = 'x';
    }
}

