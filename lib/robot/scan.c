#include "lib/robot/scan.h"

int scan_count;
float sum_rolled_average;
float needs_to_be_subtracted;
float last_value;
float second_last_value;
float_array scanned_values;
float_array rolled_average_values;
float_array maxima_ids;

char simple_scan()
{
    float rel_average = 0.0;
    for (int i = 0; i < SIMPLE_SCAN_COUNT; ++i) {
        rel_average += col_get_rel_rgb(s4, SCAN_RGB_RELATIVE_COLOR);
    }
    rel_average /= SIMPLE_SCAN_COUNT;
    return (rel_average > COLOR_DECIDE_VALUE) ? COLOR_IF_HIGHER : COLOR_IF_LOWER;
}

void init_complex_scan()
{
    scan_count = -MOVING_AVERAGE_COUNT;
    second_last_value = 0.0;
    sum_rolled_average = 0.0;
    needs_to_be_subtracted = 0.0;
    last_value = 0.0;
    second_last_value = 0.0;
    destroy_array(&scanned_values);
    destroy_array(&rolled_average_values);
    destroy_array(&maxima_ids);
    scanned_values = create_float_array(INITIAL_ARRAY_SIZE);
    rolled_average_values = create_float_array(INITIAL_ARRAY_SIZE);
    maxima_ids = create_float_array(INITIAL_ARRAY_SIZE);
}

void complex_scan()
{
    float value = col_get_rel_rgb(s4, SCAN_RGB_RELATIVE_COLOR);
    sum_rolled_average += value / MOVING_AVERAGE_COUNT;
    ++scan_count;
    append_array(&scanned_values, value);
    if (scan_count >= 0) {
        sum_rolled_average -= needs_to_be_subtracted;
        append_array(&rolled_average_values, sum_rolled_average);

        // check if last value was a maximum greater than maximum threshold
        if (second_last_value <= last_value && sum_rolled_average < last_value && last_value >= MAXIMUM_THRESHOLD) {
            append_array(&maxima_ids, scan_count - 1);
        }

        // save values for next iteration
        needs_to_be_subtracted = scanned_values.pointer[scan_count];
        second_last_value = last_value;
        last_value = sum_rolled_average;
    }
    display_set_spot(11, "val", value);
}

char* evaluate_complex_scan(int maxima_count, char* output_path)
{
    // check if last value is also a maximum and if so add it to the maximas
    int index_last_value = rolled_average_values.itemCount - 1;
    if (rolled_average_values.pointer[index_last_value] > rolled_average_values.pointer[index_last_value - 1]) {
        append_array(&maxima_ids, index_last_value);
    }
    float_array selected_maxima_ids = calc_most_signigicant_maximas(&rolled_average_values, &maxima_ids, maxima_count);

    // save data if wanted
    if (output_path != NULL) {
        save_array(&scanned_values, output_path, "w");
        save_array(&rolled_average_values, output_path, "a");
        save_array(&maxima_ids, output_path, "a");
        save_array(&selected_maxima_ids, output_path, "a");
    }

    // evaluate to colors
    char* colors = malloc(sizeof(char) * maxima_count);
    for (int i = 0; i < maxima_count; i++) {
        if (rolled_average_values.pointer[(int)selected_maxima_ids.pointer[i]] > COLOR_DECIDE_VALUE) {
            colors[i] = COLOR_IF_HIGHER;
        } else {
            colors[i] = COLOR_IF_LOWER;
        }
    }
    return colors;
}
