//
// Created by pjs on 2020/10/7.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pid = fork();
  if (pid < 0) {
    printf("fork error\n");
    exit(1);
  } else if (pid == 0) {
    sleep(1);
    printf("child\n");
  } else {
    int res = waitpid(pid, NULL, 0);
    printf("%d\n", res);
  }
  return 0;
}