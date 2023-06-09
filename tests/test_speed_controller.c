#include "lib/robot/_robot_config.h"
#include "lib/utils/drive_control.h"

#include <stdio.h>

#define DRIVE_END_SPEED DRIVE_START_SPEED
#define DEG 1000

#define TEMP_OUTPUT "data/temp/drive_smooth_output.txt"

int main()
{
    FILE* fp = fopen(TEMP_OUTPUT, "w");
    init_smooth_speed_controller(DRIVE_START_SPEED, DRIVE_END_SPEED, DRIVE_MAX_SPEED, DRIVE_ACC_FACTOR, DRIVE_DEACC_FACTOR, DEG);
    for (int i = 0; i <= DEG; ++i) {
        int current_speed = get_smooth_speed(i);
        fprintf(fp, ";%.2f", (float)current_speed);
    }
    fclose(fp);

    system("python3 utils/plot_drive_smooth.py");
    return 0;
}