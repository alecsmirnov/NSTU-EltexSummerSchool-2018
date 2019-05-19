#ifndef FIELD_H
#define FIELD_H

#include <stdbool.h>
#include <stdint.h>

#include <unistd.h>


typedef enum {LEFT, UP, RIGHT, DOWN} Direction;

typedef struct Position {
    int8_t x;
    int8_t y;
} Position, Target;

typedef struct Scout {
    Position coords;
    Direction direction;
    useconds_t time;
} Scout;

typedef struct Field {
    Scout* scouts;
    uint8_t scouts_count;

    Target* targets;
    uint8_t targets_count;

    int8_t width;
    int8_t height;
} Field;

static inline bool positionCmp(Position A, Target B) {
    return A.x == B.x && A.y == B.y;
}

void fieldInit(Field* field);
void fieldSetSize(Field* field, int8_t width, int8_t height);
void fieldSetScoutsCount(Field* field, uint8_t count, useconds_t time_limit);
void fieldSetTargetsCount(Field* field, uint8_t count);
void fieldClear(Field* field);

void start(Field* field);

#endif
