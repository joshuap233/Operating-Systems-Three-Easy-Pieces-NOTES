//
// Created by pjs on 2020/12/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "common.h"
#include <string.h>


int make_socket() {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd < 0) {
        err_exit("socket");
    }
    return sock_fd;
}

int make_server_socket(sockaddr_in_t info) {
    int sock_fd = make_socket();
    if (bind(sock_fd, (struct sockaddr *) &info, sizeof(info)) < 0) {
        err_exit("bind");
    }
    return sock_fd;
}


void init_sockaddr_in(sockaddr_in_t *info, short port) {
    info->sin_family = AF_INET;
    info->sin_port = htons(port);
    info->sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&info->sin_zero, sizeof(info->sin_zero));
}