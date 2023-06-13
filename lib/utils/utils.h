#pragma once

#include <stdbool.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int check_if_char_in_array(char *array, int array_length, char compare_value);
