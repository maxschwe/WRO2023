#pragma once

#define MAIN_PRIORITY 5

#define HIGH_PRIORITY 9
#define MID_PRIORITY 10
#define LOW_PRIORITY 11

#ifndef STACK_SIZE
#define STACK_SIZE 4096
#endif

#ifndef LOOP_REF
#define LOOP_REF ULONG_C(1000000)
#endif

#ifndef TOPPERS_MACRO_ONLY

#include "config.h"
#include "ev3api.h"
#include "helpers.h"
#include "target_test.h"

extern void main_task(intptr_t exinf);

#endif
