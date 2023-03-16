#pragma once

#include "ev3api.h"
#include "target_test.h"

#define MAIN_PRIORITY 5

#define HIGH_PRIORITY 9
#define MID_PRIORITY 10
#define LOW_PRIORITY 11

#ifndef STACK_SIZE
#define STACK_SIZE 4096
#endif

#ifndef TOPPERS_MACRO_ONLY

#include <stdio.h>

extern void main_task(intptr_t exinf);

#endif
