#include "lib/utils/utils.h"

int check_if_char_in_array(char *array, int array_length, char compare_value) {
    for (int i = 0; i < array_length; ++i) {
        if (array[i] == compare_value) {
            return i;
        }
    }
    return -1;
}
