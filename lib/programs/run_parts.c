#include "lib/programs/run_parts.h"

void inline start_backward_and_scan() {
    drive_smooth_custom(-10, -25, 70, 0, 600, DRIVE_ACC_FACTOR, DRIVE_DEACC_FACTOR, false, false, true);
    drive_col_custom(-25, 0, s1, COL_WHITE_REF, false, false, false);
    drive_smooth_custom(-25, -30, 35, 0, 30, DRIVE_ACC_FACTOR, DRIVE_DEACC_FACTOR, false, false, true);
    drive_col_custom(-30, 0, s1, COL_BLACK_REF, true, false, false);
    drive_smooth_custom(-30, -10, 25, 0, 90, DRIVE_ACC_FACTOR, DRIVE_DEACC_FACTOR, true, false, true);
    float value1, value2;
    char text[20];
    wait(0.2);
    scans_blocks[1] = simple_scan(&value2);
    drive_smooth(20, 0, 30, false);
    drive_col(10, 0, s1, COL_BLACK_REF, true, false);
    drive_smooth(10, 0, 55, false);
    scans_blocks[0] = simple_scan(&value1);
    m_on(a, -2);
    m_on(d, -1);

    // drive backwards and drive to white containers
    drive_smooth(20, 0, 65, true);
    sprintf(text, "%.2f;%c", value1, scans_blocks[0]);
    display_set_text(0, text);
    sprintf(text, "%.2f;%c", value2, scans_blocks[1]);
    display_set_text(1, text);

    for (int i = 0; i < BLOCKS_COUNT; ++i) {
        if (scans_blocks[i] == 'b') {
            ++blocks_col_counts[0];
        } else {
            ++blocks_col_counts[1];
        }
    }
    needed_for_big_ship[0] = 'w';
    needed_for_big_ship[1] = scans_blocks[0];
    needed_for_big_ship[2] = scans_blocks[1];
}

void inline drive_to_white_containers() {
    turn_90(true);

    // stop actuatuors and init
    act_init(lifter);
    act_init(dropper);
    m_off(a, true);
    m_off(d, true);

    linefollow_smooth(100, 150, false);
    linefollow_intersection(100, false);

    linefollow_deg(100, 620, false);
    linefollow_intersection(100, true);

    turn_90(true);
}

void inline collect_white_container() {
    linefollow_smooth(35, 100, false);
    linefollow_deg(30, 300, false);
    beep();
    linefollow_col_1(15, COL_LIGHT_BLUE_REF, false, false);
    linefollow_smooth(10, 26, true);
    beep();
    // collect white container
    wait(0.1);
    turn_90(true);
    wait_stand();
    init_drive_position();

    // surprise rule: collect second white container
    // drive_smooth(-10, 0, 90, true);
    // lifter_collect(true);
    // drive_smooth(10, 0, 180, true);

    drive_smooth(10, 0, 90, true);

    lifter_collect(false);
}

void inline collect_and_scan_coloured_containers() {
    float value1, value2, value3, value4;
    char text[20];
    drive_smooth_custom(10, 30, 30, 0, 50, DRIVE_ACC_FACTOR, DRIVE_DEACC_FACTOR, false, false, true);

    drive_col(30, 0, s1, COL_GREY_REF, false, false);

    // collect with simple scan
    // collect 1. coloured container
    drive_smooth(20, 0, 180, false);
    // wait_center_press();
    scans_containers[0] = simple_scan(&value1);
    drive_smooth(10, 0, 110, true);
    lifter_collect(true);

    // collect 2. coloured container
    drive_smooth(20, 0, 35, false);
    // wait_center_press();
    scans_containers[1] = simple_scan(&value2);
    drive_smooth(10, 0, 105, true);
    lifter_collect(true);

    // collect 3. coloured container
    drive_smooth(20, 0, 35, false);
    // wait_center_press();
    scans_containers[2] = simple_scan(&value3);
    drive_smooth(10, 0, 110, true);
    lifter_collect(true);

    // scan 4. coloured container
    drive_smooth(20, 0, 35, false);
    // wait_center_press();
    scans_containers[3] = simple_scan(&value4);
    drive_smooth(10, 0, 125, true);
    lifter_collect(false);

    sprintf(text, "%.2f;%c", value1, scans_containers[0]);
    display_set_text(2, text);
    sprintf(text, "%.2f;%c", value2, scans_containers[1]);
    display_set_text(3, text);
    sprintf(text, "%.2f;%c", value3, scans_containers[2]);
    display_set_text(4, text);
    sprintf(text, "%.2f;%c", value4, scans_containers[3]);
    display_set_text(5, text);
}

void inline collect_big_ship() {
    // drive forward and take big ship
    drive_col(40, 0, s1, COL_GREY_REF, true, false);
    // drive_smooth(10, 0, 100, true);

    drive_smooth(20, 0, 300, true);
    turn_90(true);
    drive_time(-30, 0, 0.8, true);
    drive_smooth(15, 0, 360, true);
    turn_90(false);
    drive_smooth(10, 0, 240, true);
    // drive_smooth(10, -50, 220, true);
    // drive_smooth(10, 50, 220, true);
    // drive_smooth(10, 0, 245, true);
    act_move(lifter, LIFTER_FORWARD_BOAT_GRABBED, true);

    wait(0.2);
    // move backwards and drive to small ship
    drive_smooth(-80, 0, 300, false);
    on(-80, 0);
    while (col_get_ref(s1) < COL_GREY_REF && col_get_ref(s2) < COL_GREY_REF && col_get_ref(s3) < COL_GREY_REF) {
    }
    drive_smooth(-20, 0, 330, true);
    turn_90(true);
}

void inline collect_small_ship() {
    linefollow_deg(40, 300, false);
    linefollow_col_1(40, COL_BLACK_REF, false, false);
    linefollow_deg(40, 20, false);
    linefollow_col_1(40, COL_BLACK_REF, true, false);
    beep();
    linefollow_deg(40, 200, false);
    linefollow_smooth(10, 100, true);
    wait(0.1);

    // // Trex arme
    // turn_180(true);

    // // collect small ship
    // act_move(lifter, LIFTER_INIT, true);
    // drive_smooth(-15, 0, 430, true);
    // act_move_speed(lifter, 80, LIFTER_BACK_BOAT_GRABBED, true);
    // wait(0.3);

    // // drive to open sea and drop read container
    // linefollow_deg(40, 300, false);
    // linefollow_intersection(20, true);
    // act_move_speed(lifter, 60, LIFTER_FORWARD_BOAT_GRABBED, true);
    // turn_90(false);
    // wait(0.1);

    // normale Arme
    turn_180(true);

    // collect small ship
    act_move(lifter, LIFTER_INIT, true);
    drive_smooth(-15, 0, 430, true);
    act_move_speed(lifter, 80, LIFTER_BACK_BOAT_GRABBED, true);
    off(true);

    wait(0.2);

    // drive to open sea and drop read container
    linefollow_deg(30, 200, false);
    drive_smooth(10, 10, 405, true);
    act_move_speed(lifter, 60, LIFTER_FORWARD_BOAT_GRABBED, false);
    drive_deg(10, 10, 75, true);
    wait_stand();
    turn_line(false, true);
    wait_stand();
}

void inline drive_to_open_sea_and_drop_red_container() {
    linefollow_smooth(100, 100, false);
    linefollow_intersection(100, false);
    linefollow_intersection(100, true);
    turn_90(false);
    linefollow_smooth(40, 780, true);

    // drive again against red container
    // drive_deg(-10, -60, 0, 200, false);
    // drive_deg(-60, -10, 0, 200, true);
    // wait(0.3);
    // drive_deg(10, 40, 0, 200, false);
    // drive_deg(40, 10, 0, 150, true);
}

void inline place_ships() {
    // drive backward
    drive_smooth(-10, 0, 800, true);
    // place big ship

    drive_smooth_custom(10, 10, TURNSING_MAX_SPEED, -50, 645, TURNSING_ACC_FACTOR, TURNSING_DEACC_FACTOR, true, false, false);

    // drive_smooth(10, -50, 640, true);
    act_move_speed(lifter, 80, LIFTER_BACK_BOAT_GRABBED, false);
    drive_smooth(20, 0, 50, false);
    drive_time(20, 0, 0.5, true);
    drive_smooth(-20, 0, 150, true);

    turnsing_180(false, false);
    
    // place small ship
    act_move_speed(lifter, 80, LIFTER_INIT, false);
    drive_smooth(-30, 0, 50, false);
    drive_time(-10, 0, 0.4, true);
    wait_stand();
    drive_smooth(10, 0, 300, true);
    wait_stand();
    turnsing_90(true, false);
}

void inline place_containers_on_ships()
{
    int blocks_col_counts_copy[BLOCK_COLORS_COUNT];
    for (int i = 0; i < BLOCK_COLORS_COUNT; i++) {
        blocks_col_counts_copy[i] = blocks_col_counts[i];
    }
    wait_stand();
    init_drive_position();

    // drop off white container
    wait(0.2);
    int target_pos = get_free_pos_ship(true);
    drive_to_ship_position(target_pos);
    drop_off(true, target_pos);

    // surpise rule: drop off second white container on big ship
    // target_pos = get_free_pos_ship(true);
    // drive_to_ship_position(target_pos);
    // drop_off(true, target_pos);

    // drop off coloured containers
    for (int i = 0; i < COLOURED_CONTAINER_COUNT; i++) {
        bool is_big_ship = false;

        // move lifters up and grabber down on 3. drop off
        if (i == 3) {
            act_move_speed(lifter, 100, LIFTER_UP, false);
        }

        if (scans_containers[i] == 'b' && blocks_col_counts_copy[0] > 0) {
            // colour container is blue and big ship needs blue container
            is_big_ship = true;

        } else if (scans_containers[i] == 'g' && blocks_col_counts_copy[1] > 0) {
            // colour container is green and big ship needs green container
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

        // if it is the last container dont move dropper up
        drop_off(i != 3, target_pos);
    }
    wait(0.2);
    act_move_speed(dropper, 100, DROPPER_INIT, true);

    // drive in finish if not already inside
    if (target_pos > 2) {
        drive_to_ship_position(7);
    }
}

void drive_to_ship_position(int target_pos)
{
    drive_position(pos_ship_values[target_pos - 1]);
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
        // for (int i = 1; i <= SMALL_SHIP_POS_COUNT; ++i) {
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

void inline drive_and_drop_off_second_red_container() {
    turn_90(true);

    // stop actuatuors and init
    act_init(lifter);
    act_init(dropper);
    m_off(a, true);
    m_off(d, true);

    linefollow_smooth(100, 150, false);
    linefollow_intersection(100, false);

    linefollow_deg(100, 620, false);
    linefollow_intersection(100, true);

    act_move(dropper, DROPPER_NORMAL, false);

    turn_90(false);

    // drive forward to second red container drop off
    linefollow_deg(20, 320, true);
    turn_180(true);
    act_move_speed(lifter, 10, LIFTER_RED_CONTAINER, true);
    drive_deg(-10, 0, 80, true);
    drive_deg(10, 100, 30, true);

    wait(0.2);
    
    act_move_speed(lifter, 10, LIFTER_DOWN_CONTAINER, true);

    linefollow_smooth(30, 250, true);

    drive_smooth(-10, 0, 450, true);
    
    linefollow_smooth(100, 300, true);
    linefollow_intersection(100, false);

    // drive forward to white containers
    act_move(lifter, LIFTER_INIT, false);

}

void inline collect_blocks_end() {
    drive_to_ship_position(8);
    turnsing_90(false, true);
    drive_to_custom("k4", 'w', "k1", 'w', false);
    drive_smooth(30, 0, 360, false);
    drive_time(30, 0, 0.5, true);
    drive_smooth(-10, 0, 50, true);
    act_move(lifter, LIFTER_UP, true);
    drive_smooth(-10, 0, 100, true);
    act_move(lifter, LIFTER_BACK_BOAT_GRABBED, true);
    drive_smooth(10, 0, 120, true);
    act_move(lifter, LIFTER_UP, true);
    drive_smooth(-10, 0, 300, true);
    drive_to("k1", 'w', "k4", 'e');
    turn_90(true);
    linefollow_deg(50, 400, false);
    act_move_speed(lifter, 20, LIFTER_INIT, false);
    act_move(dropper, DROPPER_INIT, false);
    drive_smooth(10, -2, 520, true);
    drive_smooth(-10, -50, 15, true);
}

void inline collect_blocks_start() {
    turn_90(false);

    // stop actuatuors and init
    act_init(lifter);
    act_init(dropper);
    m_off(a, true);
    m_off(d, true);

    drive_smooth(30, 0, 360, false);
    drive_time(30, 0, 0.5, true);
    drive_smooth(-10, 0, 50, true);
    act_move(lifter, LIFTER_UP, true);
    drive_smooth(-10, 0, 100, true);
    act_move(lifter, LIFTER_BACK_BOAT_GRABBED, true);
    drive_smooth(10, 0, 120, true);
    act_move(lifter, LIFTER_UP, true);
    drive_smooth(-10, 0, 300, true);
    turn_180(false);
    drive_to("k1", 'e', "k4", 'e');
    turn_90(true);
    linefollow_deg(50, 400, false);
    act_move_speed(lifter, 20, LIFTER_INIT, false);
    act_move(dropper, DROPPER_INIT, false);
    drive_smooth(10, 0, 200, true);
    drive_smooth(-10, -50, 15, true);

    drive_smooth(-10, 0, 570, true);
    drive_to("k4", 'n', "s6", 'x');
}

void inline collect_containers_on_block_position() {
    drive_deg(10, 0, 100, true);
    turn_90(false);
    drive_deg(10, 0, 150, true);
    act_move(lifter, LIFTER_TREX_CONTAINER, true);
    drive_deg(-10, 0, 250, true);
    beep();
    drive_deg(10, -50, 250, true);
    drive_deg(10, 50, 250, true);
    act_move(lifter, LIFTER_INIT, true);
    drive_smooth(-10, 0, 130, true);
    turn_90(true);
    drive_deg(-10, 0, 50, true);
    lifter_collect(true);
    drive_deg(-10, 0, 170, true);
    lifter_collect(true);
    drive_deg(10, 0, 50, true);
    turn_90(true);
}

void inline place_containers_big_ship(bool boat_front, bool flag_left) {
    int pos3, pos4, pos5, pos6;
    if (boat_front) {
        if (flag_left) {
            pos3 = -10;
            pos4 = -110;
            pos5 = -210;
            pos6 = -310;
            
        } else {
            pos3 = -410;
            pos4 = -310;
            pos5 = -210;
            pos6 = -110;
        }
        act_move(lifter, LIFTER_BACK_BOAT_GRABBED, true);
        drive_smooth(-10, 0, 350, true);
        turnsing_90(false, true);
    } else {
        if (flag_left) {
            pos3 = 10;
            pos4 = 110;
            pos5 = 210;
            pos6 = 310;
        } else {
            pos3 = 410;
            pos4 = 310;
            pos5 = 210;
            pos6 = 110;
        }
        act_move(lifter, LIFTER_INIT, true);
        drive_smooth(10, 0, 300, true);
        turnsing_90(true, false);   
    }
    int pos_ships[7] = {0, 0, 0, pos3, pos4, pos5, pos6};
    init_drive_position();
    int target_pos = get_free_pos_ship(true);
    drive_position(pos_ships[target_pos]);
    drop_off(true, target_pos);
    target_pos = get_free_pos_ship(true);
    drive_position(pos_ships[target_pos]);
    drop_off(true, target_pos);
    target_pos = get_free_pos_ship(true);
    drive_position(pos_ships[target_pos]);
    drop_off(true, target_pos);
    target_pos = get_free_pos_ship(true);
    drive_position(pos_ships[target_pos]);
    drop_off(true, target_pos);

    drive_position(0);
    if (boat_front) {
        turnsing_90(true, false);
    } else {
        turnsing_90(false, true);
    }
}

void inline place_containers_small_ship(bool boat_front, bool flag_left) {
    int pos1, pos2;
    if (boat_front) {
        if (flag_left) {
            pos1 = -130;
            pos2 = -230;
            
        } else {
            pos1 = -150;
            pos2 = -250;
        }
        act_move(lifter, LIFTER_BACK_BOAT_GRABBED, true);
        drive_smooth(-10, 0, 350, true);
        turnsing_90(false, true);
    } else {
        if (flag_left) {
            pos1 = 130;
            pos2 = 230;
            
        } else {
            pos1 = 150;
            pos2 = 250;
        }
        act_move(lifter, LIFTER_INIT, true);
        drive_smooth(10, 0, 300, true);
        turnsing_90(true, false);   
    }
    int pos_ships[7] = {0, pos1, pos2, 0, 0, 0, 0};
    init_drive_position();
    int target_pos = get_free_pos_ship(false);
    drive_position(pos_ships[target_pos]);
    drop_off(true, target_pos);
    target_pos = get_free_pos_ship(false);
    drive_position(pos_ships[target_pos]);
    drop_off(true, target_pos);

    drive_position(0);
    if (boat_front) {
        turnsing_90(true, false);
    } else {
        turnsing_90(false, true);
    }
}

void inline collect_containers(bool standing_at_white) {
    linefollow_smooth(35, 100, false);
    linefollow_deg(30, 440, false);
    beep();
    linefollow_col_1(15, COL_LIGHT_BLUE_REF, false, false);
    linefollow_smooth(10, 26, true);
    beep();
    // collect white container
    wait(0.2);
    turn_90(true);
    wait_stand();
    wait(0.1);
    

    int pos1, pos2, pos3, pos4, pos5, pos6;
    pos1 = -90;
    pos2 = 90;
    pos3 = 855;
    pos4 = 1000;
    pos5 = 1150;
    pos6 = 1300;
    if (standing_at_white) {
        init_drive_position();
    } else {
        init_drive_position_with_deg(1075);
    }

    act_move(dropper, DROPPER_NORMAL, false);

    drive_position(pos5);
    lifter_collect(true);
    drive_position(pos4);
    lifter_collect(true);
    drive_position(pos6);
    lifter_collect(true);
    drive_position(pos1);
    lifter_collect(true);
    drive_position(pos2);
    lifter_collect(true);
    drive_position(pos3);
    lifter_collect(true);
}

void inline collect_and_scan_coloured_containers_in_order() {
    float value1, value2, value3, value4;
    char text[20];
    bool picked_up[4] = {false, false, false, false};
    int index = -1;

    drive_smooth_custom(10, 30, 30, 0, 50, DRIVE_ACC_FACTOR, DRIVE_DEACC_FACTOR, false, false, true);

    drive_col(30, 0, s1, COL_GREY_REF, false, false);

    // collect with simple scan
    // collect 1. coloured container
    drive_smooth(10, 0, 190, false);

    scans_containers[0] = simple_scan(&value1);
    drive_smooth(10, 0, 115, false);
    if ((index = check_if_char_in_array(needed_for_big_ship, BIG_SHIP_POS_COUNT, scans_containers[0])) >= 0) {
        off();
        lifter_collect(true);
        picked_up[0] = true;
        needed_for_big_ship[index] = 'x';
    }

    // collect 2. coloured container
    drive_smooth(10, 0, 40, false);
    // wait_center_press();
    scans_containers[1] = simple_scan(&value2);
    drive_smooth(10, 0, 110, false);
    if ((index = check_if_char_in_array(needed_for_big_ship, BIG_SHIP_POS_COUNT, scans_containers[1])) >= 0) {
        off();
        lifter_collect(true);
        picked_up[1] = true;
        needed_for_big_ship[index] = 'x';
    }

    // collect 3. coloured container
    drive_smooth(10, 0, 40, false);
    // wait_center_press();
    scans_containers[2] = simple_scan(&value3);
    drive_smooth(10, 0, 110, false);
    if ((index = check_if_char_in_array(needed_for_big_ship, BIG_SHIP_POS_COUNT, scans_containers[2])) >= 0) {
        off();
        lifter_collect(true);
        picked_up[2] = true;
        needed_for_big_ship[index] = 'x';
    }

    // scan 4. coloured container
    drive_smooth(10, 0, 40, false);
    // wait_center_press();
    scans_containers[3] = simple_scan(&value4);
    if ((index = check_if_char_in_array(needed_for_big_ship, BIG_SHIP_POS_COUNT, scans_containers[3])) >= 0) {
        drive_smooth(10, 0, 120, true);
        lifter_collect(true);
        picked_up[3] = true;
        needed_for_big_ship[index] = 'x';
    }

    int pos3 = 885;
    int pos4 = 1015;
    int pos5 = 1165;
    int pos6 = 1320;

    int positions[4] = {pos3, pos4, pos5, pos6};

    for (int i = 0; i <  4; ++i) {
        if (!picked_up[i]) {
            drive_position(positions[i]);
            lifter_collect(true);
        }
    }
    drive_position(positions[3]);

    sprintf(text, "%.2f;%c", value1, scans_containers[0]);
    display_set_text(2, text);
    sprintf(text, "%.2f;%c", value2, scans_containers[1]);
    display_set_text(3, text);
    sprintf(text, "%.2f;%c", value3, scans_containers[2]);
    display_set_text(4, text);
    sprintf(text, "%.2f;%c", value4, scans_containers[3]);
    display_set_text(5, text);
}

void inline place_containers_in_order() {
    wait_stand();
    init_drive_position();

    // drop off white container
    wait(0.2);
    int target_pos = get_free_pos_ship(true);
    drive_to_ship_position(target_pos);
    drop_off(true, target_pos);
    target_pos = get_free_pos_ship(true);
    drive_to_ship_position(target_pos);
    drop_off(true, target_pos);
    target_pos = get_free_pos_ship(true);
    drive_to_ship_position(target_pos);
    drop_off(true, target_pos);
    target_pos = get_free_pos_ship(false);
    drive_to_ship_position(target_pos);
    drop_off(true, target_pos);
    target_pos = get_free_pos_ship(false);
    drive_to_ship_position(target_pos);
    drop_off(false, target_pos);
    wait(0.2);
    act_move_speed(dropper, 100, DROPPER_INIT, true);

    // drive in finish if not already inside
    if (target_pos > 2) {
        drive_to_ship_position(7);
    }
}
