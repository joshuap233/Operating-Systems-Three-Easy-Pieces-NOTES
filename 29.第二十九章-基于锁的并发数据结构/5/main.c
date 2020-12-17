//
// Created by pjs on 2020/11/1.
//

#include <stdio.h>
#include "queue.h"
#include "../timer.h"

#define MAX_WORKER 8

typedef struct {
    queue_t *q;
} threadArgs;

void *worker(void *tArgs) {
    int ret;
    threadArgs *args = (threadArgs *) tArgs;
    for (int i = 0; i < 1000; i++) {
        if (i % 2 == 0) {
            enqueue_queue(args->q, i);
        } else {
            dequeue_queue(args->q, &ret);
//            printf("%d\n", ret);
        }
    }
    return NULL;
}

int main() {
    double start, end;
    pthread_t ps[MAX_WORKER];
    queue_t q;
    threadArgs tArgs;
    for (int t = 1; t <= MAX_WORKER; t++) {
        init_queue(&q);
        tArgs.q = &q;
        start = Time_GetSeconds();

        for (int i = 0; i < t; i++) {
            Pthread_create(&ps[i], NULL, &worker, &tArgs);
        }
        for (int i = 0; i < t; i++) {
            Pthread_join(ps[i], NULL);
        }

        end = Time_GetSeconds();
        printf("%f\n", end - start);
        free_queue(&q);
    }
    return 0;
}