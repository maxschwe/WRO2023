#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib/utils/utils.h"

#define REALLOC_FACTOR 2.0
#define INITIAL_ARRAY_SIZE 100

typedef struct {
    float* pointer;
    int arraySize;
    int itemCount;
} float_array;

float_array create_float_array(int initialSize);
void append_array(float_array* array, float value);
void finish_array(float_array* array);
void print_array(const float_array* array);
void save_array(const float_array* array, const char* filepath, const char* mode);
void destroy_array(float_array* array);

float_array rolling_average(const float_array* array, int sampleCount);
float_array filter_high_pass(const float_array* array, float threshold);

float_array find_maxima_ids(const float_array* array, float maximaThreshold);
float_array calc_most_signigicant_maximas(const float_array* array, const float_array* maxima_ids, int needed_maximas);
