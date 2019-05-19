#include <stdio.h>

#include "strArray.h"


int main(int argc, char** argv) {
    char** strings = NULL;
    size_t count = 0;

    input(&strings, &count);

    puts(" ");
    sortCase_10(strings, count);

    puts(" ");
    puts("Sorted:");
    printStrings(strings, count);

    freeStrings(&strings, count);

    return 0;
}
