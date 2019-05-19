CFLAGS  = -std=c99 -g

main: strArray.o main.o
	gcc $(CFLAGS) -o main strArray.o main.o

strArray.o: strArray.c strArray.h
	gcc $(CFLAGS) -c strArray.c

main.o: main.c strArray.h
	gcc $(CFLAGS) -c main.c
	
clean:
	rm -rf *.o main
