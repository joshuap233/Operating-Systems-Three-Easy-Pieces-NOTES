//
// Created by pjs on 2020/11/1.
//

#ifndef OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_PTHREAD_H
#define OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_PTHREAD_H

#include <pthread.h>
#include <assert.h>

#define Pthread_mutex_

#define Pthread_mutex_init(mutex, mutexattr) assert(pthread_mutex_init(mutex, mutexattr)==0)

#define Pthread_mutex_lock(mutex) assert(pthread_mutex_lock(mutex)==0);

#define Pthread_mutex_unlock(mutex) assert(pthread_mutex_unlock(mutex)==0);


#endif //OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_PTHREAD_H
