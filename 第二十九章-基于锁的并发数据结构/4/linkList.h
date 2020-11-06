//
// Created by pjs on 2020/11/1.
//
#ifndef OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_LINKLIST_H
#define OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_LINKLIST_H

#include "../Pthread.h"

#define SUCCESS 0
#define ERROR -1

typedef struct node_t {
    int key;
    struct node_t *next;
    pthread_mutex_t lock;
} node_t;

typedef struct {
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void list_init(list_t *list);

int list_insert(list_t *list, int key);

int lookup(list_t *list, int key);

void free_list(list_t *list);

#endif //OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_LINKLIST_H
