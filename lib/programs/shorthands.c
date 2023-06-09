#include "lib/programs/shorthands.h"

void move_lifter_up(bool block)
{
    act_move(lifter, LIFTER_UP, block);
}

void move_lifter_down(bool block)
{
    act_move(lifter, LIFTER_INIT, block);
}

void lifter_collect(bool block)
{
    move_lifter_up(true);
    move_lifter_down(block);
}
