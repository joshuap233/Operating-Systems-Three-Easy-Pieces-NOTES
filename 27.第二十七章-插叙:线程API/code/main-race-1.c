//
// Created by pjs on 2020/11/1.
//

#include <stdio.h>

#include "Pthread.h"

int balance = 0;

void *worker(void *lock) {
    Pthread_mutex_lock(lock);
    balance++; // unprotected access
    Pthread_mutex_unlock(lock);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    pthread_mutex_t lock;
    Pthread_mutex_init(&lock, NULL);

    Pthread_create(&p, NULL, worker, &lock);

    Pthread_mutex_lock(&lock);
    balance++; // unprotected access
    Pthread_mutex_unlock(&lock);

    Pthread_join(p, NULL);
    return 0;
}
