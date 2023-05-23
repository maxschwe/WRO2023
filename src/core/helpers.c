#include "../../include/core/helpers.h"
#include "../../include/config.h"

int filled_spots = 0;
clock_t start_time;
bool timer_reseted = false;
char texts[MAX_SPOTS][MAX_LENGTH];

void display_clear()
{
    ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
    filled_spots = 0;
}

void display_append(char title[MAX_LENGTH], float value)
{
    if (filled_spots >= MAX_SPOTS) {
        for (int i = 1; i < MAX_SPOTS; ++i) {
            strncpy(texts[i - 1], texts[i], MAX_LENGTH - 1);
        }
        filled_spots = MAX_SPOTS - 1;
    }

    display_set_spot(filled_spots++, title, value);
}

void display_set_spot(int spot_num, char title[MAX_LENGTH], float value)
{
    snprintf(texts[spot_num], MAX_LENGTH - 1, "%s:%.2f", title, value);
    display_redraw();
}

void display_set_text(int spot_num, char text[MAX_LENGTH])
{
    strncpy(texts[spot_num], text, MAX_LENGTH);
    display_redraw();
}

void display_redraw()
{
    for (int i = 0; i < MAX_SPOTS; ++i) {
        ev3_lcd_draw_string(texts[i], (i % 2) * (EV3_LCD_WIDTH / 2), 10 + (i / 2) * 20);
    }
}

bool button_pressed(button_t button)
{
    return ev3_button_is_pressed(button);
}
void wait_button_press(button_t button)
{
    while (!ev3_button_is_pressed(button)) {
    }
}

void wait_center_press()
{
    wait_button_press(ENTER_BUTTON);
}

void wait(float seconds)
{
    tslp_tsk(seconds * 1000000U);
}

void beep()
{
    ev3_speaker_play_tone(NOTE_C5, 200);
}

void error_beep()
{
    ev3_speaker_play_tone(NOTE_C6, 500);
}
