//
// Created by pjs on 2020/12/5.
//

#ifndef OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H
#define OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H
#define True 1

#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

#define PRINTLN(...) do{printf(__VA_ARGS__);printf("\n");}while (0)

void println_file_type(__mode_t);

void println_user(unsigned);

void println_group(unsigned);

void print_time(struct timespec, char *);

void print_permissions(__mode_t);

char *get_abs_path(char *p, char *f);

#endif //OPERATING_SYSTEMS_THREE_EASY_PIECES_NOTES_COMMON_H
