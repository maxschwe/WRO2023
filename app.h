#pragma once

#define MAIN_PRIORITY 5

#define HIGH_PRIORITY 9
#define MID_PRIORITY 10
#define LOW_PRIORITY 11

#ifndef STACK_SIZE
#define STACK_SIZE 16384
#endif

#ifndef LOOP_REF
#define LOOP_REF ULONG_C(10000)
#endif

#ifndef TOPPERS_MACRO_ONLY

#include "lib/includes.h"

extern void main_task(intptr_t exinf);

#endif
