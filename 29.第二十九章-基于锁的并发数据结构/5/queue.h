//
// Created by pjs on 2020/11/1.
//

#ifndef OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_QUEUE_H
#define OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_QUEUE_H
#define NUMCPUS 8
#define SUCCESS 0
#define EMPTY -1

#include "../Pthread.h"

typedef struct node_t {
    int value;
    struct node_t *next;
} node_t;

typedef struct {
    node_t *head;
    node_t *tail;
    pthread_mutex_t head_lock;
    pthread_mutex_t tail_lock;
} queue_t;

void init_queue(queue_t *q);

void enqueue_queue(queue_t *q, int value);

int dequeue_queue(queue_t *q, int *value);

int free_queue(queue_t *q);

#endif //OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_QUEUE_H
