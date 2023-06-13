#include "lib/programs/test.h"

void test()
{
    for (int i = 0; i < 10; i++) {
        drive_smooth(10, 0, 100, true);
        wait(0.5);
    }
    display_set_spot(2, "b-c", m_get_deg(b));
    display_set_spot(4, "c-c", m_get_deg(c));
}
