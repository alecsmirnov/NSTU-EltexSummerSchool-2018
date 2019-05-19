DEFINES = -D_POSIX_C_SOURCE
CFLAGS  = -std=c99 -g $(DEFINES)

main: main.o CircleOfLife.o Hive.o
	gcc $(CFLAGS) -o main main.o CircleOfLife.o Hive.o

main.o: main.c
	gcc $(CFLAGS) -c main.c

CircleOfLife.o: CircleOfLife.c CircleOfLife.h Hive.h
	gcc $(CFLAGS) -c CircleOfLife.c

Hive.o: Hive.c Hive.h
	gcc $(CFLAGS) -c Hive.c

clean:
	rm -rf *.o main





