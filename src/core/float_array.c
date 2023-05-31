#include "../../include/core/float_array.h"
#include <stdbool.h>
#include <unistd.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))


int scan_count;
float sum_rolled_average;
float needs_to_be_subtracted;
float sum_rolled_average;
float last_value;
float second_last_value;
float_array temp_scanned_values;
float_array maxima_ids;

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
        // printf("Increasing array size from %i to %i\n", array->arraySize, newSize);
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
        // printf("Decreasing array size from %i to %i\n", array->arraySize, newSize);
        float* new_pointer = realloc(array->pointer, newSize * sizeof(float));
        if (new_pointer == NULL) {
            exit(EXIT_FAILURE);
        }
        array->pointer = new_pointer;
        array->arraySize = newSize;
    }
}

void destroy_array(float_array* array)
{
    if (array != NULL) {
        free(array->pointer);
    }
}

void print_array(const float_array* array)
{
    for (int i = 0; i < array->itemCount; ++i) {
        printf("Value %i: %.3f\n", i, array->pointer[i]);
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

float_array filter_high_pass(const float_array* array, float threshold)
{
    float_array high_pass_filtered = create_float_array(INITIAL_ARRAY_SIZE);
    for (int i = 0; i < array->itemCount; ++i) {
        if (array->pointer[i] > threshold) {
            // display_set_spot(5, "a", i);
            append_array(&high_pass_filtered, array->pointer[i]);
        }
    }
    finish_array(&high_pass_filtered);
    return high_pass_filtered;
}

void save_array(const float_array* array, const char* filepath, const char* mode)
{
    FILE* fp = fopen(filepath, mode);
    for (int i = 0; i < array->itemCount; ++i) {
        fprintf(fp, "%f,", array->pointer[i]);
    }
    fprintf(fp, "\n");
    fclose(fp);
}

float_array find_maxima_ids(const float_array* array, float maximaThreshold)
{
    float_array maxima_ids = create_float_array(10);

    // first and last values can also be maximas
    float first_value = array->pointer[0];
    float second_value = array->pointer[1];
    if (first_value > second_value && first_value > maximaThreshold) {
        append_array(&maxima_ids, 0);
    }

    float last_value = array->pointer[array->itemCount - 1];
    float pre_last_value = array->pointer[array->itemCount - 2];
    if (last_value > pre_last_value && last_value > maximaThreshold) {
        append_array(&maxima_ids, array->itemCount - 1);
    }

    float prev_value = first_value;
    float current_value = second_value;
    float next_value;
    for (int i = 2; i < array->itemCount - 1; ++i) {
        // display_set_spot(6, "a", i);
        next_value = array->pointer[i + 1];
        if (prev_value <= current_value && current_value > next_value && current_value > maximaThreshold) {
            append_array(&maxima_ids, i);
        }
        prev_value = current_value;
        current_value = next_value;
    }

    finish_array(&maxima_ids);
    return maxima_ids;
}

int comp(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

float_array calc_most_signigicant_maximas(const float_array* array, const float_array* maxima_ids, int needed_maximas)
{
    float_array significances = create_float_array(maxima_ids->itemCount);
    float_array selected_maxima_ids = create_float_array(needed_maximas);
    int maximaCount = maxima_ids->itemCount;
    int significance = 0;

    // calc significances of maximas
    for (int i = 0; i < maximaCount; ++i) {
        int bottomSignificance = array->itemCount;
        int upSignificance = bottomSignificance;
        int currentId = maxima_ids->pointer[i];
        float currentValue = array->pointer[currentId];
        int significanceCount = 0;
        for (int i = currentId - 1; i >= 0; --i) {
            // display_set_spot(8, "a", i);
            if (currentValue <= array->pointer[i]) {
                bottomSignificance = significanceCount;
                break;
            }
            significanceCount++;
        }
        significanceCount = 0;
        for (int i = currentId + 1; i < array->itemCount; ++i) {
            if (currentValue < array->pointer[i]) {
                upSignificance = significanceCount;
                break;
            }
            significanceCount++;
        }
        significance = MIN(bottomSignificance, upSignificance);
        append_array(&significances, significance);
    }
    finish_array(&significances);

    // calc most significant maximas
    for (int i = 0; i < needed_maximas; ++i) {
        int hightestSignificance = 0;
        selected_maxima_ids.pointer[i] = array->itemCount - 1;
        for (int j = 0; j < maximaCount; ++j) {
            if (significances.pointer[j] >= hightestSignificance) {
                // check if is not already included
                bool is_included = false;
                for (int k = 0; k < i; ++k) {
                    if (maxima_ids->pointer[j] == selected_maxima_ids.pointer[k]) {
                        is_included = true;
                        break;
                    }
                }
                if (!is_included) {
                    hightestSignificance = significances.pointer[j];
                    selected_maxima_ids.pointer[i] = maxima_ids->pointer[j];
                }
            }
        }
        selected_maxima_ids.itemCount++;
    }

    // sort array
    qsort(selected_maxima_ids.pointer, needed_maximas, sizeof(float), comp);
    finish_array(&selected_maxima_ids);

    for (int i = 0; i < needed_maximas; ++i) {
        printf("Id: %i, %f\n", (int)selected_maxima_ids.pointer[i], array->pointer[(int)selected_maxima_ids.pointer[i]]);
    }
    return selected_maxima_ids;
}

char* evaluate(const float_array* data, const float_array* rolled_average, const float_array* maxima_ids, int maxima_count, char* output_path)
{
    // float_array rolled_average = rolling_average(data, MOVING_AVERAGE_COUNT);
    // float_array high_pass_filtered = filter_high_pass(&rolled_average, high_pass_threshold);
    // float_array maxima_ids = find_maxima_ids(data, maxima_threshold);
    float_array selected_maxima_ids = calc_most_signigicant_maximas(rolled_average, maxima_ids, maxima_count);

    if (output_path != NULL) {
        save_array(data, output_path, "w");
        save_array(rolled_average, output_path, "a");
        save_array(maxima_ids, output_path, "a");
        save_array(&selected_maxima_ids, output_path, "a");
    }

    // evaluate to colors
    char* colors = malloc(sizeof(char) * maxima_count);
    for (int i = 0; i < maxima_count; i++) {
        if (data->pointer[(int)selected_maxima_ids.pointer[i]] > COLOR_THRESHOLD) {
            colors[i] = 'b';
        } else {
            colors[i] = 'g';
        }
    }
    return colors;
}

void reset_scan()
{
    scan_count = -MOVING_AVERAGE_COUNT;
    last_value = 0.0;
    second_last_value = 0.0;
    sum_rolled_average = 0.0;
    needs_to_be_subtracted = 0.0;
    sum_rolled_average = 0.0;
    destroy_array(&temp_scanned_values);
    destroy_array(&maxima_ids);
    temp_scanned_values = create_float_array(INITIAL_ARRAY_SIZE);
    maxima_ids = create_float_array(INITIAL_ARRAY_SIZE);
}
