#include <stdio.h>

#define PARAM 1

void test(float param) {
    printf("%i", param);
}

int main() {
    test(PARAM);
    return 0;
}   
