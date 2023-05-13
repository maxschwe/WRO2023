#include "../../include/programs/test.h"
#include <pthread.h>

void test()
{
    // on(-20, 0);
    // FILE* fp = fopen("gruen_blau.txt", "a+");
    // while (abs(m_get_deg(b)) < 1000) {
    //     rgb_t val = col_get_rgb(s4);
    //     float lowest_r = 0.0;
    //     float lowest_g = 0.0;
    //     float lowest_b = 0.0;
    //     for (int i = 0; i < SCAN_COUNT; ++i) {
    //         val = col_get_rgb(s4);
    //         lowest_r += val.r;
    //         lowest_g += val.g;
    //         lowest_b += val.b;
    //     }
    //     lowest_r /= SCAN_COUNT;
    //     lowest_g /= SCAN_COUNT;
    //     lowest_b /= SCAN_COUNT;
    //     // sprintf(output, "R: %f", lowest_r);
    //     // ev3_lcd_draw_string(output, 10, 30);
    //     // sprintf(output, "G: %f", lowest_g);
    //     // ev3_lcd_draw_string(output, 10, 50);
    //     // sprintf(output, "B: %f", lowest_b);
    //     // ev3_lcd_draw_string(output, 10, 70);
    //     float blue_rel = lowest_b / (lowest_b + lowest_r + lowest_g + 1);
    //     fprintf(fp, "%f,", blue_rel);
    // }
    // fclose(fp);
    // off(true);
    // wait(3);
    drive_smooth(10, 100, 312, true);

    // linefollow_deg_custom(100, 100000, 0.3, 50, true);
}

// 10: 0.3, 40
// 25: 0.3, 40
// 50: 0.15, 75
// 75: 0.25, 80
// 100: 0.35, 75