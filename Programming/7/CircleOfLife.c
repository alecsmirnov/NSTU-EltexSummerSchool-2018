#include "CircleOfLife.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#define CLOSE 0

#define ERR  -1
#define CHILD 0

#define RD 0
#define WR 1
#define RD_WR 2

static bool work = true;


void poohInit(Pooh* pooh, double portion, sec_t time) {
    pooh->portion = -portion;
    pooh->time = time;
}

void beesInit(Bee* bee, double portion, sec_t time_limit, uint8_t count) {
    bee->portion = portion;
    bee->time_limit = time_limit;
    bee->count = count;
}

void sigHandler(int sig_num) {
    if (sig_num == SIGUSR1)
        work = false;
}

void objBehavior(double portion, sec_t time, uint8_t id, int* fd) {
    Object obj = {portion, time, id};

    signal(SIGUSR1, sigHandler);

    do {
        sleep(time);
        close(fd[RD]);
        write(fd[WR], &obj, sizeof(Object));
    } while(work);

    exit(0);
}

void start(Life* life) {
    int fds[life->bees.count + 1][RD_WR];
    pid_t pid[life->bees.count + 1];

    pipe(fds[0]);
    pid[0] = fork();
    if (pid[0] == ERR)
        fprintf(stderr, "Error: Pooh fork error!\n");
    else
        if (pid[0] == CHILD)
            objBehavior(life->pooh.portion, life->pooh.time, 0, fds[0]);

    for (uint8_t i = 1; i != life->bees.count + 1; ++i) {
        pipe(fds[i]);
        pid[i] = fork();

        if (pid[i] == ERR)
            fprintf(stderr, "Error: bee fork error!\n");
        else
            if (pid[i] == CHILD) {
                srand(time(NULL));
                sec_t bee_time = rand() % life->bees.time_limit + 1;

                objBehavior(life->bees.portion, bee_time, i, fds[i]);
            }
    }

    for (uint8_t i = 0; i != life->bees.count + 1; ++i)
        fcntl(fds[i][RD], F_SETFL, fcntl(fds[i][RD], F_GETFL) | O_NONBLOCK);

    while(!isDepletion(life) && !isFullHive(life))
        for (uint8_t i = 0; i != life->bees.count + 1; ++i) {
            close(fds[i][WR]);
            ssize_t received = read(fds[i][RD], &life->last_visited, sizeof(Object));

            if (received > 0) {
                addHoney(&life->hive, life->last_visited.portion);

                switch (i) {
                    case 0:  printf("Pooh ate %lf honey!\n", life->pooh.portion); break;
                    default: printf("Bee[%hhu] brought %lf honey!\n", life->last_visited.id, life->bees.portion); break;
                }

                printf("Honey = %lf\n", life->hive.honey);
            }
        }

    isDepletion(life) ? printf("\nPooh is dead :(\n") : printf("\nBees win! Pooh was ate!\n");

    for (uint8_t i = 0; i != life->bees.count + 1; ++i) {
        kill(pid[i], SIGUSR1);

        if (pid[i] != waitpid(pid[i], NULL, 0))
            fprintf(stderr, "Error: child isn't done!\n");
    }
}


