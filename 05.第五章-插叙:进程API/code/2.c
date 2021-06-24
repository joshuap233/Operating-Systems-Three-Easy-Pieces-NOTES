//
// Created by pjs on 2020/10/7.
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int fd = open("./check.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    int pid = fork();
    if (pid < 0) {
        printf("fork error\n");
        exit(1);
    } else if (pid == 0) {
        char *buf = "child\n";
        int error = write(fd, buf, sizeof(char) * strlen(buf));
        printf("child error: %d\n", error == -1 ? 1 : 0);

    } else {
        char *buf = "parent\n";
        int error = write(fd, buf, sizeof(char) * strlen(buf));
        printf("child error: %d\n", error == -1 ? 1 : 0);

        int wc = wait(NULL);
        close(fd);
    }
    return 0;
}