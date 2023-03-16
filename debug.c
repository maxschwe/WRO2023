#include "debug.h"

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
        display_set_spot(6, "1", col_get_ref(s1));
        display_set_spot(7, "2", col_get_ref(s2));
        display_set_spot(8, "3", col_get_ref(s3));
        display_set_spot(9, "4", col_get_ref(s4));
        wait(0.1);
    }
}