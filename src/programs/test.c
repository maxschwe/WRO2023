#include "../../include/programs/test.h"

void test()
{
    linefollow_smooth(100, 100, false);
    linefollow_intersection(100, false);
    linefollow_intersection(100, false);
    linefollow_intersection(100, true);
    turn_90(false);
    linefollow_smooth(100, 100, false);
    for (int i = 0; i < 100; i++) {
        linefollow_intersection(100, true);
        turn_90(true);
        linefollow_smooth(100, 100, false);
        linefollow_intersection(100, false);
        linefollow_intersection(100, true);
        turn_90(true);
        linefollow_smooth(100, 100, false);
        linefollow_intersection(100, false);
        linefollow_intersection(100, true);
        turn_90(true);
        linefollow_smooth(100, 100, false);
        linefollow_intersection(100, false);
        linefollow_intersection(100, true);
        turn_90(true);
        linefollow_intersection(100, false);
    }
    linefollow_intersection(100, true);
    turn_180(true);
    linefollow_smooth(100, 100, false);
    linefollow_intersection(100, true);
    turn_90(true);
    linefollow_smooth(100, 100, false);
    linefollow_intersection(100, false);
    linefollow_intersection(100, true);
    turn_180(true);

    // drive_smooth(20, 0, 1000, true);
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