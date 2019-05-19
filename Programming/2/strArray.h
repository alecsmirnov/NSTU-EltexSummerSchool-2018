#ifndef STRARRAY_H
#define STRARRAY_H

#include <stdio.h>

#define LEN_MAX 255


inline void outputStr(const char** strings, size_t number) {
    printf("%s", strings[number]);
}

void input(char*** strings, size_t* count);
void printStrings(const char** strings, size_t count);
void freeStrings(char*** strings, size_t count);

void sortCase_1(char** strings, size_t count);
void sortCase_2(char** strings, size_t count);
void sortCase_3(char** strings, size_t count);
void sortCase_4(char** strings, size_t count);
void sortCase_5(char** strings, size_t count);
void sortCase_6(char** strings, size_t count);
void sortCase_7(char** strings, size_t count);
void sortCase_8(char** strings, size_t count);
void sortCase_9(char** strings, size_t count);
void sortCase_10(char** strings, size_t count);

#endif
