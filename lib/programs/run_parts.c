#include "lib/programs/run_parts.h"

int pos_ship_values[SHIP_POS_COUNT + ADDITIONAL_POS_COUNT] = { SHIP_POS1, SHIP_POS2, SHIP_POS3, SHIP_POS4, SHIP_POS5, SHIP_POS6, SHIP_POS_FINISH, SHIP_POS_DRIVE_BACK };

void place_containers_on_ships()
{
    int blocks_col_counts_copy[BLOCK_COLORS_COUNT];
    for (int i = 0; i < BLOCK_COLORS_COUNT; i++) {
        blocks_col_counts_copy[i] = scans_blocks[i];
    }
    
    wait_stand();
    m_reset(b);

    // drop off white container
    int target_pos = get_free_pos_ship(true);
    drive_to_ship_position(target_pos);
    drop_off(true, target_pos);

    // drop off coloured containers
    for (int i = 0; i < COLOURED_CONTAINER_COUNT; i++) {
        bool is_big_ship = false;

        // move lifter up and grabber down on 3. drop off
        if (i == 2) {
            act_move(lifter, LIFTER_UP, false);
        }

        // colour container is blue and big ship needs blue container
        if (scans_containers[i] == 'b' && blocks_col_counts_copy[0] > 0) {
            is_big_ship = true;

            // colour container is green and big ship needs green container
        } else if (scans_containers[i] == 'g' && blocks_col_counts_copy[1] > 0) {
            is_big_ship = true;
        }

        if (is_big_ship) {
            // container is blue
            if (scans_containers[i] == 'b') {
                blocks_col_counts_copy[0]--;
                // container is green
            } else {
                blocks_col_counts_copy[1]--;
            }
        }

        target_pos = get_free_pos_ship(is_big_ship);
        drive_to_ship_position(target_pos);
        // bool is_last_container_and_on_first_or_second_position = COLOURED_CONTAINER_COUNT == i + 1 && target_pos <= 2;
        drop_off(true, target_pos);
    }

    // drive in finish
    if (target_pos > 2) {
        drive_to_ship_position(7);
    }
}

void drive_to_ship_position(int target_pos)
{
    int delta_deg = pos_ship_values[target_pos - 1] - m_get_deg(b);
    int speed = 10;
    if (delta_deg < 0) {
        speed = -speed;
    }
    drive_smooth(speed, 0, delta_deg, true);
}

int get_free_pos_ship(bool big_ship)
{
    if (big_ship) {
        for (int i = BIG_SHIP_LAST_POSITION_TO_CHECK; i > SMALL_SHIP_POS_COUNT; --i) {
            if (!occupied_ship_pos[i - 1]) {
                return i;
            }
        }
    } else {
        for (int i = SMALL_SHIP_POS_COUNT; i > 0; --i) {
            if (!occupied_ship_pos[i - 1]) {
                return i;
            }
        }
    }
    return SHIP_POS_COUNT;
}

void drop_off(bool lift_end, int pos)
{
    act_move(dropper, DROPPER_DROPPED, true);
    occupied_ship_pos[pos - 1] = true;
    if (lift_end) {
        wait(0.2);
        act_move(dropper, DROPPER_NORMAL, true);
    }
}
