//
// Created by pjs on 2020/10/8.
//
#include "sched.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/time.h"
#include "unistd.h"

int main() {
  int fd1[2], fd2[2], fdt[2], pid, n;

  struct timeval tv_bg, tv_end;
  struct sched_param param;

  printf("输入测试次数(次数太少会导致误差极大): ");
  scanf("%d", &n);

  if (pipe(fd1) < 0 || pipe(fd2) < 0 || pipe(fdt) < 0) {
    perror("pipe");
    exit(1);
  };

  if ((pid = fork()) < 0) {
    printf("error");
    exit(1);
  } else if (pid == 0) {
    // SCHED_FIFO指定先来先服务调度
    sched_setscheduler(getpid(), SCHED_FIFO, &param);

    gettimeofday(&tv_bg, NULL);
    for (int i = 0; i < n; i++) {
      read(fd1[0], NULL, 1);
      write(fd2[1], "h", 1);
    }

    write(fdt[1], &tv_bg.tv_usec, sizeof(tv_bg.tv_usec));
    exit(0);

  } else {
    sched_setscheduler(getpid(), SCHED_FIFO, &param);

    for (int i = 0; i < n; i++) {
      write(fd1[1], "h", 1);
      read(fd2[0], NULL, 1);
    }
    gettimeofday(&tv_end, NULL);

    read(fdt[0], &tv_bg.tv_usec, sizeof(tv_bg.tv_usec));

    printf("上下文切换时间为: %ld 微秒",
           (tv_end.tv_usec - tv_bg.tv_usec) / (2 * n));
  }
  return 0;
}