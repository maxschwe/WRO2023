#include "lib/programs/globals_programs.h"

// char* scans_blocks
char scans_blocks[BLOCKS_COUNT];
// char* scans_containers;
char scans_containers[COLOURED_CONTAINER_COUNT];

int blocks_col_counts[BLOCK_COLORS_COUNT];
bool occupied_ship_pos[SHIP_POS_COUNT];

int pos_ship_values[SHIP_POS_COUNT + ADDITIONAL_POS_COUNT] = { SHIP_POS1, SHIP_POS2, SHIP_POS3, SHIP_POS4, SHIP_POS5, SHIP_POS6, SHIP_POS_FINISH, SHIP_POS_FINISH };

void init_programs_globals()
{
    for (int i = 0; i < BLOCK_COLORS_COUNT; ++i) {
        blocks_col_counts[i] = 0;
    }
    for (int i = 0; i < SHIP_POS_COUNT; ++i) {
        occupied_ship_pos[i] = false;
    }
}
