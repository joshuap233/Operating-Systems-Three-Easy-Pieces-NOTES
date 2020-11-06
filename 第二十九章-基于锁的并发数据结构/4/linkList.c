//
// Created by pjs on 2020/11/1.
//
#include <stdio.h>
#include "linkList.h"

void list_init(list_t *list) {
    list->head = NULL;
    Pthread_mutex_init(&list->lock, NULL);
};

int list_insert(list_t *list, int key) {
    node_t *node = (node_t *) malloc(sizeof(node_t));

    if (node == NULL) {
        perror("malloc");
        return ERROR;
    }
    Pthread_mutex_init(&node->lock, NULL);
    node->key = key;

    Pthread_mutex_lock(&list->lock);
    node->next = list->head;
    list->head = node;
    Pthread_mutex_unlock(&list->lock);

    return SUCCESS;
}

int lookup(list_t *list, int key) {
    int rv = -1;
    //获取head节点后释放,防止刚获取头节点就切出去的情况
    Pthread_mutex_lock(&list->lock);

    node_t *curr = list->head;
    Pthread_mutex_lock(&curr->lock);

    Pthread_mutex_unlock(&list->lock);
    while (curr) {
        if (curr->key == key) {
            rv = 0;
            break;
        }
        Pthread_mutex_lock(&curr->next->lock);
        Pthread_mutex_unlock(&curr->lock);

        curr = curr->next;
    }
    Pthread_mutex_unlock(&curr->lock);

    return rv;
}

void free_list(list_t *list) {
    Pthread_mutex_lock(&list->lock);
    node_t *curr = list->head;
    node_t *next = list->head->next;
    while (curr) {
        free(curr);
        curr = next;
        if (next) {
            next = next->next;
        }
    }
    Pthread_mutex_unlock(&list->lock);
}