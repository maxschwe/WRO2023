#include "app.h"

void main_task(intptr_t unused)
{
    init_programs_globals();
    init_robot();

    beep();

    while (!button_pressed(ENTER_BUTTON) && !button_pressed(LEFT_BUTTON) && !button_pressed(RIGHT_BUTTON)) { }
    
    if (button_pressed(ENTER_BUTTON)) {
        run();
        // second_day();
    } else if (button_pressed(LEFT_BUTTON)) {
        test();
    } else {
        debug();
    }
}