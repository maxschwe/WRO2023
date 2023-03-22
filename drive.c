#include "drive.h"

#define B EV3_PORT_B
#define C EV3_PORT_C
#define D EV3_PORT_D
#define S1 EV3_PORT_1
#define S2 EV3_PORT_2
#define S3 EV3_PORT_3
#define S4 EV3_PORT_4

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
}

void off(bool brake)
{
    m_off(b, brake);
    m_off(c, brake);
}

void drive_deg(int speed, int target_speed, int steering, int deg, bool brake)
{
    int current_deg_b, current_deg_c, target_deg_b, target_deg_c, current_speed, current_steering;
    int taken_deg_b = 0;
    int taken_deg_c = 0;
    int b_left_deg, c_left_deg;
    int start_deg_b = m_get_deg(b);
    int start_deg_c = m_get_deg(c);
    int speed_diff = target_speed - speed;
    current_deg_b = start_deg_b;
    current_deg_c = start_deg_c;
    deg = abs(deg);
    bool is_b_used;
    if (steering > 0) {
        target_deg_b = deg;
        target_deg_c = deg * (1 - steering / 50.0);
        is_b_used = true;
    } else {
        target_deg_b = deg * (1 + steering / 50.0);
        target_deg_c = deg;
        is_b_used = false;
    }
    if (speed < 0) {
        target_deg_b = -target_deg_b;
        target_deg_c = -target_deg_c;
    }
    // display_set_spot(0, "Tb", target_deg_b);
    // display_set_spot(1, "Tc", target_deg_c);
    while (taken_deg_b < deg && taken_deg_c < deg) {
        // b_left_deg = target_deg_b - current_deg_b + start_deg_b;
        // c_left_deg = target_deg_c - current_deg_c + start_deg_c;
        // // TODO: make speed curve x^3, not linear
        // current_speed = (1.0 * abs(is_b_used ? taken_deg_b : taken_deg_c) / deg) * speed_diff + speed;
        // int divident = MAX(abs(b_left_deg), abs(c_left_deg)) * 2;
        // int zaehler = b_left_deg - c_left_deg;
        // // if (speed < 0) {
        // //     zaehler = -zaehler;
        // // }
        // current_steering = (1.0 * zaehler / divident) * 100;
        // // current_steering = (1.0 * abs(b_left_deg - c_left_deg) / (MAX(abs(b_left_deg), abs(c_left_deg)) * 2)) * 100;
        // // if (abs(b_left_deg) > abs(c_left_deg)) {
        // //     if (b_left_deg < 0) {
        // //         current_speed = -current_speed;
        // //     }
        // // } else {
        // //     current_steering = -current_steering;
        // //     if (c_left_deg < 0) {
        // //         current_speed = -current_speed;
        // //     }
        // // }
        // // if (current_speed < 0) {
        // //     current_steering = -current_steering;
        // // }
        // on(current_speed, current_steering);
        // display_set_spot(2, "St", current_steering);
        // display_set_spot(3, "Sp", current_speed);
        // display_set_spot(6, "b", b_left_deg);
        // display_set_spot(7, "c", c_left_deg);
        // current_deg_b = m_get_deg(b);
        // current_deg_c = m_get_deg(c);
        // taken_deg_b = abs(current_deg_b - start_deg_b);
        // taken_deg_c = abs(current_deg_c - start_deg_c);
        // display_set_spot(8, "b", taken_deg_b);
        // display_set_spot(9, "c", taken_deg_c);
        b_left_deg = target_deg_b - current_deg_b + start_deg_b;
        c_left_deg = target_deg_c - current_deg_c + start_deg_c;
        // TODO: make speed curve x^3, not linear
        current_speed = (1.0 * abs(is_b_used ? taken_deg_b : taken_deg_c) / deg) * speed_diff + speed;
        int divident = MAX(abs(b_left_deg), abs(c_left_deg)) * 2;
        int zaehler = b_left_deg - c_left_deg;
        current_steering = (1.0 * zaehler / divident) * 100;
        on(current_speed, current_steering);
        // display_set_spot(2, "St", current_steering);
        // display_set_spot(3, "Sp", current_speed);
        // display_set_spot(6, "b", b_left_deg);
        // display_set_spot(7, "c", c_left_deg);
        current_deg_b = m_get_deg(b);
        current_deg_c = m_get_deg(c);
        taken_deg_b = abs(current_deg_b - start_deg_b);
        taken_deg_c = abs(current_deg_c - start_deg_c);
        // display_set_spot(8, "b", taken_deg_b);
        // display_set_spot(9, "c", taken_deg_c);
    }

    m_off(b, brake);
    m_off(c, brake);
}

void drive_smooth(int steering, int deg, bool deacc, bool brake)
{
    int max_acc_per_100_deg = 20;
    int min_speed = 10;
    int max_speed;
    if (deacc) {
        max_speed = MIN(100, min_speed + deg / (2 * 100 * max_acc_per_100_deg));
        if (max_speed < 100) {
            drive_deg(min_speed, max_speed, steering, deg / 2, true);
        }
    } else {
        max_speed = MIN(100, min_speed + deg / (100 * max_acc_per_100_deg));
    }
}

void drive_deg2(int initial_speed, int target_speed, int steering, int deg, bool_t brake)
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
            // sprintf(output, "S: %i, D: %i", current_speed, difference);
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
            // sprintf(output, "S: %i, D: %i", current_speed, difference);
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

void linefollow(int speed, int deg)
{
    float kp = 0.5;
    float kd = 0.2;
    float error = 0;
    int last_error = 0;
    int current_speed = 0;
    int initial_b = ev3_motor_get_counts(B);
    while (abs(ev3_motor_get_counts(B) - initial_b) < deg) {
        int ref_s2 = col_get_ref(s2);
        int ref_s3 = col_get_ref(s3);
        error = (ref_s2 - ref_s3);
        // error = (50 - ref_s3);
        error *= kp;
        error += (error - last_error) * kd;
        // current_speed = speed - abs(error * error * error) * 0.01;
        // display_set_spot(2, "Sp", current_speed);
        // display_set_spot(3, "St", error);
        // display_set_spot(4, "diff", error * error * error);
        on(speed, error);
        last_error = error;
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
    int ref_s2 = ev3_color_sensor_get_reflect(EV3_PORT_2);
    int ref_s3 = ev3_color_sensor_get_reflect(EV3_PORT_3);
    int initial_b = ev3_motor_get_counts(EV3_PORT_B);
    while (ref_s2 + ref_s3 > 30 || abs(ev3_motor_get_counts(EV3_PORT_B) - initial_b) < 200) {
        ref_s2 = ev3_color_sensor_get_reflect(EV3_PORT_2);
        ref_s3 = ev3_color_sensor_get_reflect(EV3_PORT_3);
        error = (ref_s2 - ref_s3) / 25;
        error *= error * error * error * error * kp;
        error += (error - last_error) * kd;
        // error = error + 0.3 * (100 - speed) * error;
        last_error
            = error;

        if (error > 0) {
            power_b = -1 * speed;
            power_c = speed - error;
        } else {
            power_b = -1 * speed - error;
            power_c = speed;
        }
        ev3_motor_set_power(EV3_PORT_B, power_b);
        ev3_motor_set_power(EV3_PORT_C, power_c);
    }
    if (brake) {
        ev3_motor_stop(EV3_PORT_B, true);
        ev3_motor_stop(EV3_PORT_C, true);
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
    int error = 0;
    int last_error = 0;
    int ref_s2 = ev3_color_sensor_get_reflect(S2);
    int ref_s3 = ev3_color_sensor_get_reflect(S3);
    while (ev3_color_sensor_get_reflect(S1) < ref_light_s1) {
        // sprintf(output, "Val: %i", ev3_color_sensor_get_reflect(S1));
        // ev3_lcd_draw_string(output, 10, 20);
        ref_s2 = ev3_color_sensor_get_reflect(S2);
        ref_s3 = ev3_color_sensor_get_reflect(S3);
        error = (ref_s2 - ref_s3);
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
    ev3_motor_rotate(D, 120, 60, block);
}

char scan(int output_y)
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
    float blue_rel = lowest_b / (lowest_b + lowest_r + lowest_g + 1);
    sprintf(output, "%f, %c", blue_rel, (blue_rel < 0.45) ? 'g' : 'b');
    ev3_lcd_draw_string(output, 10, output_y);
    return (blue_rel < 0.45) ? 'g' : 'b';
}