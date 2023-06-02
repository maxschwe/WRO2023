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

// Ship Positions: if new added also increase ADDITIONAL_POS_COUNT
#define SHIP_POS1 135
#define SHIP_POS2 235
#define SHIP_POS3 460
#define SHIP_POS4 570
#define SHIP_POS5 680
#define SHIP_POS6 780
#define SHIP_POS_FINISH 280
#define SHIP_POS_DRIVE_BACK 370

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
