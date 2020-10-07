//
// Created by pjs on 2020/10/7.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pid = fork();
  int fd[2];
  if (pipe(fd) < 0) {
    perror("pipe");
    exit(1);
  }
  if (pid == 0) {
    int ppid = fork();
    if (ppid == 0) {
      char *msg = "Hello!\n";
      write(fd[1], msg, sizeof(char) * strlen(msg));
      close(fd[1]);
    } else if (ppid > 0) {
      wait(NULL);
      char asw[10];
      int res = read(fd[0], asw, sizeof(char) * 10);
      printf("size:%d, %s", res, asw);
      close(fd[0]);
    }
  }
  return 0;
}