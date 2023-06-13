#pragma once

#define BLOCKS_COUNT 2
#define BLOCK_COLORS_COUNT 2
#define COLOURED_CONTAINER_COUNT 4

#define SMALL_SHIP_POS_COUNT 2
#define BIG_SHIP_POS_COUNT 4
#define SHIP_POS_COUNT (SMALL_SHIP_POS_COUNT + BIG_SHIP_POS_COUNT)
#define ADDITIONAL_POS_COUNT 2

// change to 6 if you also want last position on big ship to be placed
#define BIG_SHIP_LAST_POSITION_TO_CHECK 5

// Ship Positions: if new position added also increase ADDITIONAL_POS_COUNT
#define SHIP_POS1 150
#define SHIP_POS2 250
#define SHIP_POS3 450
#define SHIP_POS4 550
#define SHIP_POS5 659
#define SHIP_POS6 750
#define SHIP_POS_FINISH 260
#define SHIP_POS_DRIVE_BACK 330

// scans
#define SAVE_SCANS_BLOCKS true

#if SAVE_SCANS_BLOCKS
#define SCANS_BLOCKS_FILEPATH "blocks.txt"
#else
#define SCANS_BLOCKS_FILEPATH NULL
#endif

#define SAVE_SCANS_CONTAINERS true

#if SAVE_SCANS_CONTAINERS
#define SCANS_CONTAINERS_FILEPATH "containers.txt"
#else
#define SCANS_CONTAINERS_FILEPATH NULL
#endif
