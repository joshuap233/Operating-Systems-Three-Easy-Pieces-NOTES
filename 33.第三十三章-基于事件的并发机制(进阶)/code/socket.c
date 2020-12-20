//
// Created by pjs on 2020/11/24.
//

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "common.h"

#define PORT 8080

void *server();

void *client();

int main() {
    pthread_t s, c;

    Pthread_create(&s, NULL, server, NULL);
    Pthread_create(&c, NULL, client, NULL);
    Pthread_join(s, NULL);
    Pthread_join(c, NULL);
    return 0;
}

_Noreturn void *server() {
    sockaddr_in_t info, client_info;
    init_sockaddr_in(&info, 8080);
    init_sockaddr_in(&client_info, 8080);
    int socket_fd, new_socket_fd;
    char inputBuffer[256] = {};

    socklen_t addrLen = sizeof(client_info);

    char message[] = "Hi, this is server.\n";
    socket_fd = make_server_socket(info);

    if (socket_fd == -1) {
        perror("socket");
        exit(1);
    }

    //最大连接数为5
    listen(socket_fd, 5);
    new_socket_fd = accept(socket_fd, (struct sockaddr *) &client_info, &addrLen);
    if (new_socket_fd == -1) {
        perror("accept");
        exit(1);
    }

    while (1) {
        send(new_socket_fd, message, sizeof(message), 0);
        recv(new_socket_fd, inputBuffer, sizeof(inputBuffer), 0);
        printf("server recv：%s\n", inputBuffer);
    }
}

_Noreturn void *client() {
    sockaddr_in_t info;
    init_sockaddr_in(&info, 8080);

    char message[] = "Hi there";
    char receiveMessage[100] = {};

    int socket_fd = make_socket();

    int error = connect(socket_fd, (struct sockaddr *) &info, sizeof(info));
    if (error == -1) {
        perror("connect");
        exit(1);
    }

    while (1) {
        send(socket_fd, message, sizeof(message), 0);
        recv(socket_fd, receiveMessage, sizeof(receiveMessage), 0);

        printf("client recv：%s", receiveMessage);
        sleep(1);
    }

//    printf("close Socket\n");
//    close(socket_fd);
}