#include "drive.h"

void on(int speed, int steering)
{
    int speed_left, speed_right;
    if (steering > 0) {
        speed_left = speed * (1 + steering / 50);
        speed_right = speed;
    } else {
        speed_left = speed;
        speed_right = speed * (1 + steering / 50);
    }
    m_on(b, speed_left);
    m_on(c, speed_right);
}

void off(bool brake)
{
    m_off(b, brake);
    m_off(c, brake);
}

void drive_deg(int speed, int steering, float deg)
{
}

void drive_deg(int initial_speed, int target_speed, int steering, int deg, bool_t brake)
{
    int initial_deg;
    int difference = 0;
    int current_speed = 0;
    char output[100];
    // ev3_lcd_draw_string(output, 10, 10);
    if (initial_speed > 0) {
        int power_b;
        int power_c;
        initial_deg = ev3_motor_get_counts(steering < 0 ? C : B);
        initial_speed = abs(initial_speed);
        target_speed = abs(target_speed);
        deg = abs(deg);
        while ((difference = abs(ev3_motor_get_counts(steering < 0 ? C : B) - initial_deg)) < deg) {
            current_speed = (difference * 1.0 / deg) * abs(initial_speed - target_speed) + initial_speed;
            sprintf(output, "S: %i, D: %i", current_speed, difference);
            // ev3_lcd_draw_string(output, 10, 30);

            if (steering < 0) {
                power_b = -1 * (current_speed + (steering / 50.0) * current_speed);
                power_c = current_speed;
            } else {
                power_b = -1 * current_speed;
                power_c = current_speed - (steering / 50.0) * current_speed;
            }
            ev3_motor_set_power(B, power_b);
            ev3_motor_set_power(C, power_c);
            // ev3_lcd_draw_string()
        }
    } else {
        int power_b;
        int power_c;
        initial_deg = ev3_motor_get_counts(steering < 0 ? B : C);
        initial_speed = abs(initial_speed);
        target_speed = abs(target_speed);
        deg = abs(deg);
        while ((difference = abs(ev3_motor_get_counts(steering < 0 ? B : C) - initial_deg)) < deg) {
            current_speed = (difference * 1.0 / deg) * abs(initial_speed - target_speed) + initial_speed;
            sprintf(output, "S: %i, D: %i", current_speed, difference);
            // ev3_lcd_draw_string(output, 10, 30);

            if (steering > 0) {
                power_b = current_speed - (steering / 50.0) * current_speed;
                power_c = -1 * current_speed;
            } else {
                power_b = current_speed;
                power_c = -1 * (current_speed + (steering / 50.0) * current_speed);
            }
            ev3_motor_set_power(B, power_b);
            ev3_motor_set_power(C, power_c);
            // ev3_lcd_draw_string()
        }
    }
    // ev3_lcd_draw_string("Beendet", 10, 30);
    if (brake) {
        ev3_motor_stop(B, true);
        ev3_motor_stop(C, true);
    }
}

void linefollow(void)
{
    int power_b;
    int power_c;
    float kp = 1.4;
    float kd = 0.3;
    int error = 0;
    int last_error = 0;
    while (true) {
        int ref_s2 = ev3_color_sensor_get_reflect(S2);
        int ref_s3 = ev3_color_sensor_get_reflect(S3);
        error = (ref_s2 - ref_s3) / 25;
        error *= error * error * error * error * kp;
        error += (error - last_error) * kd;
        last_error = error;

        if (error > 0) {
            power_b = -100;
            power_c = 100 - error;
        } else {
            power_b = -100 - error;
            power_c = 100;
        }
        ev3_motor_set_power(B, power_b);
        ev3_motor_set_power(C, power_c);
    }
}

void linefollow_intersection(int speed, bool_t brake)
{
    int power_b;
    int power_c;
    float kp = 1.5;
    float kd = 0.9;
    int error = 0;
    int last_error = 0;
    int ref_s2 = ev3_color_sensor_get_reflect(S2);
    int ref_s3 = ev3_color_sensor_get_reflect(S3);
    int initial_b = ev3_motor_get_counts(B);
    while (ref_s2 + ref_s3 > 30 || abs(ev3_motor_get_counts(B) - initial_b) < 400) {
        ref_s2 = ev3_color_sensor_get_reflect(S2);
        ref_s3 = ev3_color_sensor_get_reflect(S3);
        error = (ref_s2 - ref_s3) / 25;
        error *= error * error * error * error * kp;
        error += (error - last_error) * kd;
        error = error + 0.3 * (100 - speed) * error;
        last_error = error;

        if (error > 0) {
            power_b = -1 * speed;
            power_c = speed - error;
        } else {
            power_b = -1 * speed - error;
            power_c = speed;
        }
        ev3_motor_set_power(B, power_b);
        ev3_motor_set_power(C, power_c);
    }
    if (brake) {
        ev3_motor_stop(B, true);
        ev3_motor_stop(C, true);
    }
}

#define SCAN_COUNT 10

void linefollow_deg(int speed, int deg, bool_t brake)
{
    int power_b;
    int power_c;
    float kp = 0.5;
    float kd = 0.2;
    // kp = kp + 0.1 * ((100 - speed) / 100) * kp;
    // kd = kd - 0.8 * ((100 - speed) / 100) * kd;
    int error = 0;
    int last_error = 0;
    int ref_s2 = ev3_color_sensor_get_reflect(S2);
    int ref_s3 = ev3_color_sensor_get_reflect(S3);
    int initial_b = ev3_motor_get_counts(B);
    while (abs(ev3_motor_get_counts(B) - initial_b) < deg) {
        ref_s2 = ev3_color_sensor_get_reflect(S2);
        ref_s3 = ev3_color_sensor_get_reflect(S3);
        error = (ref_s2 - ref_s3) / 20;
        error *= kp;
        error += (error - last_error) * kd;

        last_error = error;
        if (error > 0) {
            power_b = -1 * speed;
            power_c = speed - error;
        } else {
            power_b = -1 * speed - error;
            power_c = speed;
        }
        ev3_motor_set_power(B, power_b);
        ev3_motor_set_power(C, power_c);
    }
    if (brake) {
        ev3_motor_stop(B, true);
        ev3_motor_stop(C, true);
    }
}

void linefollow_col_1(int speed, int ref_light_s1, bool_t brake)
{
    char output[100];
    int power_b;
    int power_c;
    float kp = 0.5;
    float kd = 0.2;
    // kp = kp + 0.1 * ((100 - speed) / 100) * kp;
    // kd = kd - 0.8 * ((100 - speed) / 100) * kd;
    int error = 0;
    int last_error = 0;
    int ref_s2 = ev3_color_sensor_get_reflect(S2);
    int ref_s3 = ev3_color_sensor_get_reflect(S3);
    while (ev3_color_sensor_get_reflect(S1) < ref_light_s1) {
        sprintf(output, "Val: %i", ev3_color_sensor_get_reflect(S1));
        ev3_lcd_draw_string(output, 10, 20);
        ref_s2 = ev3_color_sensor_get_reflect(S2);
        ref_s3 = ev3_color_sensor_get_reflect(S3);
        error = (ref_s2 - ref_s3) / 20;
        error *= kp;
        error += (error - last_error) * kd;

        last_error = error;
        if (error > 0) {
            power_b = -1 * speed;
            power_c = speed - error;
        } else {
            power_b = -1 * speed - error;
            power_c = speed;
        }
        ev3_motor_set_power(B, power_b);
        ev3_motor_set_power(C, power_c);
    }
    if (brake) {
        ev3_motor_stop(B, true);
        ev3_motor_stop(C, true);
    }
}

void move_up(bool_t block)
{
    ev3_motor_rotate(D, -120, 10, block);
}

void move_down(bool_t block)
{
    ev3_motor_rotate(D, 120, 20, block);
}

void scan(int output_y)
{
    char output[100];
    rgb_raw_t val;
    ev3_color_sensor_get_rgb_raw(S4, &val);
    float lowest_r = 0.0;
    float lowest_g = 0.0;
    float lowest_b = 0.0;
    for (int i = 0; i < SCAN_COUNT; ++i) {
        ev3_color_sensor_get_rgb_raw(S4, &val);
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
    float blue_rel = lowest_b / (lowest_b + lowest_r + lowest_g);
    sprintf(output, "%f, %c", blue_rel, (blue_rel < 0.45) ? 'g' : 'b');
    ev3_lcd_draw_string(output, 10, output_y);
}