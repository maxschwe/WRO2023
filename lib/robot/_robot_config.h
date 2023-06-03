#pragma once

// ----------------------------
// ---------- motors ----------
// ----------------------------
#define A_COUNTERCLOCKWISE false
#define B_COUNTERCLOCKWISE true
#define C_COUNTERCLOCKWISE false
#define D_COUNTERCLOCKWISE false

#define A_LARGE_MOTOR true
#define B_LARGE_MOTOR false
#define C_LARGE_MOTOR false
#define D_LARGE_MOTOR true

// -------------------------------
// ---------- actuators ----------
// -------------------------------
// lifter (port d)
#define LIFTER_MAX_POS_SPEED 40
#define LIFTER_MAX_NEG_SPEED 60

#define LIFTER_INIT -5
#define LIFTER_GRABBED 60
#define LIFTER_BACK_BOAT_GRABBED 115
#define LIFTER_UP 190

// dropper (port a)
#define DROPPER_MAX_POS_SPEED 20
#define DROPPER_MAX_NEG_SPEED 40

#define DROPPER_INIT 0
#define DROPPER_NORMAL 25
#define DROPPER_DROPPED 140
#define DROPPER_BODEN 140

// ---------------------------
// ---------- drive ----------
// ---------------------------
#define DRIVE_ACC_FACTOR 5 // 1 Speed change per x degree
#define DRIVE_DEACC_FACTOR 8 // 1 Speed change per x degree
#define DRIVE_START_SPEED 10
#define DRIVE_MAX_SPEED 100
#define STEERING_CORRECTION_FACTOR 50.0

// turn degrees
#define TURN_90_DEG 312
#define TURN_180_DEG 630
#define TURNSING_90_DEG 630
#define TURNSING_180_DEG 1260

// --------------------------------
// ---------- linefollow ----------
// --------------------------------
#define LINEFOLLOW_ACC 4 // 1 Speed change per x degree
#define LINEFOLLOW_DEACC 5 // 1 Speed change per x degree
#define LINEFOLLOW_START_SPEED 15 // 1 Speed change per x degree
#define LINEFOLLOW_MAX_SPEED 100

#define LINEFOLLOW_INTERSECTION_VALUE 30
#define LINEFOLLOW_INTERSECTION_INITIAL_DEG 100

#define KP_10 0.3
#define KP_25 0.3
#define KP_50 0.2
#define KP_75 0.25
#define KP_100 0.35

#define KD_10 20
#define KD_25 20
#define KD_50 10
#define KD_75 10
#define KD_100 15

// ----------------------------------
// ---------- color sensor ----------
// ----------------------------------
#define COL_BLACK_REF 30
#define COL_WHITE_REF 60
#define COL_GREY_REF 35
#define COL_LIGHT_BLUE_REF 22

#define COL_REL_RGB_THRESHOLD 4 // threshold for relative value to pass (if lower -> result is 0)
#define SIMPLE_SCAN_COUNT 20
#define SCAN_RGB_RELATIVE_COLOR 'b'
#define COLOR_DECIDE_VALUE 0.48
#define COLOR_IF_HIGHER 'b'
#define COLOR_IF_LOWER 'g'

// -----------------------------------------
// ---------- complex scan config ----------
// -----------------------------------------
#define MOVING_AVERAGE_COUNT 100
#define MAXIMUM_THRESHOLD 0.2
#define COLOR_THRESHOLD 0.48

// ----------------------------------
// ---------- debug prints ----------
// ----------------------------------
// #define DRIVE_SMOOTH_PRINT_DEBUG true

// -----------------------------
// ---------- display ----------
// -----------------------------
#define DISPLAY_MAX_SPOTS 12
#define DISPLAY_SPOT_MAX_LENGTH 11
// -----------------------------------
