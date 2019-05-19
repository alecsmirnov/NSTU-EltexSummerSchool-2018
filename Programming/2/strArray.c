#include "strArray.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>


#define chrToInt(x) ((x) - '0')

static size_t perm_count = 0;


void initStrings(char*** strings, size_t count) {
    *strings = (char**)malloc(sizeof(char*) * count);

    for (size_t i = 0; i != count; ++i)
        (*strings)[i] = NULL;
}

void inputStr(char** str) {
    char buff[LEN_MAX];
    fgets(buff, LEN_MAX, stdin);

    *str = strrchr(buff, '\0');

    size_t length = (size_t)(*str - buff);

    *str = (char*)malloc(sizeof(char) * length);
    strncpy(*str, buff, length);
    (*str)[length - 1] = '\0';
}

void input(char*** strings, size_t* count) {
    printf("Enter the number of strings: ");
    scanf("%zd%*c", count);

    printf("Enter the strings:\n");
    initStrings(strings, *count);
    for (size_t i = 0; i != *count; ++i)
        inputStr(&(*strings)[i]);
}

extern inline void outputStr(const char** strings, size_t number);

void printStrings(const char** strings, size_t count) {
    for (size_t i = 0; i != count; ++i) {
        outputStr(strings, i);
        puts("");
    }
}

void freeStrings(char*** strings, size_t count) {
    for (size_t i = 0; i != count; ++i)
        free((*strings)[i]);
    free(*strings);

    *strings = NULL;
}

size_t wordsCount(char* str) {
    size_t count = 0;

    bool alpha = false;
    for ( ; *str; ++str)
        if (!isspace(*str)) {
            if (alpha == false) {
                alpha = true;
                ++count;
            }
        }
        else
            if (alpha)
                alpha = false;

    return count;
}

size_t getDigitsCount(char* str) {
    size_t count = 0;

    for ( ; *str; ++str)
        if (isdigit(*str))
            ++count;

    return count;
}

int8_t getSecondDigit(char* str) {
    for ( ; *str && !isdigit(*str); ++str);
    ++str;
    for ( ; *str && !isdigit(*str); ++str);

    return isdigit(*str) ? chrToInt(*str) : -1;
}

size_t getFirstWordLen(char* str) {
    size_t length = 0;

    for ( ; *str && !isalpha(*str); ++str);
    for ( ; *str && isalpha(*str); ++str)
        ++length;

    return length;
}

int comp_1(const void* str_1, const void* str_2) {
    int result = 0;
    result = strlen(*(char**)str_1) > strlen(*(char**)str_2) ? 1 : -1;

    if (result == -1)
        ++perm_count;

    return result;
}

int comp_2(const void* str_1, const void* str_2) {
    int result = 0;
    result = strlen(*(char**)str_1) < strlen(*(char**)str_2) ? 1 : -1;

    if (result == 1)
        ++perm_count;

    return result;
}

int comp_3(const void* str_1, const void* str_2) {
    int result = strcmp(*(char**)str_1, *(char**)str_2);

    if (result == 1)
        ++perm_count;

    return result;
}

int comp_4(const void* str_1, const void* str_2) {
    int result = strcmp(*(char**)str_2, *(char**)str_1);

    if (result == -1)
        ++perm_count;

    return result;
}

int comp_5(const void* str_1, const void* str_2) {
    int result = 0;
    result = wordsCount(*(char**)str_1) > wordsCount(*(char**)str_2) ? 1 : -1;

    if (result == -1)
        ++perm_count;

    return result;
}

int comp_6(const void* str_1, const void* str_2) {
    int result = 0;
    result = wordsCount(*(char**)str_1) < wordsCount(*(char**)str_2) ? 1 : -1;

    if (result == 1)
        ++perm_count;

    return result;
}

int comp_7(const void* str_1, const void* str_2) {
    size_t val_1 = getDigitsCount(*(char**)str_1);
    size_t val_2 = getDigitsCount(*(char**)str_2);

    int result = 0;
    result = val_1 > val_2 ? 1 : -1;

    return result;
}

int comp_8(const void* str_1, const void* str_2) {
    size_t val_1 = getDigitsCount(*(char**)str_1);
    size_t val_2 = getDigitsCount(*(char**)str_2);

    int result = 0;
    result = val_1 < val_2 ? 1 : -1;

    if (result == 1)
        ++perm_count;

    return result;
}

int comp_9(const void* str_1, const void* str_2) {
    size_t word_1 = getFirstWordLen(*(char**)str_1);
    size_t word_2 = getFirstWordLen(*(char**)str_2);

    int result = 0;
    result = word_1 > word_2 ? 1 : -1;

    if (result == 1)
        ++perm_count;

    return result;
}

int comp_10(const void* str_1, const void* str_2) {
    size_t word_1 = getFirstWordLen(*(char**)str_1);
    size_t word_2 = getFirstWordLen(*(char**)str_2);

    int result = 0;
    result = word_1 < word_2 ? 1 : -1;

    return result;
}

void sortStrings(char** strings, size_t count, int (*comp)(const void* str_1, const void* str_2)) {
    qsort(strings, count, sizeof(char**), comp);
}

void sortCase_1(char** strings, size_t count) {
    sortStrings(strings, count, comp_1);

    printf("Permutation count: %zd\n", perm_count);
    printf("Min length of string: %zd\n", strlen(strings[0]));
    perm_count = 0;
}

void sortCase_2(char** strings, size_t count) {
    sortStrings(strings, count, comp_2);

    printf("Permutation count: %zd\n", perm_count);
    printf("Max length of string: %zd\n", strlen(strings[0]));
    perm_count = 0;
}

void sortCase_3(char** strings, size_t count) {
    sortStrings(strings, count, comp_3);

    printf("Permutation count: %zd\n", perm_count);
    printf("First letter of the first str: %c\n", strings[0][0]);
    perm_count = 0;
}

void sortCase_4(char** strings, size_t count) {
    sortStrings(strings, count, comp_4);

    printf("Permutation count: %zd\n", perm_count);
    printf("Length of the first str: %zd\n", strlen(strings[0]));
    perm_count = 0;
}

void sortCase_5(char** strings, size_t count) {
    sortStrings(strings, count, comp_5);

    printf("Permutation count: %zd\n", perm_count);
    printf("First letter of the last str: %c\n", strings[count - 1][0]);
    perm_count = 0;
}

void sortCase_6(char** strings, size_t count) {
    sortStrings(strings, count, comp_6);

    printf("Permutation count: %zd\n", perm_count);
    printf("Max count of the words: %zd\n", wordsCount(strings[0]));
    perm_count = 0;
}

void sortCase_7(char** strings, size_t count) {
    sortStrings(strings, count, comp_7);

    printf("String:\tDigits count:\tSecond digit:\n");
    for (size_t i = 0; i != count; ++i) {
        outputStr(strings, i);
        printf("\t%zd", getDigitsCount(strings[i]));
        printf("\t%d\n", getSecondDigit(strings[i]));
    }
}

void sortCase_8(char** strings, size_t count) {
    sortStrings(strings, count, comp_8);

    printf("Permutation count: %zd\n", perm_count);
    printf("String:\tDigits count:\n");
    for (size_t i = 0; i != count; ++i) {
        outputStr(strings, i);
        printf("\t%zd\n", getDigitsCount(strings[i]));
    }
    perm_count = 0;
}

void sortCase_9(char** strings, size_t count) {
    sortStrings(strings, count, comp_9);

    printf("Permutation count: %zd\n", perm_count);
    printf("Max length of the word: %zd\n", getFirstWordLen(strings[count - 1]));
    perm_count = 0;
}

void sortCase_10(char** strings, size_t count) {
    sortStrings(strings, count, comp_10);

    printf("Words in the first str: %zd\n", wordsCount(strings[0]));
    printf("Min length of the word: %zd\n", getFirstWordLen(strings[count - 1]));
}
