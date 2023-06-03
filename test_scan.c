#define LOCAL_TEST

#include "lib/robot/_robot_config.h"
#include "lib/utils/float_array.h"

#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define MAXIMA_COUNT 2
#define TEMP_DATA_PATH "utils/data/temp_data.txt"

#define DOWNLOAD 1

void load_file(const char* filename, float_array* data_array, float_array* rolled_average_array, float_array* maxima_ids)
{
    FILE* fp = fopen(filename, "r");
    float new_value;
    fscanf(fp, ",%f", &new_value);
    append_array(data_array, new_value);
    while (getc(fp) != '\n') {
        fscanf(fp, "%f", &new_value);
        append_array(data_array, new_value);
    }
    // print_array(data_array);
    fscanf(fp, ",%f", &new_value);
    append_array(rolled_average_array, new_value);
    while (getc(fp) != '\n') {
        fscanf(fp, "%f", &new_value);
        append_array(rolled_average_array, new_value);
    }
    // print_array(rolled_average_array);
    fscanf(fp, ",%f", &new_value);
    append_array(maxima_ids, new_value);
    while (getc(fp) != '\n') {
        fscanf(fp, "%f", &new_value);
        append_array(maxima_ids, new_value);
    }

    finish_array(data_array);
    finish_array(rolled_average_array);
    finish_array(maxima_ids);
}

int main()
{
    // copy files from robot if wanted
    if (DOWNLOAD) {
        // system("cp /media/max/EV3_WRO/scan.txt ~/Dokumente/ev3/ev3rt-hrp3/sdk/workspace/WRO2023/utils/data/scan.txt");
        system("cp /media/max/EV3_WRO/scan.txt ~/Dokumente/ev3/ev3rt-hrp3/sdk/workspace/WRO2023/utils/data/scan.txt");

        printf("Copyied files from robot\n");
    }

    // open directory
    DIR* dir;
    struct dirent* subdir;
    char full_path[1000];
    char dir_path[100] = "utils/data";
    dir = opendir(dir_path);
    if (!dir) {
        return 1;
    }
    char python_exec_path[100];
    sprintf(python_exec_path, "python3 utils/plot_scan.py");

    while ((subdir = readdir(dir)) != NULL) {
        if (subdir->d_type != DT_REG) {
            continue;
        }
        sprintf(full_path, "%s/%s", dir_path, subdir->d_name);
        printf("-------------------------------------\n");
        printf("%s\n", subdir->d_name);
        float_array data = create_float_array(INITIAL_ARRAY_SIZE);
        float_array rolled_average = create_float_array(INITIAL_ARRAY_SIZE);
        float_array maxima_ids = create_float_array(INITIAL_ARRAY_SIZE);
        load_file(full_path, &data, &rolled_average, &maxima_ids);

        int index_last_value = rolled_average.itemCount - 1;
        if (rolled_average.pointer[index_last_value] > rolled_average.pointer[index_last_value - 1]) {
            append_array(&maxima_ids, index_last_value);
        }
        float_array selected_maxima_ids = calc_most_signigicant_maximas(&rolled_average, &maxima_ids, MAXIMA_COUNT);

        // save data if wanted
        if (TEMP_DATA_PATH != NULL) {
            save_array(&data, TEMP_DATA_PATH, "w");
            save_array(&rolled_average, TEMP_DATA_PATH, "a");
            save_array(&maxima_ids, TEMP_DATA_PATH, "a");
            save_array(&selected_maxima_ids, TEMP_DATA_PATH, "a");
        }

        // evaluate to colors
        char* colors = malloc(sizeof(char) * MAXIMA_COUNT);
        for (int i = 0; i < MAXIMA_COUNT; i++) {
            if (rolled_average.pointer[(int)selected_maxima_ids.pointer[i]] > COLOR_DECIDE_VALUE) {
                colors[i] = COLOR_IF_HIGHER;
            } else {
                colors[i] = COLOR_IF_LOWER;
            }
        }
        for (int i = 0; i < MAXIMA_COUNT; ++i) {
            printf("Color %i: %s\n", i, colors[i] == 'b' ? "blau" : "green");
        }
        system(python_exec_path);

        destroy_array(&data);
        destroy_array(&rolled_average);
        destroy_array(&maxima_ids);
        free(colors);
    }
    closedir(dir);

    return 0;
}