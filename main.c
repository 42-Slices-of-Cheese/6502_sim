#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"
#include "cpu.h"
#include "mem.h"



int main()
{
    struct CPU cpu;
    struct Memory memory;

    memory.data[0] = 0xA2;
    memory.data[1] = 0xED;

    start(&cpu, &memory, 1);

    // clear_mem(&memory);

    // printf("%X\n", memory.data[2]);

    // printf("%X\n", cpu.X);

    return 0;
}

