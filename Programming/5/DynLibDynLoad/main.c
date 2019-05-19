#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


int main(int argc, char** argv){
	if (argc != 2)
       fprintf(stderr, "Invalid count of command line items!\n");
    else {
		void* lib = dlopen("/home/alex/Summer school/Programming/Task_5/DynLibDynLoad/libFunctions.so", RTLD_LAZY);
		
		if (!lib)
			fprintf(stderr, "dlopen() error: %s\n", dlerror());
		else {
			int (*rToT)(int val) = dlsym(lib, "raiseToThird");
			int (*rToF)(int val) = dlsym(lib, "raiseToFourth");

			printf("Third: %d\n", (*rToT)(atoi(argv[1])));
			printf("Fourth: %d\n", (*rToF)(atoi(argv[1])));
		}
		
		dlclose(lib);
	}

    return 0;
}
