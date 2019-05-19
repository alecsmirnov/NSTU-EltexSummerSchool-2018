#ifndef CIRCLEOFLIFE_H
#define CIRCLEOFLIFE_H

#include <stdio.h>
#include <inttypes.h>
#include "Hive.h"

#define FILE_NAME "/tmp/pipe.tmp"


typedef uint8_t sec_t;

typedef struct Pooh {
    double portion;

    sec_t time;
} Pooh;

typedef struct Bee {
    double portion;

    sec_t time_limit;
    uint8_t count;
} Bee;

typedef struct Object {
    double portion;

    uint8_t time;
    uint8_t id;
} Object;

typedef struct Life {
    Pooh pooh;
    Bee bees;
    Hive hive;

    Object last_visited;
} Life;

static inline bool isEmptyHive(const Life* L) {
    return isEmpty(&L->hive);
}

static inline bool isFullHive(const Life* L) {
    return isFull(&L->hive);
}

static inline bool isDepletion(const Life* L) {
    return L->hive.honey < L->pooh.portion;
}

void poohInit(Pooh* pooh, double portion, sec_t time);
void beesInit(Bee* bee, double portion, sec_t time_limit, uint8_t count);
void start(Life* life);

#endif
