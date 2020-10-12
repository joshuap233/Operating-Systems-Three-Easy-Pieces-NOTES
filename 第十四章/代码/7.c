//
// Created by pjs on 2020/10/11.
//


#include "stdlib.h"
#include "stdio.h"

int main() {
    int *data = (int *) malloc(sizeof(int) * 100);
    free(&data[10]);
    return 0;
}
