#include "lib/programs/debug.h"

void debug()
{
    print_values();
}

void print_values()
{
    while (true) {
        if (button_pressed(ENTER_BUTTON)) {
            m_reset(a);
            m_reset(b);
            m_reset(c);
            m_reset(d);
        }
        display_clear();
        display_set_spot(0, "A", m_get_deg(a));
        display_set_spot(1, "B", m_get_deg(b));
        display_set_spot(2, "C", m_get_deg(c));
        display_set_spot(3, "D", m_get_deg(d));
        display_set_spot(4, "1", col_get_ref(s1));
        display_set_spot(5, "2", col_get_ref(s2));
        display_set_spot(6, "3", col_get_ref(s3));
        display_set_spot(7, "4", col_get_ref(s4));
        float rel_average = 0.0;
        for (int i = 0; i < SIMPLE_SCAN_COUNT; ++i) {
            rgb_t val = col_get_rgb(s4);
            rel_average += 1.0 * abs(val.r - val.b) / (val.r + val.b + val.g + 1);
        }
        rel_average = rel_average / (1.0 * SIMPLE_SCAN_COUNT);
        rgb_t rgb_val = col_get_rgb(s4);
        display_set_spot(8, "R", rgb_val.r);
        display_set_spot(9, "G", rgb_val.g);
        display_set_spot(10, "B", rgb_val.b);
        display_set_spot(11, "rel", rel_average);
        wait(0.1);
    }
}
