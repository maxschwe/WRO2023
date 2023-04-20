#include "../../include/robot/drive.h"
#include "../../include/config.h"

#define B EV3_PORT_B
#define C EV3_PORT_C
#define D EV3_PORT_D
#define S1 EV3_PORT_1
#define S2 EV3_PORT_2
#define S3 EV3_PORT_3
#define S4 EV3_PORT_4

int current_speed = 0;

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
    int b_left_deg, c_left_deg, abs_b_left, abs_c_left;
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

void linefollow_slow(int speed, int deg, bool brake)
{
    float kp = 0.4;
    float kd = 50;
    float error = 0;
    float pid_value = 0.0;
    float last_error = 0;
    int current_speed = 0;
    int initial_b = ev3_motor_get_counts(B);
    while (abs(ev3_motor_get_counts(B) - initial_b) < deg) {
        error = col_get_ref(s2) - col_get_ref(s3);

        pid_value = error * kp + (error - last_error) * kd;

        on(speed, pid_value);

        // fprintf(bt, "%f,%f; ", error, scan_diff);
        last_error = error;
    }
    current_speed = speed;
    if (brake) {
        off(brake);
        current_speed = 0;
    }
}

void linefollow_test(int speed, int deg, float kp, float kd, bool brake)
{
    int error = 0;
    float pid_value = 0.0;
    float last_error = 0;
    int current_speed = 0;
    int power_b, power_c;
    int initial_b = ev3_motor_get_counts(B);
    int counter = 0;
    while (abs(ev3_motor_get_counts(B) - initial_b) < deg) {
        error = col_get_ref(s2) - col_get_ref(s3);

        pid_value = error * kp + (error - last_error) * kd;

        on(speed, pid_value);

        // fprintf(bt, "%f,%f; ", error, scan_diff);
        last_error = error;
        counter++;
    }
    current_speed = speed;
    display_append("+", counter);
    // fprintf(bt, "\n");
    if (brake) {
        off(brake);
        current_speed = 0;
    }
}

void linefollow_intersection(int speed, bool brake)
{

    FILE* bt = ev3_serial_open_file(EV3_SERIAL_BT);
    int power_b;
    int power_c;
    float kp = 0.4;
    if (speed == 20) {
        kp = 0.5;
    }
    float kd = 50;
    float error = 0;
    float pid_value;
    int last_error = 0;
    int ref_s2 = ev3_color_sensor_get_reflect(EV3_PORT_2);
    int ref_s3 = ev3_color_sensor_get_reflect(EV3_PORT_3);
    int initial_b = ev3_motor_get_counts(EV3_PORT_B);
    while (ref_s2 + ref_s3 > 30 || abs(ev3_motor_get_counts(EV3_PORT_B) - initial_b) < 200) {
        ref_s2 = col_get_ref(s2);
        ref_s3 = col_get_ref(s3);
        error = ref_s2 - ref_s3;

        pid_value = error * kp + (error - last_error) * kd;

        on(speed, pid_value);

        // fprintf(bt, "%f,%f; ", error, scan_diff);
        last_error = error;
    }
    current_speed = speed;
    if (brake) {
        linefollow_slow(40, 90, true);
        current_speed = 0;
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
    current_speed = speed;
    if (brake) {
        ev3_motor_stop(B, true);
        ev3_motor_stop(C, true);
        current_speed = 0;
    }
}

void linefollow_col_1(int speed, int ref_light_s1, bool_t brake)
{
    char output[100];
    int power_b;
    int power_c;
    float kp = 0.5;
    float kd = 50;
    int error = 0;
    float pid_value;
    int last_error = 0;
    int ref_s2 = ev3_color_sensor_get_reflect(S2);
    int ref_s3 = ev3_color_sensor_get_reflect(S3);
    while (ev3_color_sensor_get_reflect(S1) < ref_light_s1) {
        error = col_get_ref(s2) - col_get_ref(s3);

        pid_value = error * kp + (error - last_error) * kd;

        on(speed, pid_value);

        // fprintf(bt, "%f,%f; ", error, scan_diff);
        last_error = error;
    }
    current_speed = speed;
    if (brake) {
        ev3_motor_stop(B, true);
        ev3_motor_stop(C, true);
        current_speed = 0;
    }
}

void linefollow_col_1_greater(int speed, int ref_light_s1, bool_t brake)
{
    char output[100];
    int power_b;
    int power_c;
    float kp = 0.5;
    float kd = 0.2;
    float error = 0;
    float last_error = 0;
    float pid_value = 0.0;
    int ref_s2 = ev3_color_sensor_get_reflect(S2);
    int ref_s3 = ev3_color_sensor_get_reflect(S3);
    while (ev3_color_sensor_get_reflect(S1) > ref_light_s1) {
        error = col_get_ref(s2) - col_get_ref(s3);

        pid_value = error * kp + (error - last_error) * kd;

        on(speed, pid_value);

        // fprintf(bt, "%f,%f; ", error, scan_diff);
        last_error = error;
    }
    current_speed = speed;
    if (brake) {
        ev3_motor_stop(B, true);
        ev3_motor_stop(C, true);
        current_speed = 0;
    }
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
    drive_deg(10, 30, steering, 140, false);
    drive_deg(30, 10, steering, 172, true);
}

void move_up(bool_t block)
{
    act_move(lifter, LIFTER_UP, true);
}

void move_down(bool_t block)
{
    act_move(lifter, LIFTER_INIT, true);
}

char scan(int output_y)
{
    char output[100];
    rgb_t val = col_get_rgb(s4);
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