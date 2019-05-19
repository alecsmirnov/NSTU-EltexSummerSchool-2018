#include <stdio.h>
#include <stdlib.h>

#include "Functions.h"


int main(int argc, char** argv){
	if (argc != 2)
       fprintf(stderr, "Invalid count of command line items!\n");
    else {
		printf("Third: %d\n", raiseToThird(atoi(argv[1])));
		printf("Fourth: %d\n", raiseToFourth(atoi(argv[1])));
	}

    return 0;
}
