#include "lib/programs/second_day.h"

void second_day() {
    m_on(a, -2);
    m_on(d, -1);

    // do some short stuff
    drive_line(30, true);
    turn_line(false, true);


    act_init(lifter);
    act_init(dropper);
    m_off(a, true);
    m_off(d, true);
}
