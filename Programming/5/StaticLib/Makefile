DEFINES = -D_POSIX_C_SOURCE
CFLAGS  = -std=c99 -g $(DEFINES)
LIBS    = -lm

main: main.o libFunctions.a
	gcc $(CFLAGS) -o main main.o -L. -lFunctions $(LIBS)

main.o: main.c
	gcc $(CFLAGS) -c main.c $(LIBS)

libFunctions.a: Functions.o
	ar rc libFunctions.a Functions.o
	ranlib libFunctions.a

Functions.o: Functions.c Functions.h
	gcc $(CFLAGS) -c Functions.c $(LIBS)

clean:
	rm -rf *.o *.a main