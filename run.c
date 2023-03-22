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
    on(-40, 0);
    col_wait_ref(s1, 'b');
    drive_deg(-40, -30, 0, 180, false);
    drive_deg(-30, -30, 0, 210, true);
    val[0] = scan(10);
    drive_deg(-30, -10, 0, 110, true);
    val[1] = scan(30);
    drive_deg(10, 40, 0, 170, true);
    on(30, -100);
    m_wait_deg(b, 100);
    col_wait_ref(s2, 'w');
    col_wait_ref(s2, 'b');
    m_wait_deg(b, 80);
    off(true);
    wait(0.4);
    linefollow(20, 300);
    linefollow_intersection(100, false);
    linefollow_intersection(100, false);
    linefollow_deg(40, 100, true);
    wait(0.4);
    on(30, -100);
    m_wait_deg(b, 100);
    col_wait_ref(s2, 'w');
    col_wait_ref(s2, 'b');
    m_wait_deg(b, 80);
    off(true);
    wait(0.4);
    linefollow(20, 300);
    linefollow(20, 200);
    beep();
    linefollow_col_1(10, 18, false);
    drive_deg(10, 10, 0, 10, true);

    beep();

    wait(0.4);
    drive_deg(10, 40, -100, 140, false);
    drive_deg(40, 10, -100, 172, true);
    wait(0.4);
    drive_deg(20, 10, 0, 90, true);
    move_up(true);
    move_down(false);
    drive_deg(10, 30, 0, 100, false);
    on(30, 0);
    m_wait_deg(b, 100);
    col_wait_ref(s3, 'g');
    beep();
    m_wait_deg(b, 460);

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
    drive_deg(20, 20, 1, 120, true);
    drive_deg(20, 20, -50, 150, true);
    drive_deg(20, 20, 50, 150, true);

    ev3_motor_rotate(d.port, -120, 20, true);
    drive_deg(-20, -40, 0, 200, true);
    drive_deg(-20, -20, -50, 420, true);
    drive_deg(20, 80, 0, 200, true);
    on(80, 0);
    col_wait_ref(s3, 'w');
    m_wait_deg(b, 30);
    col_wait_ref(s3, 'b');
    m_wait_deg(b, 70);
    off(true);
    on(30, -100);
    m_wait_deg(b, 100);
    col_wait_ref(s2, 'w');
    col_wait_ref(s2, 'b');
    m_wait_deg(b, 60);
    off(true);
    wait(0.4);
    linefollow(20, 400);
    linefollow_intersection(100, false);
    drive_deg(100, 20, 0, 60, true);
    wait(0.3);
    on(30, -100);
    m_wait_deg(b, 100);
    col_wait_ref(s2, 'w');
    col_wait_ref(s2, 'b');
    m_wait_deg(b, 80);
    off(true);
    wait(0.3);
    linefollow(20, 300);
    off(true);
    ev3_motor_rotate(d.port, 50, 20, false);
    wait(0.3);
    drive_deg(-10, -40, 0, 300, false);
    drive_deg(-40, -40, 0, 400, false);
    drive_deg(-40, -10, 0, 200, true);
    ev3_motor_rotate(d.port, -50, 20, true);
    linefollow(20, 200);
    linefollow_intersection(100, false);
    drive_deg(100, 20, 0, 100, true);
    wait(0.3);
    on(30, 100);
    m_wait_deg(b, 100);
    col_wait_ref(s3, 'w');
    col_wait_ref(s3, 'b');
    m_wait_deg(b, 100);
    off(true);
    linefollow(20, 600);
    linefollow_intersection(100, false);
    linefollow_intersection(100, false);
    drive_deg(100, 20, 0, 100, true);
    wait(0.3);
    on(30, 100);
    m_wait_deg(b, 100);
    col_wait_ref(s3, 'w');
    col_wait_ref(s3, 'b');
    m_wait_deg(b, 100);
    off(true);
    wait(0.3);
    linefollow(30, 800);
    off(true);
}