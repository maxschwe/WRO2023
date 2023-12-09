#include "app.h"

void main_task(intptr_t unused)
{
    init_programs_globals();
    init_robot();

    beep();

    while (!button_pressed(ENTER_BUTTON) && !button_pressed(LEFT_BUTTON) && !button_pressed(RIGHT_BUTTON)) { }

    Timer program_timer = start_timer();
    if (button_pressed(ENTER_BUTTON)) {
        run();
    } else if (button_pressed(LEFT_BUTTON)) {
        test();
    } else {
        debug();
    }
    display_set_spot(10, "Time", get_time(program_timer));
}
