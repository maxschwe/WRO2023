#include "../../include/core/float_array.h"
#include <unistd.h>

float_array create_float_array(int initialSize)
{
    float* pointer = malloc(initialSize * sizeof(float));
    float_array array = { .pointer = pointer, .arraySize = initialSize, .itemCount = 0 };
    return array;
}

void append_array(float_array* array, float value)
{
    // increase array size if necessary
    if (array->itemCount >= array->arraySize) {
        int newSize = (int)(REALLOC_FACTOR * array->arraySize);
        printf("Increasing array size from %i to %i\n", array->arraySize, newSize);
        float* new_pointer = realloc(array->pointer, newSize * sizeof(float));
        if (new_pointer == NULL) {
            exit(EXIT_FAILURE);
        }
        array->pointer = new_pointer;
        array->arraySize = newSize;
    }

    // save value
    array->pointer[array->itemCount++] = value;
}

void finish_array(float_array* array)
{
    // reduce array size to end size
    if (array->itemCount < array->arraySize) {
        int newSize = array->itemCount;
        printf("Decreasing array size from %i to %i\n", array->arraySize, newSize);
        float* new_pointer = realloc(array->pointer, newSize * sizeof(float));
        if (new_pointer == NULL) {
            exit(EXIT_FAILURE);
        }
        array->pointer = new_pointer;
        array->arraySize = newSize;
    }
}

void print_array(const float_array* array)
{
    for (int i = 0; i < array->itemCount; ++i) {
        printf("Value %i: %.3f\n", i, array->pointer[i]);
        usleep(1000);
    }
}

float_array rolling_average(const float_array* array, int sampleCount)
{
    float_array rolled_average = create_float_array(INITIAL_ARRAY_SIZE);

    // sample count higher than item count -> calculate simple average of all values
    if (sampleCount > array->itemCount) {
        int sum = 0;
        for (int i = 0; i < array->itemCount; ++i) {
            sum += array->pointer[i];
        }
        append_array(&rolled_average, 1.0 * sum / array->itemCount);
    } else {
        float lastFirstValue = 0;
        float lastRolledSum = 0;
        for (int i = 0; i < sampleCount - 1; ++i) {
            lastRolledSum += array->pointer[i];
        }
        for (int i = 0; i <= array->itemCount - sampleCount; ++i) {
            lastRolledSum = -lastFirstValue + lastRolledSum + array->pointer[i + sampleCount - 1];
            float newValue = 1.0 * lastRolledSum / sampleCount;
            lastFirstValue = array->pointer[i];
            append_array(&rolled_average, newValue);
        }
    }
    finish_array(&rolled_average);
    return rolled_average;
}

float_array filter_high_pass(const float_array* array)
{
}

void save_array(const float_array* array, char* filepath)
{
    FILE* fp = fopen(filepath, "w");
    for (int i = 0; i < array->itemCount; ++i) {
        fprintf(fp, "%f,", array->pointer[i]);
    }
}