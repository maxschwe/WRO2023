#include "../../include/programs/run.h"

#define SCAN_VAL_COUNT 2
#define NOT_TAKEN_POSITIONS 2

int taken_blocks = 0;
char val[SCAN_VAL_COUNT] = { 'n', 'n' };
int not_taken_positions[NOT_TAKEN_POSITIONS] = { 0, 0 };

bool check_if_in_array(char c)
{
    for (int i = 0; i < SCAN_VAL_COUNT; ++i) {
        if (val[i] == c) {
            return true;
        }
    }
    return false;
}

void rm_from_array(char c)
{
    for (int i = SCAN_VAL_COUNT - 1; i >= 0; --i) {
        if (val[i] == c) {
            val[i] = 'n';
            break;
        }
    }
}

void drop_off()
{
    act_move(dropper, DROPPER_DROPPED, true);
    wait(0.2);
    act_move(dropper, DROPPER_NORMAL, true);
}

void run()
{
    // init actuators
    m_on(a, -1);
    m_on(d, -1);

    // drive forward and scan
    drive_deg(-20, -40, 0, 350, false);
    beep();
    drive_col(-40, 0, s1, BLACK, false);
    drive_deg(-40, -30, 0, 180, false);
    drive_deg(-30, -30, 0, 170, true);
    beep();
    val[0] = scan(10);
    drive_deg(-30, -10, 0, 120, true);
    val[1] = scan(30);

    // stop actuatuors and init
    act_init(lifter);
    act_init(dropper);
    m_off(a, true);
    m_off(d, true);

    // drive backwards and drive to white containers
    drive_deg(10, 40, 0, 150, true);
    turn_line(true, true);
    wait(0.2);
    linefollow_slow(20, 150, false);
    linefollow_intersection(100, false);
    linefollow_intersection(100, true);
    act_move(dropper, DROPPER_NORMAL, false);
    wait(0.2);
    turn_line(true, true);

    // slow approach to white containers
    wait(0.2);
    linefollow_slow(20, 500, false);
    beep();
    linefollow_col_1(10, 18, false);
    drive_deg(10, 10, 0, 10, true);
    beep();
    wait(0.4);

    // grab white container
    turn_90(true, true);
    wait(0.4);
    drive_deg(10, 10, 0, 90, true);
    move_up(true);
    move_down(true);
    drive_deg(10, 30, 0, 100, false);
    drive_deg(30, 30, 0, 100, false);
    drive_col(30, 0, s3, GREY, false);
    drive_deg(30, 30, 0, 460, true);

    // scan 1. coloured container
    char pos1 = scan(50);
    drive_deg(10, 10, 0, 120, false);
    if (check_if_in_array(pos1)) {
        off(true);
        rm_from_array(pos1);
        move_up(true);
        move_down(true);
        wait(0.5);
        ++taken_blocks;
    } else {
        not_taken_positions[0] = 1;
    }

    // scan 2. coloured container
    drive_deg(10, 10, 0, 20, false);
    on(10, 0);
    char pos2 = scan(70);
    drive_deg(10, 10, 0, 130, false);
    if (check_if_in_array(pos2)) {
        off(true);
        beep();
        rm_from_array(pos2);
        move_up(true);
        move_down(true);
        wait(0.5);
        ++taken_blocks;
    } else {
        if (not_taken_positions[0] == 0) {
            not_taken_positions[0] = 2;
        } else {
            not_taken_positions[1] = 2;
        }
    }

    // scan 3. coloured container
    drive_deg(10, 20, 0, 20, false);
    on(20, 0);
    char pos3 = scan(90);
    drive_deg(20, 10, 0, 130, false);
    if (check_if_in_array(pos3) || taken_blocks == 2) {
        off(true);
        rm_from_array(pos3);
        move_up(true);
        move_down(true);
        wait(0.5);
        ++taken_blocks;
    } else {
        if (not_taken_positions[0] == 0) {
            not_taken_positions[0] = 3;
        } else {
            not_taken_positions[1] = 3;
        }
    }

    // scan 4. coloured container
    drive_deg(10, 20, 0, 20, false);
    on(20, 0);
    char pos4 = scan(110);
    drive_deg(20, 10, 0, 130, false);
    int last_position = 4;
    if (check_if_in_array(pos4) || taken_blocks >= 2) {
        off(true);
        rm_from_array(pos4);
        move_up(true);
        move_down(true);
        wait(0.5);
        ++taken_blocks;
    } else {
        if (not_taken_positions[0] == 0) {
            not_taken_positions[0] = 4;
        } else {
            not_taken_positions[1] = 4;
        }
    }

    // collect missing containers
    if (not_taken_positions[0] == 1) {
        drive_deg(-20, -20, 0, -450, true);
        move_up(true);
        move_down(true);
        last_position = 1;
        if (not_taken_positions[1] == 2) {
            drive_deg(20, 20, 0, 150, true);
            move_up(true);
            move_down(true);
            last_position = 2;
        } else if (not_taken_positions[1] == 3) {
            drive_deg(20, 20, 0, 300, true);
            move_up(true);
            move_down(true);
            last_position = 3;
        } else if (not_taken_positions[1] == 4) {
            drive_deg(20, 20, 0, 450, true);
            move_up(true);
            move_down(true);
            last_position = 4;
        }
    } else if (not_taken_positions[0] == 2) {
        drive_deg(-20, -20, 0, 300, true);
        move_up(true);
        move_down(true);
        last_position = 2;
        if (not_taken_positions[1] == 3) {
            drive_deg(20, 20, 0, 150, true);
            move_up(true);
            move_down(true);
            last_position = 3;
        } else if (not_taken_positions[1] == 4) {
            drive_deg(20, 20, 0, 300, true);
            move_up(true);
            move_down(true);
            last_position = 4;
        }
    } else if (not_taken_positions[0] == 3) {
        drive_deg(-20, -20, 0, 150, true);
        move_up(true);
        move_down(true);
        last_position = 3;
        if (not_taken_positions[1] == 4) {
            drive_deg(20, 20, 0, 150, true);
            move_up(true);
            move_down(true);
            last_position = 4;
        }
    }
    if (last_position == 1) {
        drive_deg(20, 20, 0, 270, false);
    } else if (last_position == 2) {
        drive_deg(20, 20, 0, 120, false);
    }

    // drive forward and take big ship
    on(20, 0);
    col_wait_ref(s1, 'b');
    drive_deg(20, 20, 1, 140, false);
    drive_deg(20, 20, 1, 220, false);
    drive_deg(20, 20, 1, 110, true);
    drive_deg(20, 20, -50, 130, true);
    drive_deg(20, 5, 50, 130, true);
    act_move(lifter, LIFTER_UP, true);

    wait(0.5);

    // move backwards and drive to small ship
    drive_deg(-20, -40, 4, 150, false);
    on(-40, 0);
    while (col_get_ref(s2) < 28) {
    }
    drive_deg(-40, -10, 0, 330, true);
    wait(0.3);
    turn_90(true, true);
    wait(0.3);
    linefollow_slow(20, 300, false);
    linefollow_col_1_greater(10, 40, false);
    linefollow_col_1(10, 30, false);
    linefollow_slow(10, 350, true);
    wait(0.3);
    turn_90(true, false);
    turn_90(true, true);

    // collect small ship
    act_move(lifter, LIFTER_INIT, true);
    wait(0.3);
    drive_deg(-10, -30, 0, 100, false);
    drive_deg(-30, -10, 0, 300, false);
    on(-10, 0);
    act_move_speed(lifter, 80, LIFTER_BACK_BOAT_GRABBED, true);
    wait(0.5);
    off(true);
    // drive_deg(-30, -10, 0, 70, true);
    // drive_deg(-20, -20, 50, 100, true);
    // drive_deg(-20, -20, -50, 100, true);

    // drive to open sea and drop read container
    linefollow_slow(20, 200, false);
    linefollow_intersection(20, false);
    act_move_speed(lifter, 80, LIFTER_UP, false);
    on(10, 20);
    m_wait_deg(b, 130);
    off(true);
    wait(0.5);
    turn_90(false, true);
    wait(0.3);
    linefollow_slow(20, 500, false);
    linefollow_intersection(100, false);
    linefollow_intersection(100, true);
    wait(0.3);
    turn_line(false, true);
    wait(0.3);
    linefollow_slow(30, 800, false);
    drive_deg(-10, -60, 0, 200, false);
    drive_deg(-60, -10, 0, 200, true);
    wait(0.3);
    drive_deg(10, 40, 0, 200, false);
    drive_deg(40, 10, 0, 150, true);

    // place big ship
    drive_deg(-10, -60, 0, 300, false);
    drive_deg(-60, -10, 0, 500, true);
    wait(0.3);
    drive_deg(10, 40, -50, 150, false);
    drive_deg(40, 40, -50, 330, false);
    drive_deg(40, 10, -50, 150, true);
    act_move(lifter, LIFTER_BACK_BOAT_GRABBED, true);
    drive_deg(30, 30, 0, 150, true);
    drive_deg(-30, -30, 0, 150, false);
    drive_deg(-30, -30, 0, 150, true);

    // place small ship
    drive_deg(-10, -40, -50, 150, false);
    drive_deg(-40, -40, -50, 330, false);
    drive_deg(-40, -10, -50, 150, true);
    wait(0.3);
    drive_deg(-10, -10, 0, 50, true);
    wait(0.3);
    drive_deg(-10, -40, -50, 150, false);
    drive_deg(-40, -40, -50, 360, false);
    drive_deg(-40, -10, -50, 150, true);
    act_move(lifter, LIFTER_INIT, true);
    drive_deg(-20, -20, 0, 200, false);
    on(-20, 0);
    wait(0.5);
    off(true);
    drive_deg(20, 20, 0, 320, true);
    drive_deg(-10, -30, 50, 150, false);
    drive_deg(-30, -30, 50, 330, false);
    drive_deg(-30, -10, 50, 150, true);
    drive_deg(10, 40, 0, 150, false);
    drive_deg(40, 40, 0, 450, false);
    drive_deg(40, 10, 0, 150, true);

    // drop of the containers
    drop_off();
    drive_deg(-15, -15, 0, 90, true);
    drop_off();
    drive_deg(-15, -15, 0, 90, true);
    drop_off();
    drive_deg(-15, -15, 0, 310, true);
    drop_off();
    drive_deg(-15, -15, 0, 80, true);
    drop_off();
}