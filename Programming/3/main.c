#include <stdio.h>

#include "Vector.h"


int main(int argc, char** argv) {
    /*
    Vector V;
    VectorInit(&V, 0);

    VectorMenu(&V);

    VectorDelete(&V);
    */

    Elem E1 = {"Elem 1", 12.5, "18.03.18", 5};
    Elem E2 = {"Elem 2", 51.5, "19.02.18", 18};
    Elem E3 = {"Elem 3", 33.3, "13.04.18", 63};

    Vector V;
    VectorInit(&V, 6);

    VectorAdd(&V, E1);
    VectorAdd(&V, E2);
    VectorAdd(&V, E3);

    VectorPrint(&V);

    VectorSort(&V);

    puts("");
    VectorPrint(&V);
    VectorDelete(&V);

    return 0;
}
