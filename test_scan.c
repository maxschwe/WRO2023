#include "include/core/float_array.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define MOVING_AVERAGE_COUNT 200
#define HIGH_PASS_THRESHOLD 0.1
#define MAXIMA_THRESHOLD 0.2
#define MAXIMA_COUNT 2
#define COLOR_THRESHOLD 0.48
#define OUTPUT_PATH "utils/output/scan1.txt"

#define DOWNLOAD 1

float_array load_file(const char* filename)
{
    FILE* fp = fopen(filename, "r");
    float_array array = create_float_array(100);
    float new_value;
    while (fscanf(fp, "%f,", &new_value) == 1) {
        append_array(&array, new_value);
    }
    finish_array(&array);
    return array;
}

int main()
{
    if (DOWNLOAD) {
        system("cp /media/max/EV3_WRO/scan1.txt ~/Dokumente/ev3/ev3rt-hrp3/sdk/workspace/WRO2023/utils/data/scan.txt");
        system("cp /media/max/EV3_WRO/data.txt ~/Dokumente/ev3/ev3rt-hrp3/sdk/workspace/WRO2023/utils/data/data.txt");

        printf("Copyied files from robot\n");
    }
    DIR* dir;

    struct dirent* subdir;
    char full_path[1000];
    char dir_path[100] = "utils/data";
    dir = opendir(dir_path);
    if (!dir) {
        return 1;
    }
    char python_exec_path[100];
    sprintf(python_exec_path, "python3 utils/plot_data.py %s", OUTPUT_PATH);
    while ((subdir = readdir(dir)) != NULL) {
        if (subdir->d_type != DT_REG) {
            continue;
        }
        sprintf(full_path, "%s/%s", dir_path, subdir->d_name);
        float_array data = load_file(full_path);
        printf("-------------------------------------\n");
        printf("%s\n", subdir->d_name);
        if (strcmp(subdir->d_name, "data.txt") != 0) {
            char* colors = evaluate(&data, MOVING_AVERAGE_COUNT, HIGH_PASS_THRESHOLD, MAXIMA_THRESHOLD, MAXIMA_COUNT, COLOR_THRESHOLD, OUTPUT_PATH);
            for (int i = 0; i < MAXIMA_COUNT; ++i) {
                printf("Color %i: %s\n", i, colors[i] == 'b' ? "blau" : "green");
            }
        } else {
            save_array(&data, OUTPUT_PATH, "w");
        }
        system(python_exec_path);
    }
    closedir(dir);

    return 0;
}