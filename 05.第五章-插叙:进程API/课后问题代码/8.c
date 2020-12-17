//
// Created by pjs on 2020/10/7.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd[2];
  if (pipe(fd) < 0) {
    perror("pipe");
    exit(1);
  }


  int pid = fork();
  if (pid == 0) {
    int ppid = fork();
    if (ppid == 0) {
      char *msg = "Hello!\n";
//      关闭多余管道端
      close(fd[0]);
      write(fd[1], msg, sizeof(char) * strlen(msg));
    } else if (ppid > 0) {
      wait(NULL);
      char asw[10];
      close(fd[1]);
      int res = read(fd[0], asw, sizeof(char) * 10);
      printf("size:%d, %s", res, asw);
    }
  }
  return 0;
}