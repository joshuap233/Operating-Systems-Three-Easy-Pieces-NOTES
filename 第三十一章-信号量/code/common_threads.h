//
// Created by pjs on 2020/11/1.
//

#ifndef OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_PTHREAD_H
#define OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_PTHREAD_H


#include <pthread.h>
#include <assert.h>
#include <stdlib.h>



#define Pthread_mutex_init(mutex, attr) assert(pthread_mutex_init(mutex, attr) == 0)

#define Pthread_mutex_lock(m) assert(pthread_mutex_lock(m) == 0)

#define Pthread_mutex_unlock(m) assert(pthread_mutex_unlock(m) == 0);

#define Pthread_cond_init(cond, attr) assert(pthread_cond_init(cond, attr) == 0)

#define Pthread_cond_wait(cond, mutex) assert(pthread_cond_wait(cond, mutex) == 0)

#define Pthread_cond_signal(cond) assert(pthread_cond_signal(cond) == 0)

#define Pthread_create(thread, attr,start_routine, arg) assert(pthread_create(thread, attr, start_routine, arg) == 0)

#define Pthread_join(thread, value_ptr) assert(pthread_join(thread, value_ptr) == 0)

#endif //OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_PTHREAD_H
