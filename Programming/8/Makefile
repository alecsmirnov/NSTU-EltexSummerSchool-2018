DEFINES = -D_POSIX_C_SOURCE -D_BSD_SOURCE
CFLAGS  = -std=c99 -g $(DEFINES)

main: main.o Field.o Vector.o
	gcc $(CFLAGS) -o main main.o Field.o Vector.o

main.o: main.c Field.h
	gcc $(CFLAGS) -c main.c

Field.o: Field.c Field.h Vector.h
	gcc $(CFLAGS) -c Field.c

Vector.o: Vector.c Vector.h
	gcc $(CFLAGS) -c Vector.c

clean:
	rm -rf *.o main