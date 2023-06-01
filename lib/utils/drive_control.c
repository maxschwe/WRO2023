#include "lib/utils/drive_control.h"

// speed controller
int smooth_deg_acc_end = 0;
int smooth_deg_deacc_start = 0;
int smooth_max_speed = 0;
int smooth_start_speed = 0;
float smooth_current_acc_factor = 0.0;
float smooth_current_deacc_factor = 0.0;

// steering controller
int start_deg_b = 0;
int start_deg_c = 0;
int target_deg_b = 0;
int target_deg_c = 0;

void init_smooth_speed_controller(int start_speed, int end_speed, int max_speed_limit, float acc_factor, float deacc_factor, int deg)
{
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

    smooth_deg_acc_end = acc_factor * (smooth_max_speed - start_speed);
    smooth_deg_deacc_start = deg - deacc_factor * (smooth_max_speed - end_speed);
    smooth_start_speed = start_speed;
    smooth_current_acc_factor = acc_factor;
    smooth_current_deacc_factor = deacc_factor;
}

int get_smooth_speed(int deg)
{
    int cur_speed;

    // TODO: make s curves

    // accelerating phase
    if (abs(deg) < abs(smooth_deg_acc_end)) {
        cur_speed = deg / smooth_current_acc_factor + smooth_start_speed;
    // max speed phase
    } else if (abs(deg) < abs(smooth_deg_deacc_start)) {
        cur_speed = smooth_max_speed;
    // deaccelerating phase
    } else {
        cur_speed = -(deg - smooth_deg_deacc_start) / smooth_current_deacc_factor + smooth_max_speed;
    }
    return cur_speed;
}

void init_steering_controller(int steering, int deg, int start_b, int start_c) {
    start_deg_b = start_b;
    start_deg_c = start_c;
    if (steering > 0) {
        target_deg_b = deg;
        target_deg_c = deg * (1 - steering / 50.0);
    } else {
        target_deg_b = deg * (1 + steering / 50.0);
        target_deg_c = deg;
    }
}

void get_steering(int current_deg_b, int current_deg_c, int *speed, int* steering) {
    int b_left_deg = target_deg_b - current_deg_b + start_deg_b;
    int c_left_deg = target_deg_c - current_deg_c + start_deg_c;
    int abs_b_left = abs(b_left_deg);
    int abs_c_left = abs(c_left_deg);
    *steering = ((b_left_deg - c_left_deg) / MAX(abs_b_left, abs_c_left)) * STEERING_CORRECTION_FACTOR;
    bool is_b_main = abs_b_left > abs_c_left;
    if ((is_b_main ? b_left_deg : c_left_deg) < 0) {
        *speed = - *speed;
        *steering = - *steering;
    }
}
