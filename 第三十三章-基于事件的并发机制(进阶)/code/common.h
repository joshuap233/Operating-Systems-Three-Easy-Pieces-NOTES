//
// Created by pjs on 2020/11/24.
//

#ifndef OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H
#define OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H

#include <pthread.h>
#include <assert.h>

#define Pthread_create(thread, attr,start_routine, arg) assert(pthread_create(thread, attr, start_routine, arg) == 0)

#define Pthread_join(thread, value_ptr) assert(pthread_join(thread, value_ptr) == 0)

#endif //OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H
