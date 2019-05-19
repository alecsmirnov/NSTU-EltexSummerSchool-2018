#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>


typedef struct Coords {
    int8_t x;
    int8_t y;
} Coords;

typedef struct Elem {
    uint8_t scout_id;
    uint8_t target_id;
    Coords coords;
} Elem;

typedef struct Vector {
    uint8_t size;
    uint8_t capacity;

    Elem* data;
} Vector;

static inline bool vectorIsEmpty(const Vector* V) {
    return V->data == NULL;
}

void vectorInit(Vector* V, uint8_t capacity);
void vectorAdd(Vector* V, Elem E);
void vectorPrint(const Vector* V);
void vectorDelete(Vector* V);

#endif

