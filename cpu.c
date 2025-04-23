#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "mem.h"



void panic(char msg[])
{
    printf("%s\n", msg);
    printf("panic!\n");
    exit(1);
}


void reg_flags(CPU *cpu, char reg)
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
            panic("Dafuq?");
            break;
    }
}

void mem_flags(CPU *cpu, Memory *mem, word addr)
{
    cpu->Z = (mem->data[addr] == 0);
    cpu->N = (mem->data[addr] & 0b10000000) > 0;
}

void clr_flg_reg(CPU *cpu)
{
    cpu->C = 0;
    cpu->Z = 0;
    cpu->I = 0;
    cpu->D = 0;
    cpu->B = 0;
    cpu->unused = 0;
    cpu->V = 0;
    cpu->N = 0;
}


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
            panic("Dafuq?");
            break;
    }

    reg_flags(cpu, reg);
}

void store_n_set(CPU *cpu, Memory *mem, char reg, word addr)
{
    switch (reg)
    {
    case 'A':
        mem->data[addr] = cpu->A;
        break;

    case 'X':
        mem->data[addr] = cpu->X;
        break;

    case 'Y':
        mem->data[addr] = cpu->Y;
        break;
    
    default:
        panic("Dafuq?");
        break;
    }
    
    // mem_flags(cpu, mem, addr);
}


void set_clr_flgs(CPU *cpu, char flag, bool val)
{
    switch (flag)
    {
    case 'C':
        if(val)
            cpu->C = 1;
        else
            cpu->C = 0;
        break;
    
    case 'Z':
        printf("Warning: Not an instruction");
        if(val)
            cpu->Z = 1;
        else
            cpu->Z = 0;
        break;

    case 'I':
        if(val)
            cpu->I = 1;
        else
            cpu->I = 0;
        break;
    
    case 'D':
        if(val)
            cpu->D = 1;
        else
            cpu->D = 0;
        break;
    
    case 'B':
        printf("Warning: Not an instruction");
        if(val)
            cpu->B = 1;
        else
            cpu->B = 0;
        break;

    case 'V':
        
        if(val)
        {
            printf("Warning: Not an instruction");
            cpu->V = 1;
        }
        else
            cpu->V = 0;
        break;
    
    case 'N':
        printf("Warning: Not an instruction");
        if(val)
            cpu->N = 1;
        else
            cpu->N = 0;
        break;

    default:
        panic("Dafuq?");
        break;
    }
}

void lda_abs(CPU *cpu, Memory *memory)
{
    word addr = memory->data[++cpu->PC];
    addr += memory->data[++cpu->PC] << 8;
    byte value = memory->data[addr];
    
    load_n_set(cpu, 'A', value);
}

void lda_ind(CPU *cpu, Memory *mem, bool ref)
{
    word vector;
    word addr;
    if(!ref){
        vector = (mem->data[++cpu->PC] + cpu->X) & 0xFF;
        addr = mem->data[vector];
        addr += (((word) mem->data[++vector]) << 8);
    }else{
        vector = mem->data[++cpu->PC];
        addr = mem->data[vector];
        addr += (((word) mem->data[++vector]) << 8);
        addr += cpu->Y;
    }

    byte value = mem->data[addr];
    load_n_set(cpu, 'A', value);
}


void ld_im(CPU *cpu, Memory *mem, char reg)
{
    byte value = mem->data[++cpu->PC];
    load_n_set(cpu, reg, value);
}

void ld_abs(CPU *cpu, Memory *mem, char reg, bool ref)
{
    word addr = mem->data[++cpu->PC];
    addr += (((word) mem->data[++cpu->PC]) << 8);

    switch (reg)
    {
    case  'A':
        if(ref)
            addr += cpu->X;
        else
            addr += cpu->Y;
        break;
    
    case 'X':
        if(ref)
            addr += cpu->Y;
        break;
    
    case 'Y':
        if(ref)
            addr += cpu->X;
        break;
    
    default:
        panic("Dafuq?");
        break;
    }

    byte value = mem->data[addr];
    load_n_set(cpu, reg, value);
}

void ld_zp(CPU *cpu, Memory *mem, char reg, bool ref)
{
    word addr = mem->data[++cpu->PC];

    if(ref) {
        if(reg == 'A' || reg == 'Y')
            addr += cpu->X;
        else if (reg == 'X')
            addr+= cpu->Y;
        else
            panic("Dafuq?");
    }

    addr = addr & 0xFF;

    byte value = mem->data[addr];
    load_n_set(cpu, reg, value);
}


void inc_dec_reg(CPU *cpu, Memory *mem, char reg, bool dir)
{
    switch (reg)
    {
    case 'X':
        if(dir)
            cpu->X++;
        else
            cpu->X--;
        break;

    case 'Y':
        if(dir)
            cpu->Y++;
        else
            cpu->Y--;
        break;
    
    default:
        panic("Dafuq?");
        break;
    }

    reg_flags(cpu, reg);
}

void inc_dec_mem(CPU *cpu, Memory *mem, char opt, bool dir)
{
    word addr = mem->data[++cpu->PC];

    switch (opt)
    {
    case 'Z':
        if(dir)
            mem->data[addr]++;
        else
            mem->data[addr]--;
        break;
    
    case 'A':
        addr += (((word) mem->data[++cpu->PC]) << 8);
        
        if(dir)
            mem->data[addr]++;
        else
            mem->data[addr]--;
        break;
    
    case 'X':
        addr += cpu->X;
        addr = addr & 0xFF;

        if(dir)
            mem->data[addr]++;
        else
            mem->data[addr]--;
        break;
    
    case 'B':
        addr += (((word) mem->data[++cpu->PC]) << 8) + cpu->X;

        if(dir)
            mem->data[addr]++;
        else
            mem->data[addr]--;
        break;
    
    default:
        panic("Dafuq?");
        break;
    }

    mem_flags(cpu, mem, addr);
}

void sta_abs(CPU *cpu, Memory *mem, bool ref)
{
    word addr = mem->data[++cpu->PC];
    addr += (((word) mem->data[++cpu->PC]) << 8);

    if(!ref) 
        addr += cpu->X;
    else
        addr += cpu->Y;
    
    store_n_set(cpu, mem, 'A', addr);
}

void sta_ind(CPU *cpu, Memory *mem, bool ref)
{
    word vector;
    word addr;
    if(!ref)
    {
        vector = (mem->data[++cpu->PC] + cpu->X) & 0xFF;
        addr = mem->data[vector];
        addr += (((word) mem->data[++vector]) << 8);
    }
    else
    {
        vector = mem->data[++cpu->PC];
        addr = mem->data[vector];
        addr += (((word) mem->data[++vector]) << 8);
        addr += cpu->Y;
    }

    store_n_set(cpu, mem, 'A', addr);
}

void store_abs(CPU *cpu, Memory *mem, char reg)
{
    word addr = mem->data[++cpu->PC];
    addr += (((word) mem->data[++cpu->PC]) << 8);

    store_n_set(cpu, mem, reg, addr);
}

void store_zp(CPU *cpu, Memory *mem, char reg, bool ref)
{
    word addr = mem->data[++cpu->PC];

    switch (reg)
    {
    case 'A':
        if(ref)
            addr += cpu->X;
        break;

    case 'X':
        if(ref)
            addr += cpu->Y;
        break;

    case 'Y':
        if(ref)
            addr += cpu->X;
        break;
    
    default:
        panic("Dafuq?");
        break;
    }

    addr = addr & 0xFF;
    store_n_set(cpu, mem, reg, addr);
}


void trasfer(CPU *cpu, char src, char dst)
{
    if(src == dst)
        panic("What are you doing?");

    switch (src)
    {
    case 'A':
        if(dst == 'X')
            cpu->X = cpu->A;
        else if (dst == 'Y')
            cpu->Y = cpu->A;
        else
            panic("NO");
        break;

    case 'X':
        if(dst == 'A')
            cpu->A = cpu->X;
        else if(dst == 'S')
            cpu->S = cpu->X;
        else
            panic("NO");
        break;

    case 'Y':
        if(dst == 'A')
            cpu->A = cpu->Y;
        else
            panic("NO");
        break;

    case 'S':
        if(dst == 'X')
            cpu->X = cpu->S;
        else
            panic("NO");
        break;
    
    default:
        panic("Dafuq?");
        break;
    }

    reg_flags(cpu, dst);
}


void bit_op(CPU *cpu, byte data, char mode)
{
    switch (mode)
    {
    case 'A':
        cpu->A &= data;
        break;

    case 'E':
        cpu->A ^= data;
        break;

    case 'O':
        cpu->A |= data;
    
    default:
        panic("Dafuq?\n");
        break;
    }
    
    reg_flags(cpu, 'A');
}

void bit_op_im_abs(CPU *cpu, Memory *mem, bool opt, char mode)
{
    word next = mem->data[++cpu->PC];
    byte data = next;
    if(opt)
        data = mem->data[next + (((word) mem->data[++cpu->PC]) << 8)];

    bit_op(cpu, data, mode);
}

void bit_op_zp(CPU *cpu, Memory *mem, bool opt, char mode)
{
    word addr = mem->data[++cpu->PC];
    if(opt)
    {
        addr += cpu->X;
        addr = addr & 0xFF;
    }
    
    byte data = mem->data[addr];

    bit_op(cpu, data, mode);
}

void bit_op_abs(CPU *cpu, Memory *mem, bool opt, char mode)
{
    word addr = mem->data[++cpu->PC];
    addr += (((word) mem->data[++cpu->PC]) << 8);

    if(opt)
        addr += cpu->X;
    else
        addr += cpu->Y;
    
    byte data = mem->data[addr];
    bit_op(cpu, data, mode);
}

void bit_op_ind(CPU *cpu, Memory *mem, bool opt, char mode)
{
    word vector;
    word addr;
    if(!opt)
    {
        vector = (mem->data[++cpu->PC] + cpu->X) & 0xFF;
        addr = mem->data[vector];
        addr += (((word) mem->data[++vector]) << 8);
    }
    else
    {
        vector = mem->data[++cpu->PC];
        addr = mem->data[vector];
        addr += (((word) mem->data[++vector]) << 8);
        addr += cpu->Y;
    }

    byte data = mem->data[addr];

    bit_op(cpu, data, mode);
}

void bit_test(CPU *cpu, Memory *mem, bool opt)
{

}


byte packFlags(CPU *cpu)
{
    return (cpu->N << 7) |
           (cpu->V << 6) |
           (cpu->unused << 5) |
           (cpu->B << 4) |
           (cpu->D << 3) |
           (cpu->I << 2) |
           (cpu->Z << 1) |
           (cpu->C);
}

void unpackFlags(CPU *cpu, byte value)
{
    cpu->C      = (value >> 0) & 1;
    cpu->Z      = (value >> 1) & 1;
    cpu->I      = (value >> 2) & 1;
    cpu->D      = (value >> 3) & 1;
    cpu->B      = (value >> 4) & 1;
    cpu->unused = (value >> 5) & 1;
    cpu->V      = (value >> 6) & 1;
    cpu->N      = (value >> 7) & 1;
}

void stack(CPU *cpu, Memory *mem, bool opt, bool reg)
{
    word addr = 0x0100;

    if(!opt)
    {
        addr += cpu->S--;
        byte data;

        if(!reg)
            data = cpu->A;
        else
            data = packFlags(cpu);

        mem->data[addr] = data;
    }
    else
    {
        addr += ++cpu->S;
        byte data = mem->data[addr];

        if(!reg)
            load_n_set(cpu, 'A', data);
        else
            unpackFlags(cpu, data);
    }
}

void jmp(CPU *cpu, Memory *mem, bool opt)
{
    word vector = mem->data[++cpu->PC];
    vector += (((word) mem->data[++cpu->PC]) << 8);
    word addr;
    if(!opt)
        addr = vector;
    else
    {
        addr = mem->data[vector];
        addr += (((word) mem->data[++vector]) << 8);
    }
    
    cpu->PC = mem->data[addr];
}

void jsr(CPU *cpu, Memory *mem)
{

}

void rts(CPU *cpu, Memory *mem)
{

}



void start(CPU *cpu, Memory *mem, unsigned int step_count)
{
    unsigned int steps = step_count;

    // printf("%X\n", ins);
    // printf("%X\n", low_nibble);
    // printf("%X\n", high_nibble);

    byte ins = mem->data[cpu->PC];

    while (steps > 0)   // i just need a way to stop
    {   
        
        byte low_nibble = (ins & 0x0F);
        byte high_nibble = (ins >> 4);

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
                    ld_im(cpu, mem, 'X');
                else
                    panic("Illegal opcode!");
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
                panic("Illegal opcode!");
                break;
        }

        cpu->PC++;
        steps--;
    }
}
