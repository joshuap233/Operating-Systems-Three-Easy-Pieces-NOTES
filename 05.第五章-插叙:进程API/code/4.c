//
// Created by pjs on 2020/10/7.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
  int pid = fork();
  char *cmd = "/bin/ls";
  char *arg[] = {"ls", "-a", NULL};

  if (pid < 0) {
    printf("fork error\n");
    exit(1);
  } else if (pid == 0) {
    //    exec不会返回,所以第一条execl语句后的语句不会被执行
    execl(cmd, "ls", NULL);
    execlp(cmd, "ls", NULL);
    execve(cmd, arg, envp);
    execv(cmd, arg);
    execvp(cmd, arg);
    execle(cmd, "ls", NULL, envp);
  } else {
  }
  return 0;
}