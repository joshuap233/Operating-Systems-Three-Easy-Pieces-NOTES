//
// Created by pjs on 2020/11/8.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include "unistd.h"

// 第一个参数为分配内存空间大小，第二个参数为运行的时间（秒）
int main(int argc, char *argv[]) {
    if (argc != 3) {
        exit(EXIT_FAILURE);
    }
    struct timeval tv_begin, now;

    int memory = atoi(argv[1]) * 1024 * 1024;
    int runtime = atoi(argv[2]);

    int length = memory / 4;
    int *arr = malloc(4 * length);
    assert(arr != NULL);
    printf("pid: %d\n", getpid());
    gettimeofday(&tv_begin, NULL);
    while (1) {
        gettimeofday(&now, NULL);
        if (now.tv_sec - tv_begin.tv_sec >= runtime) {
            break;
        }
        for (int i = 0; i < length; i++) {
            arr[i] = i;
        }
    }
    free(arr);
    return 0;
}
