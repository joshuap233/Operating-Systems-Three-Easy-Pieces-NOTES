//
// Created by pjs on 2020/11/1.
//

#ifndef OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COUNTER_H
#define OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COUNTER_H

#include "../Pthread.h"

typedef struct {
    int value;
    pthread_mutex_t lock;
} counter_t;

void init_counter(counter_t *c) ;

void increment(counter_t *c);

void decrement(counter_t *c);

int get(counter_t *c);

#endif //OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COUNTER_H
