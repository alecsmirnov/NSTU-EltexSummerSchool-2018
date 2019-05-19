#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#define FILE_NAME "/tmp/pipe.tmp"

#define ERR -1

static bool work = true;

typedef uint8_t sec_t;


void sigHandler(int sig_num) {
	if (sig_num == SIGUSR1)
		work = false;
}

void objBehavior(double portion, sec_t time, uint8_t id) {
	signal(SIGUSR1, sigHandler);
	sleep(time);

	while(work)
		if (access(FILE_NAME, F_OK) == ERR) {
			FILE* fp = NULL;
			if ((fp = fopen(FILE_NAME, "w")) == NULL)
				fprintf(stderr, "Error: can't open file!\n");

			fprintf(fp, "%lf %hhu %hhu\n", portion, time, id);

			if (fclose(fp) != 0)
				fprintf(stderr, "Error: file close error!\n");

			sleep(time);
		}

	exit(0);
}

int main(int argc, char** argv) {
	if (argc != 4)
		fprintf(stderr, "Invalid count of command line items: %d\n", argc);
	else {
		double portion = atof(argv[1]);
		sec_t time = atoi(argv[2]);
		uint8_t id = atoi(argv[3]);

		objBehavior(portion, time, id);
    }

	return 0;
}
