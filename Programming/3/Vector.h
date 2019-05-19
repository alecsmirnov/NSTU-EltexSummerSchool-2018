#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>


typedef struct Elem {
    char name[20];
    double price;
    char date[9];
    uint16_t count;
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
void VectorAdd(Vector* V, Elem E);
void VectorSort(Vector* V);
void VectorPrint(const Vector* V);
void VectorDelete(Vector* V);

void VectorMenu(Vector* V);

#endif

