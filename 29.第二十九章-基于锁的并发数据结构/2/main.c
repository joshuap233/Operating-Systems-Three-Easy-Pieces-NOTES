//
// Created by pjs on 2020/11/1.
//

#include <stdio.h>
#include "counter.h"
#include "../timer.h"

#define MAX_WORKER 8

void *worker(void *c) {
    counter_t *counter = (counter_t *) c;
    for (int i = 0; i < 10000; i++) {
        increment(counter);
    }
    return NULL;
}

int main() {
    double start, end;
    pthread_t ps[MAX_WORKER];
    counter_t c;

    for (int t = 1; t <= MAX_WORKER; t++) {
        init_counter(&c);

        start = Time_GetSeconds();

        for (int i = 0; i < t; i++) {
            Pthread_create(&ps[i], NULL, &worker, &c);
        }
        for (int i = 0; i < t; i++) {
            Pthread_join(ps[i], NULL);
        }
        end = Time_GetSeconds();
        printf("%f\n", end - start);
    }

    return 0;
}