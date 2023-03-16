#ifndef MOTOR_H
#define MOTOR_H

#include "ev3api.h"
#include <stdbool.h>

typedef struct {
    motor_port_t port;
    motor_type_t type;
    bool counterclockwise;
} Motor;

void m_init(Motor m);
void m_on(Motor m, int speed);
void m_off(Motor m, bool brake);
void m_reset(Motor m);
int m_get_deg(Motor m);

#endif
