#include "CircleOfLife.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

#define CLOSE 0

#define ERR  -1
#define CHILD 0


void poohInit(Pooh* pooh, double portion, sec_t time) {
	pooh->portion = -portion;
	pooh->time = time;
}

void beesInit(Bee* bee, double portion, sec_t time_limit, uint8_t count) {
	bee->portion = portion;
	bee->time_limit = time_limit;
	bee->count = count;
}

void start(Life* life) {
	pid_t pid[life->bees.count + 1];

	pid[0] = fork();
	if (pid[0] == ERR)
		fprintf(stderr, "Error: Pooh fork error!\n");
	else
    	if (pid[0] == CHILD) {
			char str_port[9], str_time[3];
			snprintf(str_port, sizeof(str_port), "%lf", life->pooh.portion);
			snprintf(str_time, sizeof(str_time), "%hhu", life->pooh.time);
	
			execl("./Object", "Object", str_port, str_time, "0", NULL);
		}

	for (uint8_t i = 1; i != life->bees.count + 1; ++i) {
		pid[i] = fork();

		if (pid[i] == ERR)
			fprintf(stderr, "Error: bee fork error!\n");
		else
			if (pid[i] == CHILD) {
				srand(time(NULL));
				sec_t bee_time = rand() % life->bees.time_limit + 1;

				char str_port[9], str_time[3], str_id[3];
				snprintf(str_port, sizeof(str_port), "%lf", life->bees.portion);
				snprintf(str_time, sizeof(str_time), "%hhu", bee_time);
				snprintf(str_id, sizeof(str_id), "%hhu", i);				
				
				execl("./Object", "Object", str_port, str_time, str_id, NULL);
			}
	}

	while(!isDepletion(life) && !isFullHive(life))
		if (access(FILE_NAME, F_OK) != ERR) {
			FILE* fp = NULL;
			if ((fp = fopen(FILE_NAME, "r")) == NULL)
				fprintf(stderr, "Error: can't open file!\n");

			if (fscanf(fp, "%lf %hhu %hhu", &life->last_visited.portion, &life->last_visited.time, &life->last_visited.id) == 3) {
				addHoney(&life->hive, life->last_visited.portion);

				switch (life->last_visited.id) {
					case 0:  printf("Pooh ate %lf honey!\n", life->pooh.portion); break;
					default: printf("Bee[%hhu] brought %lf honey!\n", life->last_visited.id, life->bees.portion); break;
				}

				printf("Honey = %lf\n", life->hive.honey);
			}

			if (fclose(fp) != 0)
				fprintf(stderr, "Error: file close error!\n");
			if (remove(FILE_NAME) != 0)
				fprintf(stderr, "Error: deleting file error!");
        }

	isDepletion(life) ? printf("\nPooh is dead :(\n") : printf("\nBees win! Pooh was ate!\n");

	for (uint8_t i = 0; i != life->bees.count + 1; ++i) {
		kill(pid[i], SIGUSR1);

		if (pid[i] != waitpid(pid[i], NULL, 0))
			fprintf(stderr, "Error: child isn't done!\n");
	}
}