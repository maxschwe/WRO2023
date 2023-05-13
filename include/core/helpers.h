#ifndef HELPERS_H
#define HELPERS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ev3api.h"

#define MAX_SPOTS 12
#define MAX_LENGTH 11

void display_clear();
void display_append(char title[MAX_LENGTH], float value);
void display_set_spot(int spot_num, char title[MAX_LENGTH], float value);
void display_set_text(int spot_num, char text[MAX_LENGTH]);
void display_redraw();
bool button_pressed(button_t button);
void wait_button_press(button_t button);
void wait_center_press();
void wait(float seconds);
void beep();
void error_beep();

#endif