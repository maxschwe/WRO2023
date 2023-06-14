#include "lib/programs/second_day_test.h"

void inline second_day_test_func() {
    // drive backwards and scan
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
    drive_smooth(10, 0, 50, false);
    scans_blocks[0] = simple_scan(&value1);
    m_on(a, -2);
    m_on(d, -1);

    // drive backwards and drive to white containers
    drive_smooth(20, 0, 65, true);
    sprintf(text, "%.2f;%c", value1, scans_blocks[0]);
    display_set_text(0, text);
    sprintf(text, "%.2f;%c", value2, scans_blocks[1]);
    display_set_text(1, text);
    

    // collect green containers
    drive_deg(10, 0, 100, true);
    turn_90(false);
    drive_deg(10, 0, 150, true);
    act_move(lifter, LIFTER_TREX_CONTAINER, true);
    drive_deg(-15, 0, 250, true);
    beep();
    drive_deg(15, -50, 250, true);
    drive_deg(15, 50, 250, true);
    act_move(lifter, LIFTER_INIT, true);
    drive_smooth(-10, 0, 130, true);
    turn_90(true);
    drive_deg(-15, 0, 50, true);
    lifter_collect(true);
    drive_deg(-15, 0, 170, true);
    lifter_collect(true);
    drive_deg(10, 0, 50, true);
    turn_90(true);

    // collect ships
    drive_to("k1", 'e', "s4", 'x');
    linefollow_deg(10, 550, true);
    wait(0.2);
    turn_90(true);
    wait(0.2);
    drive_smooth(-10, 0, 300, true);
    act_move(lifter, LIFTER_BACK_BOAT_GRABBED, true);
    drive_smooth(10, 0, 800, true);
    act_move(lifter, LIFTER_FORWARD_BOAT_GRABBED, true);

    // drive to start area
    turnsing_90(true, true);
    drive_col(30, 0, s2, COL_WHITE_REF, false, false);
    drive_deg(30, 0, 30, false);
    drive_col(30, 0, s2, COL_BLACK_REF, true, true);
    drive_smooth(10, 0, 90, true);
    turn_line(false, true);
    linefollow_intersection(50, true);
    turn_90(true);
    drive_smooth(10, 0, 500, true);
    

    // place on small ship
    place_containers_small_ship(true, true);
    drive_smooth(-10, 0, 160, true);
    drive_to("k1", 's', "k3", 'w');
    drive_deg(20, -100, 20, true);
    act_move(lifter, LIFTER_INIT, true);
    drive_smooth(-10, 0, 300, true);
    drive_smooth(10, 0, 300, true);
    turn_90(false);
    act_move(lifter, LIFTER_INIT, false);

    // collect white containers
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
    drive_smooth(-10, 0, 90, true);
    lifter_collect(true);
    drive_smooth(10, 0, 180, true);

    float value3, value4; 
    // drive_smooth(10, 0, 90, true);

    lifter_collect(false);
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
    act_move_speed(lifter, 20, LIFTER_UP, true);
    act_move_speed(lifter, 20, LIFTER_INIT, true);

    // scan 4. coloured container
    drive_smooth(20, 0, 35, false);
    // wait_center_press();
    scans_containers[3] = simple_scan(&value4);
    drive_smooth(10, 0, 125, true);
    act_move_speed(lifter, 20, LIFTER_UP, true);
    act_move_speed(lifter, 20, LIFTER_INIT, true);

    sprintf(text, "%.2f;%c", value1, scans_containers[0]);
    display_set_text(2, text);
    sprintf(text, "%.2f;%c", value2, scans_containers[1]);
    display_set_text(3, text);
    sprintf(text, "%.2f;%c", value3, scans_containers[2]);
    display_set_text(4, text);
    sprintf(text, "%.2f;%c", value4, scans_containers[3]);
    display_set_text(5, text);


    drive_smooth(-10, 0, 220, true);
    drive_to_custom("s4", 'w', "k3", 'e', false);
    linefollow_deg(30, 200, false);
    act_move(lifter, LIFTER_FORWARD_BOAT_GRABBED, false);
    drive_to("k3", 'e', "k4", 's');

    linefollow_deg(20, 400, true);

    act_move(lifter, LIFTER_INIT, true);
    
    int pos3, pos4, pos5, pos6;
    if (true) {
        if (false) {
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
        act_move(lifter, LIFTER_INIT, true);
        drive_smooth(-10, 0, 350, true);
        turnsing_90(false, true);
    } else {
        if (false) {
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
    if (true) {
        turnsing_90(true, false);
    } else {
        turnsing_90(false, true);
    }

    act_move(lifter, LIFTER_INIT, false);
    drive_smooth(-10, 0, 300, true);
    turn_90(false);
    drive_time(-30, 0, 1.5, true);
    act_move(dropper, DROPPER_BODEN, true);
    act_move(dropper, DROPPER_NORMAL, true);
    drive_smooth(10, 0, 130, true);
    act_move(dropper, DROPPER_BODEN, true);
    act_move(dropper, DROPPER_NORMAL, false);
}