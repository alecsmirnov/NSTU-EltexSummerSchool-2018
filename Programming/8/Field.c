#include "Field.h"
#include "Vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/msg.h>

#define ERR  -1
#define CHILD 0

#define CH_LEFT  "\u2190"
#define CH_UP    "\u2191"
#define CH_RIGHT "\u2192"
#define CH_DOWN  "\u2193"

#define CH_HLINE "\u2594"
#define CH_VLINE "\u2595"
#define CH_ULINE "\u2582"


static uint8_t scouts_done = 0;

typedef struct Message {
    long type;

    uint8_t scout_id;
    uint8_t target_id;
    Position coords;
    bool found;
} Message, Object;

void fieldInit(Field* field) {
    field->targets = NULL;
    field->targets_count = 0;

    field->scouts = NULL;
    field->scouts_count = 0;

    field->width = 0;
    field->height = 0;
}

void fieldSetSize(Field* field, int8_t width, int8_t height) {
    field->width = width;
    field->height = height;
}

Direction getDirection(Field* field, Position coords) {
    int8_t x = coords.x;
    Direction pos_x = LEFT;
    if (coords.x <= field->width - coords.x) {
        x = field->width - coords.x;
        pos_x = RIGHT;
    }

    int8_t y = coords.y;
    Direction pos_y = UP;
    if (coords.y <= field->height - coords.y) {
        y = field->height - coords.y;
        pos_y = DOWN;
    }

    return x < y ? pos_y : pos_x;
}

void fieldSetScoutsCount(Field* field, uint8_t count, useconds_t time_limit) {
    field->scouts_count = count;
    field->scouts = (Scout*)malloc(sizeof(Scout) * field->scouts_count);

    srand(time(NULL));
    for (uint8_t i = 0; i != field->scouts_count; ++i) {
        Position position = {rand() % field->width, rand() % field->height};
        field->scouts[i].coords = position;
        field->scouts[i].direction = getDirection(field, field->scouts[i].coords);
        field->scouts[i].time = rand() % time_limit + 1;
    }
}

void fieldSetTargetsCount(Field* field, uint8_t count) {
    field->targets_count = count;
    field->targets = (Target*)malloc(sizeof(Target) * field->targets_count);

    srand(time(NULL));
    for (uint8_t i = 0; i != field->targets_count; ++i) {
        Position position = {rand() % field->width, rand() % field->height};
        field->targets[i] = position;
    }
}

void fieldPrint(const Field* field, bool* targets_found, Vector* found_log) {
    char* field_view[field->width][field->height];
    for (int8_t i = 0; i != field->width; ++i)
        for (int8_t j = 0; j != field->height; ++j)
            field_view[i][j] = " ";

    for (uint8_t i = 0; i != field->targets_count; ++i) {
        int8_t x = field->targets[i].x;
        int8_t y = field->targets[i].y;

        field_view[x][y] = targets_found[i] ? "X" : "o";
    }

    for (uint8_t i = 0; i != field->scouts_count; ++i) {
        int8_t x = field->scouts[i].coords.x;
        int8_t y = field->scouts[i].coords.y;

        if (0 <= x && x < field->width && 0 <= y && y < field->height) {
            char* direction;

            switch (field->scouts[i].direction) {
                case LEFT:  direction = CH_LEFT; break;
                case UP:    direction = CH_UP; break;
                case RIGHT: direction = CH_RIGHT; break;
                case DOWN:  direction = CH_DOWN; break;
                default:;
            }

            field_view[x][y] = direction;
        }
    }

    printf(" ");
    for (int8_t i = 0; i != field->width; ++i)
        printf("%hhd ", i);

    printf("\n ");
    for (int8_t i = 0; i != field->width; ++i)
        printf(CH_ULINE""CH_ULINE);
    printf("\n");

    for (int8_t i = 0; i != field->height; ++i) {
        printf(CH_VLINE);
        for (int8_t j = 0; j != field->width; ++j)
            j == field->width - 1 ? printf("%s", field_view[j][i]) :
                                    printf("%s ", field_view[j][i]);

        printf(CH_VLINE"  %hhd\n", i);
    }

    printf(" ");
    for (int8_t i = 0; i != field->width; ++i)
        printf(CH_HLINE""CH_HLINE);
    printf("\n");

    uint8_t count = 0;
    for (uint8_t i = 0; i != field->targets_count; ++i)
        if (targets_found[i])
            ++count;

    count ? printf("Targets found: %hhu of %hhu\n", count, field->targets_count) :
            printf("No targets found!\n");

    vectorPrint(found_log);
}

void fieldClear(Field* field) {
    free(field->targets);
    free(field->scouts);
    fieldInit(field);
}

void objBehavior(Field* field, uint8_t scout_id, key_t msgq_key) {
    int msgq_id = msgget(msgq_key, 0666 | IPC_EXCL);
    if (msgq_id == ERR)
        fprintf(stderr, "Error: msgget() error!\n");

    Message msg = {1, scout_id, 0, field->scouts[scout_id].coords, false};

    int8_t  path_end = 0;
    int8_t* path = &path_end;

    int8_t step = 1;
    switch (field->scouts[scout_id].direction) {
        case LEFT:  path = &msg.coords.x; path_end = -1; step = -1; ++*path; break;
        case UP:    path = &msg.coords.y; path_end = -1; step = -1; ++*path; break;
        case RIGHT: path = &msg.coords.x; path_end = field->width; --*path; break;
        case DOWN:  path = &msg.coords.y; path_end = field->height; --*path; break;
        default:;
    }

    while (*path != path_end) {
        usleep(field->scouts[scout_id].time);
        *path += step;

        msg.found = false;
        for (uint8_t i = 0; i != field->targets_count && !msg.found; ++i)
            if (positionCmp(msg.coords, field->targets[i])) {
                msg.target_id = i;
                msg.found = true;
            }

        ssize_t sended = msgsnd(msgq_id, &msg, sizeof(Message) - sizeof(long), IPC_NOWAIT);
        if (sended == ERR)
            fprintf(stderr, "Error: Scout[%hhu] sending error!\n", scout_id);
    }

    exit(0);
}

void start(Field* field) {
    scouts_done = 0;

    bool targets_found[field->targets_count];
    for (uint8_t i = 0; i != field->targets_count; ++i)
        targets_found[i] = false;

    key_t key = 1;
    int msgq_id = msgget(key, IPC_CREAT | 0666);
    if (msgq_id == ERR)
        fprintf(stderr, "Error: msgget() error!\n");

    pid_t pid[field->scouts_count];
    for (uint8_t i = 0; i != field->scouts_count; ++i) {
        pid[i] = fork();

        if (pid[i] == ERR)
            fprintf(stderr, "Error: scout fork error!\n");
        else
            if (pid[i] == CHILD)
                objBehavior(field, i, key);
    }

    Vector found_log;
    vectorInit(&found_log, 0);

    Message msg = {1, 0, 0, {0, 0}, false};

    fieldPrint(field, targets_found, &found_log);
    while(scouts_done != field->scouts_count) {
        ssize_t received = msgrcv(msgq_id, &msg, sizeof(Message) - sizeof(long), msg.type, IPC_NOWAIT);

        if (received != ERR) {
            if (msg.found) {
                Elem elem = {msg.scout_id, msg.target_id, {msg.coords.x, msg.coords.y}};
                vectorAdd(&found_log, elem);
                targets_found[msg.target_id] = true;
            }

            field->scouts[msg.scout_id].coords = msg.coords;

            system("clear");
            fieldPrint(field, targets_found, &found_log);
        }
        else
            for (uint8_t i = 0; i != field->scouts_count; ++i)
                if (pid[i] == waitpid(pid[i], NULL, WNOHANG))
                    ++scouts_done;
    }

    ssize_t receive = msgctl(msgq_id, IPC_RMID, NULL);
    if (receive == ERR)
        fprintf(stderr, "Error: msgq close errror!\n");

    printf("\nAir exploring is done!\n");
}
