//
// Created by pjs on 2020/11/24.
//

#ifndef OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H
#define OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H

#include <pthread.h>
#include <assert.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>

#define Pthread_create(thread, attr, start_routine, arg) assert(pthread_create(thread, attr, start_routine, arg) == 0)

#define Pthread_join(thread, value_ptr) assert(pthread_join(thread, value_ptr) == 0)
#define err_exit(message) do{perror(message);exit(EXIT_FAILURE);}while(0)
typedef struct sockaddr_in sockaddr_in_t;

int make_socket();

int make_server_socket(sockaddr_in_t info);

void init_sockaddr_in(sockaddr_in_t *info, short port);

#endif //OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H
