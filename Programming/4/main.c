#include <stdio.h>
#include <stdlib.h>

#include "Vector.h"


int main(int argc, char** argv) {
    if (argc != 3)
       fprintf(stderr, "Invalid count of command line items!\n");
    else {
        Vector V;
        VectorInit(&V, 0);
        readFile(&V, argv[1]);
        VectorPrint(&V);

        writeStringsLess(&V, atoi(argv[2]), "output_1.txt");
        writeMoreSpaces(&V, atoi(argv[2]), "output_2.txt");

        VectorDelete(&V);
    }

    return 0;
}
