#include "Field.h"

#define FIELD_WIDTH  10
#define FIELD_HEIGHT 10

#define SCOUTS_COUNT      5
#define SCOUTS_TIME_LIMIT 900000

#define TARGETS_COUNT 10


int main(int argc, char** argv) {
    Field f;

    fieldInit(&f);
    fieldSetSize(&f, FIELD_WIDTH, FIELD_HEIGHT);

    fieldSetScoutsCount(&f, SCOUTS_COUNT, SCOUTS_TIME_LIMIT);
    fieldSetTargetsCount(&f, TARGETS_COUNT);

    start(&f);

    fieldClear(&f);

    return 0;
}
