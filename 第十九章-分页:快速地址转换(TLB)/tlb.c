//
// Created by pjs on 2020/10/18.
//
#define _GNU_SOURCE //sched_setaffinity
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>


#define PAGESIZE 4096

int main(int argc, char *argv[]) {
    int nLoop = 10, nPages = 10;
    int opt;

    if (argc == 5) {
        while ((opt = getopt(argc, argv, "l:p:")) != -1) {
            switch (opt) {
                case 'l':
                    nLoop = atoi(optarg);
                    break;
                case 'p':
                    nPages = atoi(optarg);
                    break;
            }
        }
    }
    int jump = PAGESIZE / sizeof(int);
    int *a = (int *) malloc(nPages * jump * sizeof(int));

    cpu_set_t set;
    // 将cpu 0 添加到集合
    CPU_SET(0, &set);
    //绑定cpu核心
    if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
        perror("sched_setaffinity");
        exit(EXIT_FAILURE);
    }

    uint64_t start, end;
    unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;
    asm volatile ("CPUID\n\t"
                  "RDTSC\n\t"
                  "mov %%edx, %0\n\t"
                  "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
    "%rax", "%rbx", "%rcx", "%rdx");

    for (int j = 0; j < nLoop; j++) {
        for (int i = 0; i < nPages * jump; i += jump) {
            a[i] += 1;
        }
    }
    asm volatile("RDTSCP\n\t"
                 "mov %%edx, %0\n\t"
                 "mov %%eax, %1\n\t"
                 "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
    "%rax", "%rbx", "%rcx", "%rdx");
    start = (((uint64_t) cycles_high << 32) | cycles_low);
    end = (((uint64_t) cycles_high1 << 32) | cycles_low1);
    printf("time: %f clock cycles, page: %d\n", (float) (end - start) / (nLoop * nPages), nPages);
    return 0;
}