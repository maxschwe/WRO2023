#include "lib/utils/drive_control.h"

// speed controller
int smooth_deg_acc_end = 0;
int smooth_deg_deacc_start = 0;
int smooth_start_speed = 0;
int smooth_max_speed = 0;
float smooth_current_acc_factor = 0.0;
float smooth_current_deacc_factor = 0.0;
float smooth_acc_a_factor = 0.0;
float smooth_acc_b_factor = 0.0;
float smooth_deacc_a_factor = 0.0;
float smooth_deacc_b_factor = 0.0;

// steering controller
int start_deg_b = 0;
int start_deg_c = 0;
int target_deg_b = 0;
int target_deg_c = 0;
int current_steering = 0;
int is_b_main_motor = true;

void init_smooth_speed_controller(int start_speed, int end_speed, int max_speed_limit, float acc_factor, float deacc_factor, int deg)
{
    max_speed_limit = abs(max_speed_limit);
    deg = abs(deg);
    if (end_speed < 0) {
        deg = -deg;
    }
    // when currently driving in different direction than wanted (probably because robot was not stopped before)
    if ((start_speed >= 0) != (end_speed >= 0)) {
        start_speed = -start_speed;
    }

    // calc max speed (with using limit)
    smooth_max_speed = (deg + start_speed * acc_factor + end_speed * deacc_factor) / (acc_factor + deacc_factor);
    if (end_speed >= 0) {
        smooth_max_speed = MIN(smooth_max_speed, max_speed_limit);
    } else {
        smooth_max_speed = MAX(smooth_max_speed, -max_speed_limit);
    }

    smooth_start_speed = start_speed;
    smooth_current_acc_factor = acc_factor;
    smooth_current_deacc_factor = deacc_factor;

    // degs for acceleration
    smooth_deg_acc_end = acc_factor * (smooth_max_speed - start_speed);
    // degs for deacceleration
    int smooth_deg_deacc = deacc_factor * (smooth_max_speed - end_speed);
    smooth_deg_deacc_start = deg - smooth_deg_deacc;

    // acc x^3 factors
    float smooth_acc_factor = 1.0 * (smooth_max_speed - smooth_start_speed) / (smooth_deg_acc_end * smooth_deg_acc_end);
    smooth_acc_a_factor = -2 * smooth_acc_factor / smooth_deg_acc_end;
    smooth_acc_b_factor = 3 * smooth_acc_factor;

    // deacc x^3 factors
    float smooth_deacc_factor = 1.0 * (end_speed - smooth_max_speed) / (smooth_deg_deacc * smooth_deg_deacc);
    smooth_deacc_a_factor = -2 * smooth_deacc_factor / smooth_deg_deacc;
    smooth_deacc_b_factor = 3 * smooth_deacc_factor;
}

int get_smooth_speed(int deg)
{
    int cur_speed;

    if (abs(deg) < abs(smooth_deg_acc_end)) {
        // accelerating phase
        // int deg_squared = deg * deg;
        // cur_speed = smooth_acc_a_factor * deg_squared * deg + smooth_acc_b_factor * deg_squared + smooth_start_speed;

        // old: constant acceleration
        cur_speed = deg / smooth_current_acc_factor + smooth_start_speed;
    } else if (abs(deg) < abs(smooth_deg_deacc_start)) {
        // max speed phase
        cur_speed = smooth_max_speed;
    } else {
        // deaccelerating phase
        // int deg_relative_to_deacc_start = deg - smooth_deg_deacc_start;
        // int deg_relative_squared = deg_relative_to_deacc_start * deg_relative_to_deacc_start;
        // cur_speed = smooth_deacc_a_factor * deg_relative_squared * deg_relative_to_deacc_start + smooth_deacc_b_factor * deg_relative_squared + smooth_max_speed;

        // old: constant deacceleration
        cur_speed = -(deg - smooth_deg_deacc_start) / smooth_current_deacc_factor + smooth_max_speed;
    }
    return cur_speed;
}

void init_steering_controller(int steering, int deg, int start_b, int start_c, bool is_b_main)
{
    start_deg_b = start_b;
    start_deg_c = start_c;
    current_steering = steering;
    is_b_main_motor = is_b_main;
    if (steering > 0) {
        target_deg_b = deg;
        target_deg_c = deg * (1 - steering / 50.0);
    } else {
        target_deg_b = deg * (1 + steering / 50.0);
        target_deg_c = deg;
    }
}

void get_steering_old(int current_deg_b, int current_deg_c, int* speed, int* steering)
{
    int b_left_deg = target_deg_b - current_deg_b + start_deg_b;
    int c_left_deg = target_deg_c - current_deg_c + start_deg_c;
    int abs_b_left = abs(b_left_deg);
    int abs_c_left = abs(c_left_deg);
    *steering = 1.0 * (b_left_deg - c_left_deg) / MAX(abs_b_left, abs_c_left) * STEERING_CORRECTION_FACTOR;
    bool is_b_main = abs_b_left > abs_c_left;
    if ((is_b_main ? b_left_deg : c_left_deg) < 0) {
        *speed = -*speed;
        *steering = -*steering;
    }
}

void get_steering(int current_deg_b, int current_deg_c, int* speed, int* steering) {
    static int last_error = 0;
    int b_left_deg = target_deg_b - current_deg_b + start_deg_b;
    int c_left_deg = target_deg_c - current_deg_c + start_deg_c;
    int error;
    
    if (is_b_main_motor) {
        int c_should_be_left_deg = b_left_deg * (1 - current_steering / 50.0);
        error = c_should_be_left_deg - c_left_deg;
    } else {
        int b_should_be_left_deg = c_left_deg * (1 + current_steering / 50.0);
        error = b_left_deg - b_should_be_left_deg;
    }
    // display_set_spot(7, "Err", error);
    // display_set_spot(9, "ler", last_error);
    // display_set_spot(4, "b-l", b_left_deg);
    // display_set_spot(5, "c-l", c_left_deg);
    if (*speed > 0) {
        *steering = current_steering + (error * STEERING_KP + (error - last_error) * STEERING_KD);
    } else {
        *steering = current_steering - (error * STEERING_KP + (error - last_error) * STEERING_KD);
    }
    if (*steering > 100) {
        *steering = *steering - 200;
        *speed = -*speed;
    } else if (*steering < -100){
        *steering = *steering + 200;
        *speed = -*speed;
    }
    display_set_spot(11, "st", *steering );
    last_error = error;
}
