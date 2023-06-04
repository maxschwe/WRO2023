#include "lib/programs/run.h"

void run()
{
    init_complex_scan();
    drive_smooth_custom(-10, -30, 30, 0, 600, false, false);
    drive_smooth_custom(-30, -10, 35, 0, 260, true, true);
    beep();

    scans_blocks = evaluate_complex_scan(BLOCKS_COUNT, SCANS_BLOCKS_FILEPATH);

    display_set_text(0, scans_blocks[0] == 'b' ? "blue" : "green");
    display_set_text(1, scans_blocks[1] == 'b' ? "blue" : "green");

    for (int i = 0; i < BLOCKS_COUNT; ++i) {
        if (scans_blocks[i] == 'b') {
            ++blocks_col_counts[0];
        } else {
            ++blocks_col_counts[1];
        }
    }

    error_beep();
    // wait_center_press();

    m_on(a, -2);
    m_on(d, -1);

    // drive backwards and drive to white containers
    drive_smooth(15, 0, 160, true);
    turn_90(true);

    // stop actuatuors and init
    act_init(lifter);
    act_init(dropper);
    m_off(a, true);
    m_off(d, true);

    linefollow_smooth(100, 150, false);
    linefollow_intersection(100, false);
    linefollow_deg(100, 720, false);
    linefollow_intersection(100, true);

    act_move(dropper, DROPPER_NORMAL, false);

    wait(0.2);
    turn_90(true);

    // surprise rule: drop off boje in untiefe
    // slow approach to white containers
    // wait(0.2);
    // linefollow_deg(10, 380, true);
    // wait(0.3);
    // drive_deg(10, 20, -100, 140, false);
    // drive_deg(20, 20, -100, 315, false);
    // drive_deg(20, 10, -100, 172, true);
    // act_move(dropper, DROPPER_BODEN, true);
    // wait(0.2);
    // act_move(dropper, DROPPER_NORMAL, true);
    // linefollow_intersection(10, true);
    // wait(0.3);
    // drive_deg(10, 20, -100, 140, false);
    // drive_deg(20, 20, -100, 315, false);
    // drive_deg(20, 10, -100, 172, true);
    // wait(0.3);

    linefollow_smooth(35, 100, false);
    linefollow_deg(30, 300, false);
    beep();
    linefollow_col_1(15, COL_LIGHT_BLUE_REF, false, false);
    linefollow_smooth(10, 26, true);
    beep();

    // collect white container
    wait(0.2);
    turn_90(true);
    wait_stand();
    wait(0.1);
    init_complex_scan();
    drive_smooth(10, 0, 90, true);
    move_lifter_up(true);
    move_lifter_down(false);
    drive_smooth_custom(10, 30, 30, 0, 200, false, false);
    drive_col(30, 0, s1, COL_GREY_REF, false, false);
    beep();

    // collect with complex scan
    // collect 1. coloured container

    drive_smooth(10, 0, 140, false);
    // wait_center_press();
    drive_smooth_custom(10, 10, DRIVE_MAX_SPEED, 0, 155, true, true);
    collect_lifter(true);

    // collect 2. coloured container
    drive_smooth_custom(10, 10, DRIVE_MAX_SPEED, 0, 145, true, true);
    collect_lifter(true);

    // collect 3. coloured container
    drive_smooth_custom(10, 10, DRIVE_MAX_SPEED, 0, 145, true, true);
    collect_lifter(true);

    // scan 4. coloured container
    drive_smooth_custom(10, 10, DRIVE_MAX_SPEED, 0, 170, true, true);
    collect_lifter(false);

    scans_containers = evaluate_complex_scan(COLOURED_CONTAINER_COUNT, SCANS_CONTAINERS_FILEPATH);

    display_set_text(2, scans_containers[0] == 'b' ? "blue" : "green");
    display_set_text(3, scans_containers[1] == 'b' ? "blue" : "green");
    display_set_text(4, scans_containers[2] == 'b' ? "blue" : "green");
    display_set_text(5, scans_containers[3] == 'b' ? "blue" : "green");
    // collect with simple scan
    // // collect 1. coloured container
    // drive_smooth(10, 0, 460, false);
    // // wait_center_press();
    // scans_containers[0] = simple_scan();
    // drive_smooth(10, 0, 105, true);
    // move_lifter_up(true);
    // move_lifter_down(true);

    // // collect 2. coloured container
    // drive_smooth(10, 0, 40, false);
    // // wait_center_press();
    // scans_containers[1] = simple_scan();
    // drive_smooth(10, 0, 105, true);
    // move_lifter_up(true);
    // move_lifter_down(true);

    // // collect 3. coloured container
    // drive_smooth(10, 0, 40, false);
    // // wait_center_press();
    // scans_containers[2] = simple_scan();
    // drive_smooth(10, 0, 105, true);
    // move_lifter_up(true);
    // move_lifter_down(true);

    // // scan 4. coloured container
    // drive_smooth(10, 0, 40, false);
    // // wait_center_press();
    // scans_containers[3] = simple_scan();
    // drive_smooth(10, 0, 130, true);
    // move_lifter_up(true);
    // move_lifter_down(false);
    // act_move_speed(lifter, 10, LIFTER_UP, true);
    // act_move_speed(lifter, 5, LIFTER_INIT, true);

    // drive forward and take big ship

    drive_col(20, 0, s1, COL_GREY_REF, true, false);
    // drive_smooth(10, 0, 100, true);

    drive_smooth(10, 0, 300, true);
    turn_90(true);
    drive_time(-30, 0, 0.8, true);
    drive_smooth(10, 0, 360, true);
    turn_90(false);
    drive_smooth(10, 0, 220, true);
    // drive_smooth(10, -50, 220, true);
    // drive_smooth(10, 50, 220, true);
    // drive_smooth(10, 0, 245, true);
    act_move(lifter, LIFTER_UP, true);

    wait(0.3);

    // move backwards and drive to small ship
    drive_smooth(-60, 0, 300, false);
    on(-60, 0);
    while (col_get_ref(s1) < COL_GREY_REF && col_get_ref(s2) < COL_GREY_REF && col_get_ref(s3) < COL_GREY_REF) {
    }
    drive_smooth(-10, 0, 330, true);
    turn_90(true);
    linefollow_deg(40, 300, false);
    linefollow_col_1(40, COL_BLACK_REF, false, false);
    linefollow_deg(40, 20, false);
    linefollow_col_1(40, COL_BLACK_REF, true, false);
    beep();
    linefollow_deg(40, 220, false);
    linefollow_smooth(10, 100, true);
    turn_180(true);

    // collect small ship
    act_move(lifter, LIFTER_INIT, true);
    drive_smooth(-15, 0, 430, true);
    act_move_speed(lifter, 80, LIFTER_BACK_BOAT_GRABBED, true);
    wait(0.3);

    // drive to open sea and drop read container
    linefollow_deg(30, 200, false);
    drive_smooth(15, 10, 410, true);
    act_move_speed(lifter, 60, LIFTER_UP, false);
    drive_smooth(10, 10, 60, true);
    wait_stand();
    turn_line(false, true);
    wait_stand();
    linefollow_smooth(100, 200, false);
    linefollow_intersection(100, false);
    linefollow_intersection(100, true);
    turn_90(false);
    linefollow_smooth(50, 770, true);

    // drive again red container
    // drive_deg(-10, -60, 0, 200, false);
    // drive_deg(-60, -10, 0, 200, true);
    // wait(0.3);
    // drive_deg(10, 40, 0, 200, false);
    // drive_deg(40, 10, 0, 150, true);

    // place big ship
    wait_stand();
    drive_smooth(-10, 0, 800, true);
    wait_stand();
    drive_smooth(10, -50, 630, true);
    act_move_speed(lifter, 80, LIFTER_BACK_BOAT_GRABBED, false);
    drive_smooth(20, 0, 150, true);
    drive_smooth(-20, 0, 200, true);

    // place small ship
    drive_smooth(-15, -50, 630, true);
    drive_smooth(-15, 0, 30, true);
    drive_smooth(-15, -50, 630, true);
    act_move_speed(lifter, 80, LIFTER_INIT, false);
    drive_smooth(-30, 0, 100, false);
    drive_time(-30, 0, 0.5, true);
    drive_smooth(10, 0, 310, true);
    wait_stand();
    drive_smooth(-10, 50, 630, true);

    place_containers_on_ships();

    // surprise rule: take next white block
    // drive back to line
    // drive_to_ship_position(8);
    // drive_deg(10, 40, 50, 150, false);
    // drive_deg(40, 40, 50, 305, false);
    // drive_deg(40, 10, 50, 150, true);
    // linefollow_deg(10, 500, false);

    // linefollow_intersection(70, true);
    // wait(0.2);
    // turn_line(false, true);

    // // slow approach to white containers
    // wait(0.2);
    // linefollow_deg(20, 500, false);
    // beep();
    // linefollow_col_1(10, 18, false);
    // drive_deg(10, 10, 0, 20, true);
    // beep();
    // wait(0.4);

    // // grab white container
    // turn_90(true);
    // drive_deg(-15, -15, 0, 90, true);
    // move_lifter_up(true);
    // move_lifter_down(true);
    // drive_deg(15, 15, 0, 90, true);
    // turn_90(true);
    // linefollow_deg(20, 200, false);
    // linefollow_intersection(70, true);
    // turn_90(true);
    // linefollow_deg(20, 200, false);
    // linefollow_intersection(70, true);
}