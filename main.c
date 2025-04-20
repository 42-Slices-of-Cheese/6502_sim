#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef unsigned char byte;
typedef unsigned short word;



typedef struct CPU
{
    word PC;
    byte A, X, Y, S;

    byte C : 1;
    byte Z : 1;
    byte I : 1;
    byte D : 1;
    byte B : 1;
    byte Unused : 1;
    byte V : 1;
    byte N : 1;
    
} CPU;

typedef struct Memory 
{
    byte data[1024 * 64];
} Memory;

/*
    function decleration
*/

/*
    Admin functions
*/
void clear_mem(Memory *mem);
void panic();

/*
    handlers
*/
void load_n_set(CPU *cpu, char reg, byte value);
byte fetch(Memory *mem, CPU *cpu);
void ld_flags(CPU *cpu, char reg);


/*
    CPU functions
*/
void start(Memory *mem, CPU *cpu, unsigned int step_count);
void ins_ld_im(CPU *cpu, Memory *mem, char reg);


int main()
{
    struct CPU cpu;
    struct Memory memory;

    memory.data[0] = 0xA2;
    memory.data[1] = 0xED;

    start(&memory, &cpu, 1);

    // clear_mem(&memory);

    // printf("%X\n", memory.data[2]);

    return 0;
}

/*
    function definitions
*/

/*
    Admin functions
*/

void clear_mem(Memory *mem)
{
    for(int i = 0; i < 1024 * 64; i++) {
        mem->data[i] = 0;
    }
}

void panic()
{
    printf("panic!\n");
    exit(1);
}

/*
    CPU functions
*/
void start(Memory *mem, CPU *cpu, unsigned int step_count)
{
    unsigned int steps = step_count;
    byte ins = fetch(mem, cpu);
    byte low_nibble = (ins & 0x0F);
    byte high_nibble = ins >> 4;

    // printf("%X\n", ins);
    // printf("%X\n", low_nibble);
    // printf("%X\n", high_nibble);

    while (steps > 0)   // i just need a way to stop
    {    
        switch (low_nibble)
        {
            case 0x0:
                printf("Debug 0");
                break;

            case 0x1:
                printf("Debug 1");
                break;

            case 0x2:
                if(high_nibble == 0xA)
                    ins_ld_im(cpu, mem, 'X');
                else {
                    printf("Illegal opcode!");
                    panic();
                }
                break;
            
            case 0x4:
                printf("Debug 4");
                break;

            case 0x5:
                printf("Debug 5");
                break;

            case 0x6:
                printf("Debug 6");
                break;
            
            case 0x8:
                printf("Debug 8");
                break;
        
            case 0x9:
                printf("Debug 9");
                break;
        
            case 0xA:
                printf("Debug A");
                break;
            
            case 0xC:
                printf("Debug C");
                break;
        
            case 0xD:
                printf("Debug D");
                break;
        
            case 0xE:
                printf("Debug E");
                break;
            
            default:
                printf("Illegal opcode!\n");
                panic();
                break;
        }
        cpu->PC++;

        steps--;
    }
    cpu->PC--;
}


/*
    Handlers
*/
void load_n_set(CPU *cpu, char reg, byte value)
{
    switch (reg)
    {
        case 'A':
            cpu->A = value;
            break;
        
        case 'X':
            cpu->X = value;
            break;
        
        case 'Y':
            cpu->Y = value;
            break;
        
        default:
            printf("Dafuq?\n");
            panic();
            break;
    }

    ld_flags(cpu, reg);
}

/*
    flag handlers
*/

void ld_flags(CPU *cpu, char reg)
{
    switch (reg)
    {
        case 'A':
            cpu->Z = (cpu->A == 0);
            cpu->N = (cpu->A & 0b10000000) > 0;
            break;
        
        case 'X':
            cpu->Z = (cpu->X == 0);
            cpu->N = (cpu->X & 0b10000000) > 0;
            break;
        
        case 'Y':
            cpu->Z = (cpu->Y == 0);
            cpu->N = (cpu->Y & 0b10000000) > 0;
            break;
        
        default:
            printf("Dafuq?\n");
            panic();
            break;
    }
}

byte fetch(Memory *mem, CPU *cpu)
{
    word addr = cpu->PC;
    return mem->data[addr];
}



/*
    Instructions
*/

void ins_ld_im(CPU *cpu, Memory *mem, char reg)
{
    cpu->PC++;
    byte value = mem->data[cpu->PC];

    load_n_set(cpu, reg, value);
}

void ins_lda_abs(CPU *cpu, Memory *memory)
{
    cpu->PC++;
    word addr;
    addr = memory->data[cpu->PC] << 8;
    cpu->PC++;
    addr += memory->data[cpu->PC];

    cpu->A = memory->data[addr];

    ld_flags(cpu, 'A');
}

void ins_ld_abs(CPU *cpu, Memory *mem, char reg, bool ref)
{

}

void ins_ld_ind(CPU *cpu, Memory *mem, char reg, bool ref)
{
    
}

void ins_ld_zp(CPU *cpu, Memory *mem, char reg, bool ref)
{
    cpu->PC++;
    word addr = cpu->PC;

    if(ref) {
        switch (reg)
        {
        case 'A' || 'Y':
            addr += cpu->X;
            addr = (addr & 0xFF);
            break;
        
        case 'X':
            addr+= cpu->Y;
            addr = (addr & 0xFF);
            break;
        
        default:
            printf("Dafuq?\n");
            panic();
            break;
        }
    }


    byte value = mem->data[addr];

    load_n_set(cpu, reg, value);
}
