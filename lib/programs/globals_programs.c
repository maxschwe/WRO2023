#include "lib/programs/globals_programs.h"

char *scans_blocks;
char *scans_containers;

int blocks_col_counts[BLOCK_COLORS_COUNT];
bool occupied_ship_pos[SHIP_POS_COUNT];

void init_programs_globals() {
    for (int i = 0; i < BLOCK_COLORS_COUNT; ++i) {
        blocks_col_counts[i] = 0;
    }
    for (int i = 0; i < SHIP_POS_COUNT; ++i) {
        occupied_ship_pos[i] = false;
    }
    // scans_blocks = malloc(sizeof(char) * BLOCKS_COUNT);
    scans_containers = malloc(sizeof(char) * COLOURED_CONTAINER_COUNT);
}
