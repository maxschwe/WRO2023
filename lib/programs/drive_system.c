#include "lib/programs/drive_system.h"

int start_deg = 0;

// navigation on field with coords
void drive_to_custom(char start[COORD_SIZE], char start_dir, char dest[COORD_SIZE], char dest_dir, bool brake) {
    char start_loc_type = start[0];
    char start_loc_pos = start[1] - '0';
    // is currently on a strang
    if (start_loc_type == 's') {
        // is on a south strang -> dir must be north
        if (start_loc_pos % 2) {
            if (start_dir == 'e') {
                turn_90(true);
            } else if (start_dir == 's') {
                turn_180(true);
            } else if (start_dir == 'w') {
                turn_90(false);
            }
            start_dir = 'n';
        // is on a north strang -> dir must be south
        } else {
            if (start_dir == 'n') {
                turn_180(true);
            } else if (start_dir == 'e') {
                turn_90(false);
            } else if (start_dir == 'w') {
                turn_90(true);
            }
            start_dir = 's';
        }
        if (start_loc_pos == 2 || start_loc_pos == 7) {
            linefollow_col_1(100, COL_WHITE_REF, false, false);
            linefollow_deg(100, 30, false);
            linefollow_col_1(60, COL_BLACK_REF, true, false);
            linefollow_deg(10, 100, true);
        } else {
            linefollow_intersection(DRIVE_TO_LINEFOLLOW_SPEED, true);
        }
        start_loc_pos = (start_loc_pos + 1) / 2;
    }
    char dest_loc_type = dest[0];
    char dest_loc_pos = dest[1] - '0';

    // dest is strang -> turn in direction of strang and dont use dest_dir
    if (dest_loc_type == 's') {
        dest_dir = (dest_loc_pos % 2) ? 's' : 'n';
        dest_loc_pos = (dest_loc_pos + 1) / 2;
    }

    int intersection_count = abs(start_loc_pos - dest_loc_pos);
    // needs to drive to the east
    if (start_loc_pos < dest_loc_pos) {
        if (start_dir == 'n') {
            turn_90(false);
        } else if (start_dir == 's') {
            turn_90(true);
        } else if (start_dir == 'w') {
            turn_180(true);
        }
        start_dir = 'e';
    // needs to drive to the west
    } else if (start_loc_pos > dest_loc_pos){
        if (start_dir == 'n') {
            turn_90(true);
        }
        else if (start_dir == 'e') {
            turn_180(true);
        }
        else if (start_dir == 's') {
            turn_90(false);
        } 
        start_dir = 'w';
    }
    if (intersection_count > 0) {
        linefollow_smooth(DRIVE_TO_LINEFOLLOW_SPEED, DRIVE_TO_LINEFOLLOW_ACC_DEG, false);
    }
    for (int i = 0; i < intersection_count; ++i) {
        beep();
        linefollow_intersection(DRIVE_TO_LINEFOLLOW_SPEED, ((i+1) >= intersection_count) && brake);
    }
    // turn at the end to correct orientationbeep();
    if (dest_dir == 'n') {
        if (start_dir == 'e') {
            turn_90(true);
        } else if (start_dir == 's') {
            turn_180(true);
        } else if (start_dir == 'w') {
            turn_90(false);
        }
    } else if (dest_dir == 'e') {
        if (start_dir == 'n') {
            turn_90(false);
        } else if (start_dir == 's') {
            turn_90(true);
        } else if (start_dir == 'w') {
            turn_180(true);
        }
    } else if (dest_dir == 's') {
        if (start_dir == 'n') {
            turn_180(true);
        } else if (start_dir == 'e') {
            turn_90(false);
        } else if (start_dir == 'w') {
            turn_90(true);
        }
    } else if (dest_dir == 'w'){
        if (start_dir == 'n') {
            turn_90(true);
        } else if (start_dir == 'e') {
            turn_180(true);
        } else if (start_dir == 's') {
            turn_90(false);
        }
    }
    start_dir = dest_dir;
}

void drive_to(char start[COORD_SIZE], char start_dir, char dest[COORD_SIZE], char dest_dir) {
    drive_to_custom(start, start_dir, dest, dest_dir, true);
}

void init_drive_position() {
    start_deg = m_get_deg(b);
}

void init_drive_position_with_deg(int deg) {
    start_deg = m_get_deg(b) - deg;
}

void drive_position(int target_deg) {
    drive_position_custom(target_deg, DRIVE_MAX_SPEED);
}

void drive_position_custom(int target_deg, int max_speed) {
    int delta_deg = target_deg - m_get_deg(b) + start_deg;
    int speed = DRIVE_START_SPEED;
    if (delta_deg < 0) {
        speed = -speed;
    }
    drive_smooth_custom(speed, speed, max_speed, 0, abs(delta_deg), DRIVE_ACC_FACTOR, DRIVE_DEACC_FACTOR ,true, false);
}
