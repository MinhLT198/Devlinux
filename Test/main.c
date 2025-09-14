#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SQRT(x) ((x) * (x))

int number = 42;
int number1 = 0;

int main() {
    int numa = 3;
    int numa2 = SQRT(numa++);
    printf("a = %d, a2 = %d\n",numa, numa2);
    return 0;
}