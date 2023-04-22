#include "../../include/robot/drive.h"
#include "../../include/config.h"

void on(int speed, int steering)
{
    int speed_b, speed_c;
    if (steering > 0) {
        speed_b = speed;
        speed_c = speed * (1 - steering / 50.0);
    } else {
        speed_b = speed * (1 + steering / 50.0);
        speed_c = speed;
    }
    m_on(b, speed_b);
    m_on(c, speed_c);
    current_speed = speed;
}

void off(bool brake)
{
    if (brake) {
        m_off(b, true);
        m_off(c, true);
    }
    current_speed = 0;
}

void drive_deg(int speed, int target_speed, int steering, int deg, bool brake)
{
    int current_deg_b, current_deg_c, target_deg_b, target_deg_c, current_speed;
    float current_steering;
    int taken_deg_b = 0;
    int taken_deg_c = 0;
    int b_left_deg, c_left_deg;
    int start_deg_b = m_get_deg(b);
    int start_deg_c = m_get_deg(c);
    int speed_diff = target_speed - speed;
    int loop_count = 0;
    current_deg_b = start_deg_b;
    current_deg_c = start_deg_c;
    deg = abs(deg);
    bool is_b_used;
    bool is_b_main;
    if (speed < 0) {
        deg = -deg;
        speed = -speed;
        speed_diff = -speed_diff;
    }
    if (steering > 0) {
        target_deg_b = deg;
        target_deg_c = deg * (1 - steering / 50.0);
        is_b_used = true;
    } else {
        target_deg_b = deg * (1 + steering / 50.0);
        target_deg_c = deg;
        is_b_used = false;
    }
    deg = abs(deg);
    if (PRINT_DRIVE_DEBUG) {
        display_set_spot(0, "b-t", target_deg_b);
        display_set_spot(1, "c-t", target_deg_c);
    }
    while (taken_deg_b < deg && taken_deg_c < deg) {
        b_left_deg = target_deg_b - current_deg_b + start_deg_b;
        c_left_deg = target_deg_c - current_deg_c + start_deg_c;
        // TODO: make speed curve x^3, not linear
        current_speed = (1.0 * abs(is_b_used ? taken_deg_b : taken_deg_c) / deg) * speed_diff + speed;
        float zaehler = b_left_deg - c_left_deg;
        int abs_b_left = abs(b_left_deg);
        int abs_c_left = abs(c_left_deg);
        float nenner = MAX(abs_b_left, abs_c_left);
        current_steering = (zaehler / nenner) * 50.0;
        is_b_main = abs_b_left > abs_c_left;
        if ((is_b_main ? b_left_deg : c_left_deg) < 0) {
            current_speed = -current_speed;
            current_steering = -current_steering;
        }

        on(current_speed, current_steering);
        current_deg_b = m_get_deg(b);
        current_deg_c = m_get_deg(c);
        taken_deg_b = abs(current_deg_b - start_deg_b);
        taken_deg_c = abs(current_deg_c - start_deg_c);
        loop_count++;
    }
    current_speed = target_speed;
    if (brake) {
        off(brake);
        current_speed = 0;
    }

    if (PRINT_DRIVE_DEBUG) {
        display_set_spot(2, "b-c", current_deg_b);
        display_set_spot(3, "c-c", current_deg_c);
        display_set_spot(4, "b-l", b_left_deg);
        display_set_spot(5, "c-l", c_left_deg);
        display_set_spot(6, "sp", current_speed);
        display_set_spot(7, "st", current_steering);
        display_set_spot(8, "", loop_count);
    }
}

void drive_col(int speed, int steering, ColorSensor sensor, char col, bool brake)
{
    on(speed, steering);
    col_wait_ref(sensor, col);
    current_speed = speed;
    if (brake) {
        off(brake);
        current_speed = 0;
    }
}

void drive_smooth(int target_speed, int deg, bool brake)
{

    int delta_speed = target_speed - abs(current_speed);
    float delta_speed_deg_needed = delta_speed * ACC_PER_100_DEG;

    current_speed = target_speed;
}

void turn_line(bool turn_left, bool brake)
{
    int steering = turn_left ? -100 : 100;
    ColorSensor sensor = turn_left ? s2 : s3;
    drive_deg(30, 30, steering, 150, false);
    drive_col(30, steering, sensor, WHITE, false);
    drive_col(30, steering, sensor, BLACK, false);
    drive_deg(30, 20, steering, 75, true);
}

void turn_90(bool turn_left, bool brake)
{
    int steering = turn_left ? -100 : 100;
    drive_deg(10, 20, steering, 140, false);
    drive_deg(20, 10, steering, 172, true);
}

void move_up(bool block)
{
    act_move(lifter, LIFTER_UP, block);
}

void move_down(bool block)
{
    act_move(lifter, LIFTER_INIT, block);
}

#define SCAN_COUNT 2

char scan(int output_y)
{
    char output[100];
    rgb_t val = col_get_rgb(s4);
    float lowest_r = 0.0;
    float lowest_g = 0.0;
    float lowest_b = 0.0;
    for (int i = 0; i < SCAN_COUNT; ++i) {
        val = col_get_rgb(s4);
        lowest_r += val.r;
        lowest_g += val.g;
        lowest_b += val.b;
    }
    lowest_r /= SCAN_COUNT;
    lowest_g /= SCAN_COUNT;
    lowest_b /= SCAN_COUNT;
    // sprintf(output, "R: %f", lowest_r);
    // ev3_lcd_draw_string(output, 10, 30);
    // sprintf(output, "G: %f", lowest_g);
    // ev3_lcd_draw_string(output, 10, 50);
    // sprintf(output, "B: %f", lowest_b);
    // ev3_lcd_draw_string(output, 10, 70);
    float blue_rel = lowest_b / (lowest_b + lowest_r + lowest_g + 1);
    sprintf(output, "%f, %c", blue_rel, (blue_rel < 0.45) ? 'g' : 'b');
    ev3_lcd_draw_string(output, 10, output_y);
    return (blue_rel < 0.45) ? 'g' : 'b';
}