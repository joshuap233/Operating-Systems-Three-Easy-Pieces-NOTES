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
#include <math.h>
#include <limits.h>
#include <fcntl.h>
#include <aio.h>
#include "common.h"
#include "myaio.h"

#define PORT 8080

void *server();

void *client();

char *read_from(int fd);

void send_file(int fd, char *filename);


int main() {

    pthread_t s, c[10];
    Pthread_create(&s, NULL, server, NULL);
//    Pthread_create(&c[0], NULL, client, NULL);
//    Pthread_join(c[0], NULL);

    for (int i = 0; i < 10; ++i) {
        Pthread_create(&c[i], NULL, client, NULL);
    }
    for (int i = 0; i < 10; ++i) {
        Pthread_join(c[i], NULL);
    }
    Pthread_join(s, NULL);
    return 0;
}

_Noreturn void *server() {
    fd_set read_fds;
    int socket_fd, new_socket_fd;
    sockaddr_in_t info, client_info;
    socklen_t addrLen = sizeof(client_info);
    aio_buf_t buf[N_AIO];

    init_aio_buf(buf, N_AIO);
    init_sockaddr_in(&info, PORT);
    FD_ZERO(&read_fds);

    socket_fd = make_server_socket(info);
    FD_SET(socket_fd, &read_fds);

    if (listen(socket_fd, SOMAXCONN) < 0) {
        err_exit("listen");
    }

    while (1) {
        if (select(FD_SETSIZE, &read_fds, NULL, NULL, NULL) < 0) {
            err_exit("select");
        }
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == socket_fd) {
                    //新连接, socket_fd 处于非阻塞模式时, accept不会阻塞
                    new_socket_fd = accept(socket_fd, (struct sockaddr *) &client_info, &addrLen);
                    if (new_socket_fd < 0) {
                        err_exit("accept");
                    }
                    FD_SET(new_socket_fd, &read_fds);
                    printf("connect\n");
                } else {
                    //TODO: my_aio_read 改为 write 并去掉 for 循环与,
//                    char *filename = read_from(i);
//                    send_file(i, filename);
//                    close(i);
//                    FD_CLR(i, &read_fds);
                }
            }

        }

    }
}

void *client() {
    sockaddr_in_t info;
    char buf[MAX_MSG];
    int n_bytes;
    init_sockaddr_in(&info, PORT);

    char message[] = "./static/test.json";
    int size = sizeof(message);
    int socket_fd = make_socket();
    if (connect(socket_fd, (struct sockaddr *) &info, sizeof(info)) < 0) {
        err_exit("client connect\n");
    }

    if (write(socket_fd, message, size) != size) {
        err_exit("write");
    }

    while ((n_bytes = read(socket_fd, buf, MAX_MSG)) != 0) {
        if (n_bytes < 0) {
            err_exit("read");
        } else {
            printf("%s\n", buf);
        }
    }

    close(socket_fd);
    return NULL;
}

char *read_from(int fd) {
    char *buf = malloc(sizeof(MAX_MSG));
    int n_bytes = read(fd, buf, MAX_MSG);
    if (n_bytes < 0) {
        err_exit("read");
    } else {
        return buf;
    }
}

void send_file(int fd, char *filename) {
    char buf[MAX_MSG];
    int n_bytes, file;
    if ((file = openat(AT_FDCWD, filename, O_RDONLY)) < 0) {
        err_exit("open");
    }

    while ((n_bytes = read(file, buf, MAX_MSG)) != 0) {
        if (n_bytes < 0) {
            err_exit("file read");
        }
        if (write(fd, buf, MAX_MSG) < 0) {
            err_exit("write");
        }
    }
}
