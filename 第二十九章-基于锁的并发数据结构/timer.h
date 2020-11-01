//
// Created by pjs on 2020/11/1.
//

#ifndef OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_TIMER_H
#define OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_TIMER_H

#include <assert.h>
#include <sys/time.h>

double Time_GetSeconds() {
    struct timeval t;
    assert(gettimeofday(&t, NULL) == 0);
    return (double) ((double)t.tv_sec + (double)t.tv_usec / 1e6);
}

#endif //OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_TIMER_H
