#include "lib/programs/second_day.h"

void second_day() {
    m_on(a, -2);
    m_on(d, -1);

    start_backward_and_scan();
    // do some short stuff
    drive_smooth(10, 0, 270, true);
    turn_90(false);
    drive_time(-30, 0, 4, true);
    drive_smooth(10, 0, 400, true);
    act_init(lifter);
    act_init(dropper);
    m_off(a, true);
    m_off(d, true);
    turn_90(false);
    act_move(lifter, LIFTER_RED_CONTAINER, true);
    drive_smooth(-10, 0, 400, true);
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
    // drive_to("k1", 'e', "k4", 'n');



    


    
}
