#include "run.h"

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

void run()
{
    drive_deg(-20, -40, 0, 350, false);
    beep();
    drive_col(-40, 0, s1, BLACK, false);
    drive_deg(-40, -30, 0, 180, false);
    drive_deg(-30, -30, 0, 170, true);
    beep();
    val[0] = scan(10);
    drive_deg(-30, -10, 0, 100, true);
    val[1] = scan(30);
    drive_deg(10, 40, 0, 170, true);
    turn_line(true, true);
    wait(0.2);
    linefollow_slow(20, 300, false);
    linefollow_intersection(100, false);
    linefollow_intersection(100, true);
    wait(0.2);
    turn_line(true, true);

    wait(0.2);
    linefollow_slow(20, 500, false);
    beep();
    linefollow_col_1(10, 18, false);
    drive_deg(10, 10, 0, 5, true);

    beep();

    wait(0.4);
    turn_90(true, true);
    wait(0.4);
    drive_deg(20, 10, 0, 90, true);
    move_up(true);
    move_down(false);
    drive_deg(10, 30, 0, 100, false);
    drive_deg(30, 30, 0, 100, false);
    drive_col(30, 0, s3, GREY, false);
    drive_deg(30, 30, 0, 460, true);

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
    // ev3_motor_rotate(d.port, -50, 20, false);
    if (last_position == 1) {
        drive_deg(20, 20, 0, 270, false);
    } else if (last_position == 2) {
        drive_deg(20, 20, 0, 120, false);
    }
    on(20, 0);
    col_wait_ref(s1, 'b');
    drive_deg(20, 20, 1, 140, false);
    drive_deg(20, 20, 1, 200, false);
    drive_deg(20, 20, 1, 110, true);
    drive_deg(20, 20, -50, 150, true);
    drive_deg(20, 20, 50, 150, true);

    ev3_motor_rotate(d.port, -120, 20, true);
    drive_deg(-20, -40, 0, 300, true);
    wait(0.3);
    drive_deg(-20, -20, 70, 400, true);
    drive_deg(20, 80, 0, 200, true);
    drive_col(80, 0, s3, WHITE, false);
    drive_deg(80, 80, 0, 30, false);
    drive_col(60, 30, s3, BLACK, false);
    drive_deg(60, 30, 0, 100, true);
    wait(0.3);
    turn_line(true, true);
    wait(0.3);
    linefollow_slow(20, 300, false);
    linefollow_intersection(90, true);
    wait(0.3);
    turn_line(true, true);
    wait(0.3);
    linefollow_slow(20, 300, true);
    ev3_motor_rotate(d.port, 50, 20, false);
    wait(0.3);
    drive_deg(-10, -40, 0, 300, false);
    drive_deg(-40, -40, 0, 300, false);
    drive_deg(-40, -10, 0, 300, true);
    ev3_motor_rotate(d.port, -45, 40, true);
    linefollow_slow(20, 300, false);
    linefollow_intersection(100, true);
    wait(0.5);
    turn_line(false, true);
    linefollow_slow(20, 600, false);
    linefollow_intersection(100, false);
    linefollow_intersection(100, true);
    wait(0.3);
    turn_line(false, true);
    wait(0.3);
    linefollow_slow(30, 800, true);
    drive_deg(-10, -60, 0, 300, false);
    drive_deg(-60, -10, 0, 500, true);
    wait(0.3);
    drive_deg(10, 40, -50, 150, false);
    drive_deg(40, 40, -50, 330, false);
    drive_deg(40, 10, -50, 150, true);
    ev3_motor_rotate(d.port, 100, 60, false);
    drive_deg(30, 30, 0, 150, true);
    drive_deg(-30, -30, 0, 150, false);
    ev3_motor_rotate(d.port, -100, 60, false);
    drive_deg(-30, -30, 0, 150, true);

    drive_deg(-10, -40, -50, 150, false);
    drive_deg(-40, -40, -50, 330, false);
    drive_deg(-40, -10, -50, 150, true);
    drive_deg(-30, -30, 0, 50, true);
    drive_deg(-10, -40, -50, 150, false);
    drive_deg(-40, -40, -50, 360, false);
    drive_deg(-40, -10, -50, 150, true);
    ev3_motor_rotate(d.port, 150, 60, false);
    drive_deg(-20, -20, 0, 330, true);
    drive_deg(20, 20, 0, 320, true);
    drive_deg(-10, -40, 50, 150, false);
    drive_deg(-40, -40, 50, 330, false);
    drive_deg(-40, -10, 50, 150, true);
    drive_deg(10, 40, 0, 150, false);
    drive_deg(40, 40, 0, 480, false);
    drive_deg(40, 10, 0, 150, true);

    ev3_motor_rotate(a.port, 130, 20, true);
    wait(0.2);
    ev3_motor_rotate(a.port, -130, 20, true);
    drive_deg(-15, -15, 0, 90, true);
    ev3_motor_rotate(a.port, 130, 20, true);
    wait(0.2);
    ev3_motor_rotate(a.port, -130, 20, true);
    drive_deg(-15, -15, 0, 90, true);
    ev3_motor_rotate(a.port, 130, 20, true);
    wait(0.2);
    ev3_motor_rotate(a.port, -130, 20, true);
    drive_deg(-15, -15, 0, 380, true);
    ev3_motor_rotate(a.port, 130, 20, true);
    wait(0.2);
    ev3_motor_rotate(a.port, -130, 20, true);
    drive_deg(-15, -15, 0, 80, true);
    ev3_motor_rotate(a.port, 130, 20, true);
    wait(0.2);
    ev3_motor_rotate(a.port, -130, 20, true);
}