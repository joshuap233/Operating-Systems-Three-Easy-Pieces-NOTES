//
// Created by pjs on 2020/10/8.
//
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    int n;
    printf("输入运行系统调用次数: ");
    scanf("%d", &n);

    struct timeval tv_begin, tv_end;
    gettimeofday(&tv_begin, NULL);
    for (int i = 0; i < n; i++) {
        read(0, NULL, 0);
    }
    gettimeofday(&tv_end, NULL);
    printf("执行时间为: %f微秒",
           (float )(tv_end.tv_sec * 1000000 + tv_end.tv_usec - tv_begin.tv_sec * 1000000 - tv_begin.tv_usec) / n);
    return 0;
}