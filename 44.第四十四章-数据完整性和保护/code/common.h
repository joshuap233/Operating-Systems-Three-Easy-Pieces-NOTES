//
// Created by pjs on 2020/12/19.
//

#ifndef OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H
#define OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H

#include <sys/time.h>


double Time_GetSeconds() {
    struct timeval t;
    assert(gettimeofday(&t, NULL) == 0);
    return (double) ((double) t.tv_sec + (double) t.tv_usec / 1e6);
}

#endif //OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H
