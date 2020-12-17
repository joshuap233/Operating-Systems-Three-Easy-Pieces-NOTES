//
// Created by pjs on 2020/11/1.
//
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void init_queue(queue_t *q) {
    Pthread_mutex_init(&q->head_lock, NULL);
    Pthread_mutex_init(&q->tail_lock, NULL);
    node_t *node = (node_t *) malloc(sizeof(node_t));
    node->next = NULL;
    q->head = q->tail = node;
}

void enqueue_queue(queue_t *q, int value) {
    node_t *node = (node_t *) malloc(sizeof(node_t));
    assert(node != NULL);
    node->value = value;
    node->next = NULL;

    Pthread_mutex_lock(&q->tail_lock);
    q->tail->next = node;
    q->tail = node;
    Pthread_mutex_unlock(&q->tail_lock);
}

int dequeue_queue(queue_t *q, int *value) {
    Pthread_mutex_lock(&q->head_lock);
    node_t *head = q->head;
    node_t *new_head = q->head->next;
    if (!new_head) {
        Pthread_mutex_unlock(&q->head_lock);
        return EMPTY;
    }
    *value = new_head->value;
    q->head = new_head;

    Pthread_mutex_unlock(&q->head_lock);
    free(head);
    return SUCCESS;
}

int free_queue(queue_t *q) {
    int ret;
    while (dequeue_queue(q, &ret) == SUCCESS);
}