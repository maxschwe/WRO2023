#include "../../include/programs/run.h"
#include "../../include/all.h"

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

    float_array block_data = create_float_array(INITIAL_ARRAY_SIZE);
    drive_smooth_custom(-10, -30, 30, 0, 600, false, NULL);
    // drive forward and scan
    drive_smooth_custom(-30, -10, 35, 0, 260, true, NULL);

    beep();
    // finish_array(&block_data);

    m_on(a, -1);
    m_on(d, 2);

    // char col1, col2;
    // char block_array[4];
    // block_array = evaluate(&block_data, MOVING_AVERAGE_COUNT, HIGH_PASS_THRESHOLD, MAXIMA_THRESHOLD, MAXIMA_COUNT, COLOR_THRESHOLD, OUTPUT_PATH);

    // block_array[0] = 'g';
    // block_array[1] = 'g';
    // block_array[2] = 'g';
    // block_array[3] = 'g';
    // if (block_array[0] == block_array[1] && block_array[2] == block_array[3] && block_array[0] == block_array[2]) {
    //     scans_blocks[(block_array[0] == 'b') ? 0 : 1] = 2;
    //     col1 = block_array[0];
    //     col2 = col1;

    // } else {
    //     scans_blocks[0] = 1;
    //     scans_blocks[1] = 1;
    //     col1 = 'b';
    //     col2 = 'g';
    // }

    // char text[20] = "Cols: ";
    // char tmpstr[2];
    // tmpstr[0] = col1;
    // tmpstr[1] = 0;
    // strcat(text, tmpstr);
    // strcat(text, ", ");
    // tmpstr[0] = col2;
    // tmpstr[1] = 0;
    // strcat(text, tmpstr);
    scans_blocks[0] = 0;
    scans_blocks[1] = 2;

    // drive backwards and drive to white containers
    drive_smooth(25, 0, 160, true);
    wait(0.1);
    turn_line(true, true);
    wait(0.1);
    act_init(lifter);
    act_init(dropper);
    m_off(a, true);
    m_off(d, true);
    linefollow_smooth(100, 150, false);
    // stop actuatuors and init
    linefollow_intersection(100, false);
    linefollow_deg(100, 720, false);
    linefollow_intersection(100, true);
    // linefollow_deg_custom(100, 720, 0.3, 50, false);
    // linefollow_intersection_custom(50, 0.3, 40, true);
    act_move(dropper, DROPPER_NORMAL, false);
    wait(0.3);
    turn_line(true, true);

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

    linefollow_deg(25, 400, false);
    beep();
    linefollow_col_1(10, 22, false);
    drive_smooth_custom(10, 10, 10, 0, 20, true, NULL);
    beep();

    // collect white container
    wait(0.2);
    turn_90(true, true);
    wait_stand();
    wait(0.1);
    drive_smooth_custom(10, 10, 10, 0, 90, true, NULL);
    move_lifter_up(true);
    move_lifter_down(false);
    drive_smooth_custom(10, 30, 30, 0, 200, false, NULL);
    drive_col(30, 0, s3, GREY, false);
    drive_smooth(10, 0, 450, false);

    // collect 1. coloured container
    scans_container[0] = scan(50);
    drive_smooth(10, 0, 112, true);
    move_lifter_up(true);
    move_lifter_down(true);

    // collect 2. coloured container
    drive_smooth(10, 0, 20, false);
    scans_container[1] = scan(70);
    drive_smooth(10, 0, 125, true);
    move_lifter_up(true);
    move_lifter_down(true);
    drive_smooth(10, 0, 20, false);

    // collect 3. coloured container
    scans_container[2] = scan(90);
    drive_smooth(10, 0, 125, true);
    move_lifter_up(true);
    move_lifter_down(true);
    drive_smooth(10, 0, 20, false);

    // scan 4. coloured container
    scans_container[3] = scan(110);
    drive_smooth(10, 0, 130, true);
    move_lifter_up(true);
    move_lifter_down(true);
    // act_move_speed(lifter, 10, LIFTER_UP, true);
    // act_move_speed(lifter, 5, LIFTER_INIT, true);

    // drive forward and take big ship
    act_move_speed(lifter, 15, LIFTER_INIT, false);

    on(20, 0);
    col_wait_ref(s1, 'b');
    // drive_smooth(10, 0, 100, true);

    drive_smooth(10, 0, 300, true);
    turn_90(true, true);
    on(-30, 0);
    wait(0.8);
    off(true);
    drive_smooth(10, 0, 350, true);
    turn_90(false, true);
    drive_smooth(10, 0, 250, true);
    // drive_smooth(10, -50, 220, true);
    // drive_smooth(10, 50, 220, true);
    // drive_smooth(10, 0, 245, true);
    act_move(lifter, LIFTER_UP, true);

    wait(0.3);

    // move backwards and drive to small ship
    drive_deg(-40, -40, 0, 300, false);
    on(-40, 0);
    while (col_get_ref(s2) < 35) {
    }
    drive_deg(-40, -10, 0, 330, true);
    turn_90(true, true);
    linefollow_deg(40, 300, false);
    linefollow_col_1_greater(40, 40, false);
    linefollow_col_1(40, 30, false);
    linefollow_deg(15, 370, true);
    turn_180(true, true);

    // collect small ship
    act_move(lifter, LIFTER_INIT, true);
    drive_smooth(-15, 0, 430, true);
    act_move_speed(lifter, 80, LIFTER_BACK_BOAT_GRABBED, true);
    off(true);

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
    turn_90(false, true);
    linefollow_smooth(50, 770, true);

    // drive again red container
    // drive_deg(-10, -60, 0, 200, false);
    // drive_deg(-60, -10, 0, 200, true);
    // wait(0.3);
    // drive_deg(10, 40, 0, 200, false);
    // drive_deg(40, 10, 0, 150, true);

    // place big ship
    wait_stand();
    drive_smooth(-15, 0, 800, true);
    wait_stand();
    drive_smooth(15, -50, 630, true);
    act_move_speed(lifter, 80, LIFTER_BACK_BOAT_GRABBED, false);
    drive_smooth(20, 0, 150, true);
    drive_smooth(-20, 0, 200, true);

    // place small ship
    drive_smooth(-15, -50, 630, true);
    drive_smooth(-15, 0, 30, true);
    drive_smooth(-15, -50, 630, true);
    act_move_speed(lifter, 30, LIFTER_INIT, true);
    drive_smooth(-30, 0, 100, false);
    on(-30, 0);
    wait(0.5);
    off(true);
    drive_smooth(10, 0, 310, true);
    wait_stand();
    drive_smooth(-10, 50, 630, true);

    place_containers_on_ships(scans_blocks, scans_container);

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
    // turn_90(true, true);
    // drive_deg(-15, -15, 0, 90, true);
    // move_lifter_up(true);
    // move_lifter_down(true);
    // drive_deg(15, 15, 0, 90, true);
    // turn_90(true, true);
    // linefollow_deg(20, 200, false);
    // linefollow_intersection(70, true);
    // turn_90(true, true);
    // linefollow_deg(20, 200, false);
    // linefollow_intersection(70, true);
}