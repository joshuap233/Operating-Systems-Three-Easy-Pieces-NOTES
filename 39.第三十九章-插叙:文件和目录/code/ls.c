//
// Created by pjs on 2020/12/4.
//
#include <stdio.h>
#include <dirent.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include "common.h"

typedef struct {
    char *path;
    int detail;
} cmd_t;

cmd_t *parse_cmd(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    cmd_t *c = parse_cmd(argc, argv);
    DIR *dir = opendir(c->path);
    struct stat st;
    assert(dir != NULL);

    struct dirent *d;
    while ((d = readdir(dir)) != NULL) {
        if (strcmp(d->d_name, ".") && strcmp(d->d_name, "..")) {
            if (c->detail) {
                char *path = get_abs_path(c->path, d->d_name);
                assert(stat(path, &st) == 0);
                print_permissions(st.st_mode);
                printf("  ");
                print_time(st.st_atim, "%m/%d %H:%M");
                printf("  ");
                printf(
                        "%s  %s  %8ld  %s\n",
                        getpwuid(st.st_uid)->pw_name,
                        getgrgid(st.st_gid)->gr_name,
                        st.st_size,
                        d->d_name
                );
            } else {
                printf("%s ", d->d_name);
            }
        }
    }
    if (c->detail) {
        printf("\n");
    }
    closedir(dir);
    return 0;
}

cmd_t *parse_cmd(int argc, char *argv[]) {
    cmd_t *c = malloc(sizeof(cmd_t));
    c->detail = 0;
    c->path = ".";

    if (argc == 2) {
        if (strcmp(argv[1], "-l"))
            c->path = argv[1];
        else
            c->detail = 1;
    } else if (argc == 3) {
        if (!strcmp(argv[1], "-l") && !strcmp(argv[2], "-l")) {
            printf("请输入正确的参数\n");
            exit(1);
        }
        c->path = strcmp(argv[1], "-l") ? argv[1] : argv[2];
        c->detail = 1;
    } else {
        if (argc != 1) {
            printf("请输入正确的参数\n");
            exit(1);
        }
    }
    return c;
}

