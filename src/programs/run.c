#include "../../include/programs/run.h"

int scans_blocks[BLOCK_COL_COUNT];
char scans_container[COLOURED_CONTAINER_COUNT];

void init_arrays()
{
    for (int i = 0; i < BLOCK_COL_COUNT; ++i) {
        scans_blocks[i] = 0;
    }

    for (int i = 0; i < COLOURED_CONTAINER_COUNT; ++i) {
        scans_container[i] = 'n';
    }
}

void run()
{
    init_arrays();
    col_get_rgb(s4);
    // init actuators

    // drive forward and scan
    drive_deg(-20, -40, 0, 200, false);
    drive_deg(-40, -40, 0, 440, false);
    drive_deg(-40, -40, 0, 100, false);
    char scan_1 = scan(10);
    if (scan_1 == 'b') {
        scans_blocks[0] += 1;
    } else {
        scans_blocks[1] += 1;
    }
    drive_deg(-40, -10, 0, 120, true);
    char scan_2 = scan(30);
    if (scan_2 == 'b') {
        scans_blocks[0] += 1;
    } else {
        scans_blocks[1] += 1;
    }
    m_on(a, -1);
    m_on(d, -1);
    // wait_center_press();

    // drive backwards and drive to white containers
    drive_deg(20, 40, 0, 150, true);
    turn_line(true, true);
    wait(0.2);
    act_init(lifter);
    act_init(dropper);
    m_off(a, true);
    m_off(d, true);
    linefollow_slow(20, 150, false);
    // stop actuatuors and init
    linefollow_intersection(100, false);
    linefollow_deg_custom(100, 720, 0.3, 50, false);
    linefollow_intersection_custom(60, 0.3, 40, true);
    act_move(dropper, DROPPER_NORMAL, false);
    wait(0.2);
    turn_line(true, true);

    // slow approach to white containers
    wait(0.2);
    linefollow_slow(20, 500, false);
    beep();
    linefollow_col_1(10, 18, false);
    drive_deg(10, 10, 0, 20, true);
    beep();
    wait(0.4);

    // grab white container
    turn_90(true, true);
    wait(0.4);
    drive_deg(15, 15, 0, 90, true);
    move_up(true);
    move_down(false);
    drive_deg(15, 40, 0, 100, false);
    drive_deg(40, 40, 0, 100, false);
    drive_col(40, 0, s3, GREY, false);
    drive_deg(40, 40, 0, 260, false);
    drive_deg(40, 20, 0, 200, false);

    scans_container[0] = scan(50);
    drive_deg(15, 15, 0, 112, true);
    move_up(true);
    move_down(true);

    drive_deg(15, 15, 0, 20, false);
    scans_container[1] = scan(70);
    drive_deg(15, 15, 0, 120, true);
    move_up(true);
    move_down(true);
    drive_deg(15, 15, 0, 20, false);

    // collect 3. coloured container
    scans_container[2] = scan(90);
    drive_deg(15, 15, 0, 120, true);
    move_up(true);
    move_down(true);
    drive_deg(15, 15, 0, 20, false);

    // scan 4. coloured container
    scans_container[3] = scan(110);
    drive_deg(15, 15, 0, 130, true);
    move_up(true);
    move_down(true);

    // drive forward and take big ship
    act_move(lifter, LIFTER_GRABBED, false);

    on(20, 0);
    col_wait_ref(s1, 'b');
    drive_deg(30, 30, 1, 140, false);
    drive_deg(30, 30, 1, 150, false);
    drive_deg(30, 30, 1, 110, true);
    drive_deg(30, 30, -50, 210, true);
    drive_deg(30, 5, 50, 130, false);
    drive_deg(30, 5, 50, 80, true);
    act_move(lifter, LIFTER_UP, false);
    drive_deg(20, 5, 0, 100, true);

    wait(0.3);

    // move backwards and drive to small ship
    drive_deg(-20, -40, 0, 250, false);
    on(-40, 0);
    while (col_get_ref(s2) < 35) {
    }
    drive_deg(-40, -10, 0, 330, true);
    wait(0.1);
    turn_90(true, true);
    wait(0.1);
    linefollow_slow(30, 300, false);
    linefollow_col_1_greater(10, 40, false);
    linefollow_col_1(10, 30, false);
    linefollow_slow(10, 370, true);
    wait(0.3);
    drive_deg(10, 20, -100, 140, false);
    drive_deg(20, 20, -100, 315, false);
    drive_deg(20, 10, -100, 172, true);

    // collect small ship
    act_move(lifter, LIFTER_GRABBED, true);
    drive_deg(-10, -30, 0, 100, false);
    drive_deg(-30, -5, 0, 300, true);
    act_move_speed(lifter, 80, LIFTER_BACK_BOAT_GRABBED, true);
    off(true);
    // drive_deg(-30, -10, 0, 70, true);
    // drive_deg(-20, -20, 50, 100, true);
    // drive_deg(-20, -20, -50, 100, true);

    // drive to open sea and drop read container
    linefollow_slow(20, 200, false);
    drive_deg(20, 20, 10, 370, true);
    act_move_speed(lifter, 60, LIFTER_UP, false);
    drive_deg(20, 20, 10, 60, true);
    wait(0.5);
    turn_line(false, true);
    wait(0.3);
    linefollow_slow(20, 500, false);
    linefollow_intersection(100, false);
    linefollow_intersection(100, true);
    wait(0.2);
    turn_line(false, true);
    wait(0.1);
    linefollow_slow(30, 800, false);

    // drive again red container
    // drive_deg(-10, -60, 0, 200, false);
    // drive_deg(-60, -10, 0, 200, true);
    // wait(0.3);
    // drive_deg(10, 40, 0, 200, false);
    // drive_deg(40, 10, 0, 150, true);

    // place big ship
    drive_deg(-10, -60, 0, 300, false);
    drive_deg(-60, -10, 0, 500, true);
    wait(0.2);
    drive_deg(10, 60, -50, 150, false);
    drive_deg(60, 60, -50, 330, false);
    drive_deg(60, 10, -50, 150, true);
    act_move_speed(lifter, 80, LIFTER_BACK_BOAT_GRABBED, false);
    drive_deg(30, 30, 0, 150, true);
    drive_deg(-20, -50, 0, 100, false);
    drive_deg(-50, -20, 0, 100, true);

    // place small ship
    wait(0.2);
    drive_deg(-10, -60, -50, 150, false);
    drive_deg(-60, -60, -50, 330, false);
    drive_deg(-60, -10, -50, 150, true);
    wait(0.3);
    drive_deg(-10, -10, 0, 50, true);
    wait(0.3);
    drive_deg(-10, -60, -50, 150, false);
    drive_deg(-60, -60, -50, 330, false);
    drive_deg(-60, -10, -50, 150, true);
    act_move(lifter, LIFTER_INIT, true);
    drive_deg(-30, -30, 0, 100, false);
    on(-30, 0);
    wait(0.5);
    off(true);
    drive_deg(30, 30, 0, 320, true);
    wait(0.3);
    drive_deg(-10, -40, 50, 150, false);
    drive_deg(-40, -40, 50, 310, false);
    drive_deg(-40, -10, 50, 150, true);

    place_containers_on_ships(scans_blocks, scans_container);
}