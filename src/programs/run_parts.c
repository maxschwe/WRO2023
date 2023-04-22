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
    wait(0.2);
    m_reset(b);

    // drop off white container
    drive_to_ship_position(5);
    drop_off(true, 5, occupied);

    // drop off coloured containers
    for (int i = 0; i < COLOURED_CONTAINER_COUNT; i++) {
        bool is_big_ship = false;

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

        int target_pos = get_free_pos_ship(is_big_ship, occupied);
        drive_to_ship_position(target_pos);
        bool is_last_container_and_on_last_position = COLOURED_CONTAINER_COUNT == i + 1 && target_pos == 1;
        drop_off(!is_last_container_and_on_last_position, target_pos, occupied);
    }

    // drive in finish
    drive_to_ship_position(1);
}

void drive_to_ship_position(int target_pos)
{
    int delta_deg = pos_ship_values[target_pos - 1] - m_get_deg(b);
    int speed = 15;
    if (delta_deg < 0) {
        speed = -speed;
    }
    drive_deg(speed, speed, 0, abs(delta_deg), true);
}

int get_free_pos_ship(bool big_ship, bool* occupied)
{
    int initial_pos_check = 1;
    if (big_ship) {
        initial_pos_check += POS_SMALL_BOAT_COUNT;
    }
    for (int i = initial_pos_check; i <= POS_COUNT; ++i) {
        if (!occupied[i - 1]) {
            return i;
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
