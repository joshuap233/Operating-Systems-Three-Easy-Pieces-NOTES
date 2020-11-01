//
// Created by pjs on 2020/11/1.
//

#ifndef OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COUNTER_H
#define OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COUNTER_H
#define NUMCPUS 8

#include "../Pthread.h"

typedef struct {
    int global; //全局计数器
    pthread_mutex_t glock;
    int local[NUMCPUS]; //局部计数器
    pthread_mutex_t llock[NUMCPUS]; //局部锁
    int threshold; //阈值,超过该值时,将局部计数器的值添加到全局计数器中
} counter_t;

void init_counter(counter_t *c, int threshold);

void increment(counter_t *c, int tid, int step);

int get(counter_t *c);

#endif //OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COUNTER_H
