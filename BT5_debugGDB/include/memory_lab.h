#ifndef _MEMORY_LAB_H_
#define _MEMORY_LAB_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
}Loglevel;

extern const char *LoglevelStrings[];

void log_message(Loglevel level, const char* message);

void recursize(int n);
void stack_overflow();

void memory_leak();

void out_of_memory();

#endif