#include "include/core/float_array.h"

int main()
{
    FILE* fp = fopen("utils/data/gruen_blau4.txt", "r");
    float_array array = create_float_array(100);
    float new_value;
    while (fscanf(fp, "%f,", &new_value) == 1) {
        append_array(&array, new_value);
    }
    finish_array(&array);

    printf("Item Count: %i\n", array.itemCount);
    printf("Array Size: %i\n", array.arraySize);

    float_array rolled_average = rolling_average(&array, 200);
    // print_array(&rolled_average);
    save_array(&rolled_average, "utils/output/output_rolled_average.txt");

    printf("Item Count: %i\n", rolled_average.itemCount);
    printf("Array Size: %i\n", rolled_average.arraySize);
}