//
// Created by pjs on 2020/11/1.
//
#include <stdio.h>
#include <stdlib.h>
#include "counter.h"

void init_counter(counter_t *c) {
    c->value = 0;
    Pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
    Pthread_mutex_lock(&c->lock);
    c->value++;
    Pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c) {
    Pthread_mutex_lock(&c->lock);
    c->value--;
    Pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
    Pthread_mutex_lock(&c -> lock);
    int ret = c->value;
    Pthread_mutex_unlock(&c -> lock);
    return ret;
}

