#include "Vector.h"

#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#define GROWN_COEFFICIENT 1.5

#define chrToInt(x) ((x) - '0')


void VectorInit(Vector* V, uint8_t capacity) {
    V->size = 0;
    V->capacity = capacity;

    V->capacity ? (V->data = (Elem*)malloc(sizeof(Elem) * V->capacity)) :
                  (V->data = NULL);
}

void VectorInc(Vector* V) {
    if (V->size == V->capacity) {
        V->capacity *= GROWN_COEFFICIENT;
        if (V->size == V->capacity)
            ++V->capacity;

        V->data = (Elem*)realloc(V->data, sizeof(Elem) * V->capacity);
    }

    ++V->size;
}

void VectorAdd(Vector* V, Elem E) {
    V->data[V->size - 1].str = (char*)malloc(sizeof(char) * strlen(E.str));
    strcpy(V->data[V->size - 1].str, E.str);
}

void VectorPrint(const Vector* V) {
    if (VectorIsEmpty(V))
        puts("Vector is Empty!");
    else {
        printf("Strings count: %hhu\n", V->size);

        for (uint8_t i = 0; i != V->size; ++i)
            printf("%s\n", V->data[i].str);
    }
}

void VectorDelete(Vector* V) {
    free(V->data);
    VectorInit(V, 0);
}

void buffToStr(const char* buff, char** str) {
    *str = strrchr(buff, '\0');

    size_t length = (size_t)(*str - buff);

    *str = (char*)malloc(sizeof(char) * length);
    strncpy(*str, buff, length);
    (*str)[length - 1] = '\0';
}

void readFile(Vector* V, const char* file_name) {
    FILE* fp = NULL;
    if ((fp = fopen(file_name, "r")) == NULL)
        fprintf(stderr, "Unable to open \"%s\"\n", file_name);

    char* str = NULL;
    char buff[LEN_MAX];

    while (fgets(buff, sizeof(buff), fp) != NULL) {
        VectorInc(V);
        buffToStr(buff, &str);
        VectorAdd(V, (Elem){str});
    }

    free(str);

    if (fclose(fp) != 0)
        fprintf(stderr, "Unable to close \"%s\"\n", file_name);
}

void writeStringsLess(const Vector* V, uint8_t spaces, const char* output_file_name) {
    FILE* fp = NULL;
    if ((fp = fopen(output_file_name, "w")) == NULL)
        fprintf(stderr, "Unable to open \"%s\"\n", output_file_name);

    uint8_t count = 0;

    for (uint8_t line = 0; line != V->size; ++line, count = 0) {
        for (char* ptr = V->data[line].str; *ptr != '\0'; ++ptr)
            if (isspace(*ptr))
                ++count;

        if (count < spaces) {
            fputs(V->data[line].str, fp);
            fputc('\n', fp);
        }
    }

    if (fclose(fp) != 0)
        fprintf(stderr, "Unable to close \"%s\"\n", output_file_name);
}

void writeMoreSpaces(const Vector* V, uint8_t spaces, const char* output_file_name) {
    FILE* fp = NULL;
    if ((fp = fopen(output_file_name, "w")) == NULL)
        fprintf(stderr, "Unable to open \"%s\"\n", output_file_name);

    for (uint8_t line = 0; line != V->size; ++line) {
        for (char* ptr = V->data[line].str; *ptr != '\0'; ++ptr)
            if (!isspace(*ptr))
                fputc(*ptr, fp);
            else {
                char* str_spaces = (char*)malloc(spaces + 1);
                memset(str_spaces, ' ', spaces);
                str_spaces[spaces] = '\0';

                fputs(str_spaces, fp);
                free(str_spaces);
            }

        fputc('\n', fp);
    }

    if (fclose(fp) != 0)
        fprintf(stderr, "Unable to close \"%s\"\n", output_file_name);
}
