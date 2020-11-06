//
// Created by pjs on 2020/11/1.
//

#include <stdio.h>
#include "linkList.h"
#include "../timer.h"

#define MAX_WORKER 8

typedef struct {
    list_t *list;
} threadArgs;

void *worker(void *tArgs) {
    threadArgs *args = (threadArgs *) tArgs;
    for (int i = 0; i < 10000; i++) {
        list_insert(args->list, i);
        int status = lookup(args->list, i);
    }
    return NULL;
}

int main() {
    double start, end;
    pthread_t ps[MAX_WORKER];
    list_t list;
    threadArgs tArgs;
    for (int t = 1; t <= MAX_WORKER; t++) {
        list_init(&list);
        tArgs.list = &list;

        start = Time_GetSeconds();

        for (int i = 0; i < t; i++) {
            Pthread_create(&ps[i], NULL, &worker, &tArgs);
        }
        for (int i = 0; i < t; i++) {
            Pthread_join(ps[i], NULL);
        }

        end = Time_GetSeconds();
        printf("%f\n", end - start);
    }
    free_list(&list);
    return 0;
}