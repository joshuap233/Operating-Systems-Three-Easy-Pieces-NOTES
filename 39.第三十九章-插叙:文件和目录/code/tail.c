//
// Created by pjs on 2020/12/4.
//

#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int number;
    char *filename;
} cmd_t;

cmd_t *parse_cmd(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    int n;
    char r;
    int fd;
    cmd_t *cmd = parse_cmd(argc, argv);
    n = cmd->number;
    assert((fd = open(cmd->filename, O_RDONLY)) != -1);
    assert(lseek(fd, 0, SEEK_END) != -1);
    while (n) {
        assert(read(fd, &r, 1) != -1);
        if (r == '\n') {
            n--;
        }
        assert(lseek(fd, -2, SEEK_CUR) != -1);
    }
    assert(lseek(fd, 2, SEEK_CUR) != -1);

    while (read(fd, &r, 1) > 0) {
        printf("%c", r);
    }
    close(fd);
    return 0;
}

cmd_t *parse_cmd(int argc, char *argv[]) {
    cmd_t *cmd = malloc(sizeof(cmd_t));

    if (argc == 3) {
        if (argv[1][0] == '-') {
            argv[1]++;
            cmd->number = atoi(argv[1]);
            cmd->filename = argv[2];
        } else if (argv[2][0] == '-') {
            argv[2]++;
            cmd->number = atoi(argv[2]);
            cmd->filename = argv[1];
        }
    } else {
        printf("请输入正确的参数");
        exit(1);
    }
    return cmd;
}