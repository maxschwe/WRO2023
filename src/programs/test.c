#include "../../include/programs/test.h"

void test()
{
    m_on(a, -1);
    m_on(d, -1);
    wait(1);
    act_init(lifter);
    act_init(dropper);
    m_off(a, true);
    m_off(d, true);

    for (int i = 0; i < 20; ++i) {
        move_up(true);
        wait(1);
        move_down(true);
        wait(1);
    }
}