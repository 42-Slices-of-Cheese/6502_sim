#ifndef H__MEM
#define H__MEM

#include "types.h"

typedef struct Memory 
{
    byte data[1024 * 64];
} Memory;

void clear_mem(Memory *mem);

#endif