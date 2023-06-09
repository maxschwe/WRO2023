#include "lib/programs/test.h"

void test()
{
    drive_smooth(20, -100, 500, true);
    // drive_time(20, 0, 3, true);
    display_set_spot(0, "b-c", m_get_deg(b));
    display_set_spot(1, "c-c", m_get_deg(c));
    // move_lifter_up(true);
    // m_off(a, true);
    // m_off(d, true);
    // linefollow_intersection(100, true);
    // turn_90(false);
    // linefollow_smooth(50, 770, true);

    // // drive again red container
    // // drive_deg(-10, -60, 0, 200, false);
    // // drive_deg(-60, -10, 0, 200, true);
    // // wait(0.3);
    // // drive_deg(10, 40, 0, 200, false);
    // // drive_deg(40, 10, 0, 150, true);

    // // place big ship
    // wait_stand();
    // drive_smooth(-10, 0, 700, true);
    // wait_stand();
    // turn_90(true);
    // act_move_speed(lifter, 80, LIFTER_BACK_BOAT_GRABBED, false);
    // drive_smooth(10, 0, 300, true);
    // drive_smooth(-10, 0, 300, true);

    // // place small ship
    // turn_90(false);
    // drive_smooth(-10, 0, 380, true);
    // turn_90(false);
    // act_move_speed(lifter, 80, LIFTER_INIT, false);
    // drive_smooth(-10, 0, 200, false);
    // drive_time(-10, 0, 0.5, true);
    // wait_stand();
    // drive_smooth(10, 0, 310, true);
    // wait_stand();
    // drive_smooth(-10, 50, 630, true);

    // // place_containers_on_ships();
    // // linefollow_smooth(100, 500, true);
}

void scan_test()
{
    // on(-20, 0);
    // FILE* fp = fopen("blau_blau5.txt", "w");
    // while (abs(m_get_deg(b)) < 850) {
    //     float blue_rel = col_get_rel_rgb(s4, 'b');
    //     fprintf(fp, "%f,", blue_rel);
    // }
    // fclose(fp);
    // off(true);
    // FILE* fp2 = fopen("gruen_gruen1.txt", "r");
    // float_array array = create_float_array(100);
    // float new_value;
    // while (fscanf(fp2, "%f,", &new_value) == 1) {
    //     append_array(&array, new_value);
    // }
    // finish_array(&array);
    // fclose(fp2);
    // evaluate(&array);

    // linefollow_deg_custom(100, 100000, 0.3, 50, true);
}

// 10: 0.3, 40
// 25: 0.3, 40
// 50: 0.15, 75
// 75: 0.25, 80
// 100: 0.35, 75