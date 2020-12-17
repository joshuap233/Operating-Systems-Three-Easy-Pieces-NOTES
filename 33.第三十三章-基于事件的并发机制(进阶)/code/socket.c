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

typedef struct {
    struct sockaddr_in server_info;
    struct sockaddr_in client_info;
} info_t;

void *server(void *);

void *client(void *);

int main() {
    pthread_t s, c;
    struct sockaddr_in server_info, client_info = {
            .sin_family = PF_INET,
            .sin_port = htons(8080),
            .sin_addr.s_addr = inet_addr("127.0.0.1"),
    };

    // sin_zero 必须清零
    bzero(&client_info.sin_zero, sizeof(client_info.sin_zero));

    server_info = client_info;

    info_t info = {
            .server_info = server_info,
            .client_info = client_info
    };

    Pthread_create(&s, NULL, server, (void *) &info);
    Pthread_create(&c, NULL, client, (void *) &info);
    Pthread_join(s, NULL);
    Pthread_join(c, NULL);
    return 0;
}

_Noreturn void *server(void *arg) {
    int socket_fd, new_socket_fd;
    char inputBuffer[256] = {};

    info_t *info = (info_t *) arg;
    struct sockaddr_in server_info = info->server_info;
    struct sockaddr_in client_info = info->client_info;

    socklen_t addrLen = sizeof(client_info);

    char message[] = "Hi, this is server.\n";
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);


    if (socket_fd == -1) {
        perror("socket");
        exit(1);
    }

    assert(bind(socket_fd, (struct sockaddr *) &server_info, sizeof(server_info)) == 0);
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

_Noreturn void *client(void *arg) {
    info_t *info = (info_t *) arg;
    char message[] = "Hi there";
    char receiveMessage[100] = {};
    struct sockaddr_in client_info = info->client_info;

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("socket");
        exit(1);
    }

    int error = connect(socket_fd, (struct sockaddr *) &client_info, sizeof(client_info));
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