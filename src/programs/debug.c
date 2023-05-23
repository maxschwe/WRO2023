#include "../../include/programs/debug.h"

void debug()
{
    print_values();
}

void print_values()
{
    FILE* bt = ev3_serial_open_file(EV3_SERIAL_BT);
    while (true) {
        if (button_pressed(ENTER_BUTTON)) {
            m_reset(a);
            m_reset(b);
            m_reset(c);
            m_reset(d);
        }
        display_clear();
        display_set_spot(0, "A", m_get_deg(a));
        fprintf(bt, "A: %i; ", m_get_deg(a));
        display_set_spot(1, "B", m_get_deg(b));
        fprintf(bt, "B: %i; ", m_get_deg(b));
        display_set_spot(2, "C", m_get_deg(c));
        fprintf(bt, "C: %i; ", m_get_deg(c));
        display_set_spot(3, "D", m_get_deg(d));
        fprintf(bt, "D: %i; ", m_get_deg(d));
        display_set_spot(4, "1", col_get_ref(s1));
        fprintf(bt, "1: %i; ", col_get_ref(s1));
        display_set_spot(5, "2", col_get_ref(s2));
        fprintf(bt, "2: %i; ", col_get_ref(s2));
        display_set_spot(6, "3", col_get_ref(s3));
        fprintf(bt, "3: %i; ", col_get_ref(s3));
        display_set_spot(7, "4", col_get_amb(s4));
        fprintf(bt, "4: %i\n", col_get_ref(s4));
        rgb_t rgb_val = col_get_rgb(s4);
        display_set_spot(8, "R", rgb_val.r);
        display_set_spot(9, "G", rgb_val.g);
        display_set_spot(10, "B", rgb_val.b);
        display_set_spot(11, "rel", col_get_rel_rgb(s4, 'b'));
        wait(0.1);
    }
}