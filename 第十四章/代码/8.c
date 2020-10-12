//
// Created by pjs on 2020/10/11.
//

#include "stdlib.h"
#include "stdio.h"

#define INIT_SIZE 10
#define EXTEND_SIZE 5

typedef struct Vector {
    float *x;
    float *y;
    int length;
    int max_length;
} Vector;

int v_append(Vector *, float, float);

void v_free(Vector *);


int main() {
    Vector v = {
            .length = 0,
            .max_length = INIT_SIZE,
            .x = (float *) malloc(sizeof(float) * INIT_SIZE),
            .y = (float *) malloc(sizeof(float) * INIT_SIZE)
    };
    v_append(&v, 1, 2);
    printf("(x,y): (%f,%f)\n", v.x[0], v.y[0]);
    v_free(&v);
    return 0;
}


int v_append(Vector *v, float x, float y) {
    if ((*v).length + 1 >= (*v).max_length) {
        (*v).max_length += EXTEND_SIZE;
        (*v).x = (float *) realloc((*v).x, sizeof(float) * (*v).max_length);
        (*v).y = (float *) realloc((*v).y, sizeof(float) * (*v).max_length);
    }
    (*v).x[(*v).length] = x;
    (*v).y[(*v).length] = y;
    (*v).length += 1;
    return (*v).length;
}

void v_free(Vector *v) {
    free((*v).x);
    free((*v).y);
}