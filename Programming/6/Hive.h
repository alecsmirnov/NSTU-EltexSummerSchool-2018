#ifndef HIVE_H
#define HIVE_H

#include <stdbool.h>


typedef struct Hive {
	double honey;

    double capacity;
} Hive;

static inline bool isEmpty(const Hive* H) {
    return H->honey == 0;
}

static inline bool isFull(const Hive* H) {
    return H->honey == H->capacity;
}

void hiveInit(Hive* H, double capacity);
void addHoney(Hive* H, double portion);
double getHoney(Hive* H, double portion);

#endif
