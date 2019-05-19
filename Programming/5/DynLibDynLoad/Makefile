DEFINES = -D_POSIX_C_SOURCE
CFLAGS  = -std=c99 -fPIC -shared -g $(DEFINES)
LIBS    = -lm -ldl

main: main.o libFunctions.so
	gcc $(CFLAGS) -o main main.o -L. -lFunctions $(LIBS)

main.o: main.c
	gcc $(CFLAGS) -c main.c $(LIBS)

libFunctions.so: Functions.o
	gcc $(CFLAGS) -o libFunctions.so -Wl,--no-undefined Functions.o $(LIBS)

Functions.o: Functions.c Functions.h
	gcc $(CFLAGS) -c Functions.c $(LIBS)

clean:
	rm -rf *.o *.so main
