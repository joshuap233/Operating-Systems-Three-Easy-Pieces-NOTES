#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void test1();

void test2();

int main(int argc, char *argv[]) {
    if (argc == 1) {
        test1();
    } else {
        test2();
    }
    return 0;
}

void test1() {
    int pid = fork();
    int x = 100;
    if (pid < 0) {
        printf("fork error\n");
        exit(1);
    } else if (pid == 0) {
        printf("child, x %d\n", x);
    } else {
        printf("parent, x %d\n", x);
    }
}

void test2() {
    int pid = fork();
    int x = 100;
    if (pid < 0) {
        printf("fork error\n");
        exit(1);
    } else if (pid == 0) {
        printf("child,x %d\n", x);
        x = 0;
        printf("child,x %d\n", x);
    } else {
        printf("parent,x %d\n", x);
        x = 1;
        printf("parent,x %d\n", x);
    }
}