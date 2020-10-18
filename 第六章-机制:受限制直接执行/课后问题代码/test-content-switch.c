//
// Created by pjs on 2020/10/8.
//

#define _GNU_SOURCE //sched_setaffinity

#include "sched.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/time.h"
#include "unistd.h"


int main() {
    int fd1[2], fd2[2], fdt[2], pid, n;

    struct timeval tv_bg, tv_end;
    const struct sched_param param = {sched_get_priority_min(SCHED_FIFO)};
    cpu_set_t set;
    // 将cpu 0 添加到集合
    CPU_SET(0, &set);

    printf("输入测试次数(次数太少会导致误差极大): ");
    scanf("%d", &n);

    if (pipe(fd1) < 0 || pipe(fd2) < 0 || pipe(fdt) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    };

    if ((pid = fork()) < 0) {
        printf("error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 需要root 权限
        // SCHED_FIFO指定先来先服务调度,
        if (sched_setscheduler(getpid(), SCHED_FIFO, &param) == -1) {
            printf("程序运行需要root权限(sched_setscheduler系统调用)\n");
            perror("sched_setscheduler");
            exit(EXIT_FAILURE);
        }

        // 线程绑定核心
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            perror("sched_setaffinity");
            exit(EXIT_FAILURE);
        }


        gettimeofday(&tv_bg, NULL);
        for (int i = 0; i < n; i++) {
            read(fd1[0], NULL, 1);
            write(fd2[1], "h", 1);
        }

        write(fdt[1], &tv_bg, sizeof(tv_bg));
        exit(EXIT_SUCCESS);

    } else {
        if (sched_setscheduler(getpid(), SCHED_FIFO, &param) == -1) {
            perror("sched_setscheduler");
            exit(EXIT_FAILURE);
        }

        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            perror("sched_setaffinity");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < n; i++) {
            write(fd1[1], "h", 1);
            read(fd2[0], NULL, 1);
        }
        gettimeofday(&tv_end, NULL);

        read(fdt[0], &tv_bg, sizeof(tv_bg));

        printf("上下文切换时间为: %f 微秒",
               (float) (tv_end.tv_sec * 1000000 + tv_end.tv_usec - tv_bg.tv_sec * 1000000 - tv_bg.tv_usec) / 2 / n);
    }
    return 0;
}