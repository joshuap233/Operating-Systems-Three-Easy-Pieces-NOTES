//
// Created by pjs on 2020/11/24.
//

#ifndef OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H
#define OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H

#include <pthread.h>

#define Pthread_create(thread, attr, start_routine, arg) asssert(pthread_create(thread, attr, start_routine, arg) ==0)

#endif //OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H
