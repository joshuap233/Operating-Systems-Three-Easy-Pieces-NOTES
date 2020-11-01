//
// Created by pjs on 2020/11/1.
//

#include <stdio.h>
#include "counter.h"
#include "../timer.h"

#define MAX_WORKER 8
#define MAX_THRESHOLD 20
#define THRESHOLD {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024}

typedef struct {
    counter_t *c;
    int tid;
    int step;
} threadArgs;

void *worker(void *tArgs) {
    threadArgs *args = (threadArgs *) tArgs;
    for (int i = 0; i < 10000; i++) {
        increment(args->c, args->tid, args->step);
    }
    return NULL;
}

int main() {
    double start, end;
    pthread_t ps[MAX_WORKER];
    counter_t c;
    threadArgs tArgs;
    int threshold[] = THRESHOLD;
    for (int thd= 0; thd < (sizeof(threshold) / sizeof(int)); thd++) {
        for (int t = 1; t <= MAX_WORKER; t++) {
            init_counter(&c, threshold[thd]);
            tArgs.c = &c;
            tArgs.step = 1;

            start = Time_GetSeconds();

            for (int i = 0; i < t; i++) {
                tArgs.tid = i;
                Pthread_create(&ps[i], NULL, &worker, &tArgs);
            }
            for (int i = 0; i < t; i++) {
                Pthread_join(ps[i], NULL);
            }
            //理论上,线程结束后还需要同步一次计数器,但同步时间很短,对实验结果没有影响
            end = Time_GetSeconds();
            printf("%f\n", end - start);
        }
    }

    return 0;
}