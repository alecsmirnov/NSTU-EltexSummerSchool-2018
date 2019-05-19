CFLAGS  = -std=c99 -g

main: main.o Vector.o
	gcc $(CFLAGS) -o main main.o Vector.o

main.o: main.c Vector.h
	gcc $(CFLAGS) -c main.c

Vector.o: Vector.c Vector.h
	gcc $(CFLAGS) -c Vector.c

clean:
	rm -rf *.o main