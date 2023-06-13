#include "lib/programs/run.h"

void run()
{
    start_backward_and_scan();
    
    drive_to_white_containers();
    // collect_blocks_start();
    // drive_and_drop_off_second_red_container();

    // // stop actuatuors and init
    // act_init(lifter);
    // act_init(dropper);
    // m_off(a, true);
    // m_off(d, true);

    collect_white_container();
    collect_and_scan_coloured_containers();
    collect_big_ship();
    collect_small_ship();

    drive_to_open_sea_and_drop_red_container();

    place_ships();

    // place_containers_on_ships();
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