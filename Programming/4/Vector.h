#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

#define LEN_MAX 255


typedef struct Elem {
    char* str;
} Elem;

typedef struct Vector {
    uint8_t size;
    uint8_t capacity;

    Elem* data;
} Vector;

static inline bool VectorIsEmpty(const Vector* V) {
    return V->data == NULL;
}

void VectorInit(Vector* V, uint8_t capacity);
void VectorPrint(const Vector* V);
void VectorDelete(Vector* V);

void readFile(Vector* V, const char* file_name);

void writeStringsLess(const Vector* V, uint8_t spaces, const char* output_file_name);
void writeMoreSpaces(const Vector* V, uint8_t spaces, const char* output_file_name);

#endif

