#include "Vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define GROWN_COEFFICIENT 1.5

#define MENU_EXIT 4

#define chrToInt(x) ((x) - '0')


void VectorInit(Vector* V, uint8_t capacity) {
    V->size = 0;
    V->capacity = capacity;

    V->capacity ? (V->data = (Elem*)malloc(sizeof(Elem) * V->capacity)) :
                  (V->data = NULL);
}

void VectorElemAssign(Elem* E1, Elem E2) {
    strcpy(E1->name, E2.name);
    E1->price = E2.price;
    strcpy(E1->date, E2.date);
    E1->count = E2.count;
}

void VectorAdd(Vector* V, Elem E) {
    if (V->size == V->capacity) {
        V->capacity *= GROWN_COEFFICIENT;
        if (V->size == V->capacity)
            ++V->capacity;

        V->data = (Elem*)realloc(V->data, sizeof(Elem) * V->capacity);
    }

    VectorElemAssign(&V->data[V->size++], E);
}

uint8_t getMonth(const char* date) {
    uint8_t val = 0;

    for (uint8_t i = 0; i != 2; ++i)
        val = 10 * val + chrToInt(date[i + 3]);

    return val;
}

int comp(const void* E1, const void* E2) {
    const Elem* elem1 = (const Elem*)E1;
    const Elem* elem2 = (const Elem*)E2;

    int result = 0;
    result = getMonth(elem1->date) > getMonth(elem2->date) ? 1 : -1;

    return result;
}

void VectorSort(Vector* V) {
    qsort(V->data, V->size, sizeof(Elem), comp);
}

void VectorPrint(const Vector* V) {
    if (VectorIsEmpty(V))
        puts("Vector is Empty!");
    else {
        printf("Name:\tPrice:\tDate:\t\tCount:\n");

        for (uint8_t i = 0; i != V->size; ++i)
            printf("%s\t%.2f\t%s\t%hhu\n",
                   V->data[i].name, V->data[i].price,
                   V->data[i].date, V->data[i].count);
    }
}

void VectorDelete(Vector* V) {
    free(V->data);
    VectorInit(V, 0);
}

void VectorMenu(Vector* V) {
    uint8_t choice = 1;

    while (choice != MENU_EXIT) {
        puts("\"Vector menu\"");
        puts("1. Add");
        puts("2. Print");
        puts("3. Sort");
        printf("%d. Exit\n", MENU_EXIT);

        puts("Select item:");
        scanf("%hhu", &choice);

        switch (choice) {
            case 1: {
                Elem E;
                puts("Entaer name:");
                scanf("%s%*c", E.name);
                puts("Entaer price:");
                scanf("%lf%*c", &E.price);
                puts("Entaer date:");
                scanf("%s%*c", E.date);
                puts("Entaer count:");
                scanf("%hu%*c", &E.count);

                VectorAdd(V, E);
                break;
            }
            case 2: {
                VectorPrint(V);
                break;
            }
            case 3: {
                VectorSort(V);
                break;
            }
            case MENU_EXIT: {
                choice = MENU_EXIT;
                break;
            }
            default:;
        }
        puts("");
    }
}
