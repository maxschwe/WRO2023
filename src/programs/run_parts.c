#include "../../include/programs/run_parts.h"
#include "../../include/config.h"

void place_containers_on_ships(int* scans_blocks, char* scans_containers)
{
    bool occupied[POS_COUNT];
    int scans_blocks_copy[BLOCK_COL_COUNT];
    for (int i = 0; i < BLOCK_COL_COUNT; i++) {
        scans_blocks_copy[i] = scans_blocks[i];
    }
    for (int i = 0; i < POS_COUNT; ++i) {
        occupied[i] = false;
    }
    wait(0.3);
    m_reset(b);

    // drop off white container
    int target_pos = get_free_pos_ship(true, occupied);
    drive_to_ship_position(target_pos);
    drop_off(true, target_pos, occupied);

    // drop off coloured containers
    for (int i = 0; i < COLOURED_CONTAINER_COUNT; i++) {
        bool is_big_ship = false;

        // move lifter up and grabber down on 3. drop off
        if (i == 2) {
            act_move(lifter, LIFTER_UP, false);
        }

        // colour container is blue and big ship needs blue container
        if (scans_containers[i] == 'b' && scans_blocks_copy[0] > 0) {
            is_big_ship = true;

            // colour container is green and big ship needs green container
        } else if (scans_containers[i] == 'g' && scans_blocks_copy[1] > 0) {
            is_big_ship = true;
        }

        if (is_big_ship) {
            // container is blue
            if (scans_containers[i] == 'b') {
                scans_blocks_copy[0]--;
                // container is green
            } else {
                scans_blocks_copy[1]--;
            }
        }

        target_pos = get_free_pos_ship(is_big_ship, occupied);
        drive_to_ship_position(target_pos);
        // bool is_last_container_and_on_first_or_second_position = COLOURED_CONTAINER_COUNT == i + 1 && target_pos <= 2;
        drop_off(true, target_pos, occupied);
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

int get_free_pos_ship(bool big_ship, bool* occupied)
{
    if (big_ship) {
        for (int i = BIG_SHIP_LAST_POSITION_TO_CHECK; i > POS_SMALL_BOAT_COUNT; --i) {
            if (!occupied[i - 1]) {
                return i;
            }
        }
    } else {
        for (int i = POS_SMALL_BOAT_COUNT; i > 0; --i) {
            if (!occupied[i - 1]) {
                return i;
            }
        }
    }
    return POS_COUNT;
}

void drop_off(bool lift_end, int pos, bool* occupied)
{
    act_move(dropper, DROPPER_DROPPED, true);
    occupied[pos - 1] = true;
    if (lift_end) {
        wait(0.2);
        act_move(dropper, DROPPER_NORMAL, true);
    }
}
