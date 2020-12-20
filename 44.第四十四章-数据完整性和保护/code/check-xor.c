#include <stdio.h>
#include <assert.h>
#include "common.h"

#define SIZE 1

int main(int argc, char *argv[]) {
    FILE *f;
    double ts, te;
    unsigned char i1 = 0b0, i2 = 0b0;
    char *path;
    if (argc == 1) {
        path = "../check";
    } else {
        path = argv[1];
    }
    assert((f = fopen(path, "rb")) != NULL);
    ts = Time_GetSeconds();
    while (fread(&i2, SIZE, 1, f) == 1) {
        i1 = i2 ^ i1;
    }
    te = Time_GetSeconds();
    fclose(f);
    printf("Checksum: %x\n", i1);
    printf("Time: %f\n", te - ts);
    return 0;
}