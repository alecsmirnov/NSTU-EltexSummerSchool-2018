#include "CircleOfLife.h"

#define BEES_COUNT 3
#define HIVE_CAPACITY 10

#define POOH_PORTION 3.3
#define POOH_TIME 2

#define BEES_PORTION 1.9
#define BEES_TIME_LIMIT 5


int main(int argc, char** argv) {
    Life L;

    hiveInit(&L.hive, HIVE_CAPACITY);
    poohInit(&L.pooh, POOH_PORTION, POOH_TIME);
    beesInit(&L.bees, BEES_PORTION, BEES_TIME_LIMIT, BEES_COUNT);

    start(&L);

    return 0;
}
