//
// Created by pjs on 2020/10/7.
//

#include <stdio.h>
#include <stdlib.h>f
#include <unistd.h>

int main() {
  int pid = vfork();
  if (pid < 0) {
    printf("fork error\n");
    exit(1);
  } else if (pid == 0) {
    printf("Hello!\n");
    exit(0);
  } else {
    printf("Goodbye\n");
  }
  return 0;
}