//
// Created by pjs on 2020/11/1.
//
#include <stdio.h>
#include <stdlib.h>
#include "counter.h"

void init_counter(counter_t *c, int threshold) {
    c->global = 0;
    c->threshold = threshold;
    Pthread_mutex_init(&c->glock, NULL);
    for (int i = 0; i < NUMCPUS; i++) {
        c->local[i] = 0;
        Pthread_mutex_init(&(c->llock[i]), NULL);
    }
}


int get(counter_t *c) {
    Pthread_mutex_lock(&c->glock);
    int ret = c->global;
    Pthread_mutex_unlock(&c->glock);
    return ret;
}

void increment(counter_t *c, int tid, int step) {
    Pthread_mutex_lock(&(c->llock[tid]));
    c->local[tid] += step;
    if (c->local[tid] >= c->threshold) {
        Pthread_mutex_lock(&c->glock);
        c->global += c->local[tid];
        Pthread_mutex_unlock(&c->glock);
        c->local[tid] = 0;
    }
    Pthread_mutex_unlock(&(c->llock[tid]));
}