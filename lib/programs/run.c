#include "lib/programs/run.h"

void run()
{
    m_on(a, -2);
    m_on(d, -1);

    // start left turned
    drive_smooth(10, 0, 320, true);
    turn_90(false);
    drive_time(-30, 0, 4, true);
    drive_smooth(10, 0, 440, true);
    act_init(lifter);
    act_init(dropper);
    m_off(a, true);
    m_off(d, true);

    // collect red container and drop off
    turn_90(false);
    act_move(lifter, LIFTER_RED_CONTAINER, true);
    wait(1);
    drive_smooth(-10, 0, 300, true);
    act_move(lifter, LIFTER_INIT, true);
    drive_smooth(10, 0, 200, true);
    turn_90(true);
    drive_deg(20, 0, 300, false);
    drive_line(20, true);
    turn_90(false);
    linefollow_intersection(30, false);
    linefollow_deg(30, 100, true);
    turn_180(true);
    act_move(lifter, LIFTER_UP, true);
    drive_smooth(10, 0, 200, true);

    // drive to big ship and drop off
    act_move(lifter, LIFTER_INIT, true);
    linefollow_deg(10, 180, true);
    turn_90(true);
    drive_smooth(10, 0, 530, true);
    turn_90(false);
    drive_deg(10, 0, 690, true);
    act_move(lifter, LIFTER_UP, true);
    drive_to("s4", 'e', "k3", 'e');
    linefollow_deg(30, 1150, true);
    turn_90(false);
    drive_time(30, 0, 3, true);
    act_move(lifter, LIFTER_INIT, true);
    drive_smooth(-30, 0, 500, true);

    // drive back to line in the sea
    turn_90(true);
    drive_deg(10, 0, 450, true);
    turn_line(true, true);
    drive_to("s7", 'n', "k4", 'n');
    linefollow_deg(10, 100, true);
    turn_180(true);
    act_move(lifter, LIFTER_UP, true);
    drive_deg(-10, 0, 90, true);

    // collect yellow container
    act_move_speed(lifter, 40, LIFTER_INIT, true);

    // drive to lifter drop off
    linefollow_deg(10, 190, true);

    turn_90(false);
    linefollow_deg(10, 200, true);

    drive_to("k4", 'w', "s5", 'x');

    // lifter drop off
    linefollow_deg(10, 300, true);
    turn_180(true);
    act_move_speed(lifter, 10, NEW_POS, true);
    drive_deg(-10, 0, 130, true);
    drive_deg(10, 100, 30, true);

    wait(0.2);
    
    act_move_speed(lifter, 10, LIFTER_DOWN_CONTAINER, true);

    linefollow_smooth(30, 250, true);

    drive_smooth(-10, 0, 450, true);
    
    linefollow_smooth(100, 300, true);
    linefollow_intersection(100, false);

    // collect white container
    act_move(lifter, LIFTER_INIT, false);
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

    lifter_collect(true);
    turn_90(true);
    linefollow_intersection(30, true);
    linefollow_deg(20, 270, true);
    drive_smooth_custom(TURN_START_SPEED, TURN_END_SPEED, TURN_MAX_SPEED, 100, 450, TURN_ACC_FACTOR, TURN_DEACC_FACTOR, true, false, false);

    drive_smooth(-10, 0, 900, true);
    act_move_speed(dropper, 30, DROPPER_DROPPED, true);
}