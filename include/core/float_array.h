#pragma once

#include <stdio.h>
#include <stdlib.h>

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

float_array rolling_average(const float_array* array, int sampleCount);
float_array filter_high_pass(const float_array* array, float threshold);

float_array find_maxima_ids(const float_array* array, float maximaThreshold);
float_array calc_most_signigicant_maximas(const float_array* array, const float_array* maxima_ids, int needed_maximas);

char* evaluate(const float_array* data, int moving_average_count, float high_pass_threshold, float maxima_threshold, int maxima_count, float color_threshold, char* output_path);
