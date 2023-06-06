#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "ev3api.h"

#include "lib/robot/helpers.h"

typedef struct {
    Timer stall_timer;
    bool is_currently_stalled;
    float stall_detection_timeout;
} StallDetection;

typedef struct {
    motor_port_t port;
    bool is_large_motor;
    bool counterclockwise;
    StallDetection* stall_detection;
} Motor;

void m_init(Motor m);
void m_on(Motor m, int speed);
void m_off(Motor m, bool brake);
void m_reset(Motor m);
int m_get_deg(Motor m);
int m_get_speed(Motor m);
void m_wait_deg(Motor m, int deg);
void m_on_deg(Motor m, int speed, int deg, bool brake, bool block);
void m_reset_stall(Motor m);
bool m_check_stall(Motor m);
