#ifndef H__CPU
#define H__CPU

#include "types.h"
#include "mem.h"

typedef struct CPU
{
    word PC;
    byte A, X, Y, S;

    byte C : 1;
    byte Z : 1;
    byte I : 1;
    byte D : 1;
    byte B : 1;
    byte unused : 1;
    byte V : 1;
    byte N : 1;
} CPU;

void start(CPU *cpu, Memory *mem, unsigned int step_count);

#endif