#pragma once

#include <stdbool.h>
#include <string.h>

#include "ev3api.h"

#include "lib/robot/_robot_config.h"

typedef struct {
    SYSTIM start_time;
} Timer;

void display_clear();
void display_append(char title[DISPLAY_SPOT_MAX_LENGTH], float value);
void display_set_spot(int spot_num, char title[DISPLAY_SPOT_MAX_LENGTH], float value);
void display_set_text(int spot_num, char text[DISPLAY_SPOT_MAX_LENGTH]);
void display_redraw();
bool button_pressed(button_t button);
void wait_button_press(button_t button);
void wait_center_press();
void wait(float seconds);
void beep();
void error_beep();
void error_beep2();
Timer start_timer();
float get_time(Timer timer);
