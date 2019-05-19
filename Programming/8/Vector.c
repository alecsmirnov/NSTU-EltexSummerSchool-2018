#include "Vector.h"

#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#define GROWN_COEFFICIENT 1.5

#define CH_RIGHT "\u2192"


void vectorInit(Vector* V, uint8_t capacity) {
    V->size = 0;
    V->capacity = capacity;

    V->capacity ? (V->data = (Elem*)malloc(sizeof(Elem) * V->capacity)) :
                  (V->data = NULL);
}

void vectorAdd(Vector* V, Elem E) {
    if (V->size == V->capacity) {
        V->capacity *= GROWN_COEFFICIENT;
        if (V->size == V->capacity)
            ++V->capacity;

        V->data = (Elem*)realloc(V->data, sizeof(Elem) * V->capacity);
    }

    V->data[V->size++] = E;
}

void vectorPrint(const Vector* V) {
    if (!vectorIsEmpty(V)) {
        printf("\n");
        for (uint8_t i = 0; i != V->size; ++i)
            printf("Scout[%hhu] has found the Target[%hhu] "CH_RIGHT"  (%hhd, %hhd)\n",
                   V->data[i].scout_id, V->data[i].target_id, V->data[i].coords.x, V->data[i].coords.y);
    }
}

void vectorDelete(Vector* V) {
    free(V->data);
    vectorInit(V, 0);
}
