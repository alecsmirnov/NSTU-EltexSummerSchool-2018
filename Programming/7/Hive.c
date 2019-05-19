#include "Hive.h"


void hiveInit(Hive* H, double capacity) {
    H->honey = 0;
    H->capacity = capacity;
}

void addHoney(Hive* H, double portion) {
    if (!isFull(H)) {
        if (portion < 0)
            H->honey += portion;
        else
            H->honey + portion <= H->capacity ?
                (H->honey += portion) : (H->honey = H->capacity);
    }
}

double getHoney(Hive* H, double portion) {
    double given = 0;

    if (!isEmpty(H)) {
        if (H->honey <= portion) {
            given = H->honey;
            H->honey = 0;
        }
        else {
            given = portion;
            H->honey -= portion;
        }
    }

	return given;
}
