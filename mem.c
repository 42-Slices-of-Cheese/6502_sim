#include "mem.h"

void clear_mem(Memory *mem)
{
    for(int i = 0; i < 1024 * 64; i++) {
        mem->data[i] = 0;
    }
}