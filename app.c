#include "app.h"

void main_task(intptr_t unused)
{
    init();
    beep();

    while (!button_pressed(ENTER_BUTTON) && !button_pressed(LEFT_BUTTON) && !button_pressed(RIGHT_BUTTON)) { }
    if (button_pressed(ENTER_BUTTON)) {
        run();
    } else if (button_pressed(LEFT_BUTTON)) {
        test();
    } else {
        debug();
    }
}