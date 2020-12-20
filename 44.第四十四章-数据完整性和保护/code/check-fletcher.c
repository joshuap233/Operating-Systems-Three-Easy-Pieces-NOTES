/**
 * fletcher 校验公式为 s1=(s1+di)%255,s2=(s2+s1)%255,
 * 采用 fletcher-16 校验,
 * http://pages.cs.wisc.edu/~remzi/OSTEP/file-integrity.pdf
 */

#include <stdio.h>
#include <assert.h>
#include "common.h"

#define SIZE 1


int main(int argc, char *argv[]) {
    FILE *f;
    unsigned char di, s1 = 0, s2 = 0;
    double ts, te;
    char *path;

    if (argc == 1) {
        path = "../check";
    } else {
        path = argv[1];
    }
    assert((f = fopen(path, "rb")) != NULL);

    ts = Time_GetSeconds();
    while (fread(&di, SIZE, 1, f) == 1) {
        s1 = s1 + di % 255;
        s2 = s2 + s1 % 255;
    }
    te = Time_GetSeconds();
    fclose(f);
    printf("CheckSum: %x,%x\n", s1, s2);
    printf("Time: %f\n", te - ts);
    return 0;
}