//
// Created by pjs on 2020/12/4.
//

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "common.h"

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("缺少必要的参数：文件名或文件路径");
        exit(1);
    }
    struct stat buf;
    assert(stat(argv[1], &buf) == 0);
    PRINTLN("文件名: %s", argv[1]);
    PRINTLN("文件大小: %ld", buf.st_size);
    PRINTLN("块: %ld", buf.st_blocks);
    PRINTLN("IO 块: %ld", buf.st_blksize);
    println_file_type(buf.st_mode);
    print_permissions(buf.st_mode);
    printf("\n");
    PRINTLN("Inode: %lu", buf.st_ino);
    PRINTLN("设备号: %lu", buf.st_dev);
    PRINTLN("硬链接: %lu", buf.st_nlink);
    println_user(buf.st_gid);
    println_group(buf.st_gid);
    printf("最近访问时间:");
    print_time(buf.st_atim, NULL);
    printf("\n");
    printf("最近修改时间:");
    print_time(buf.st_mtim, NULL);
    printf("\n");
    printf("最近状态修改时间:");
    print_time(buf.st_ctim, NULL);
    printf("\n");
    return 0;
}
