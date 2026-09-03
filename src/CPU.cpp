#include "CPU.hpp"
#include "RAM.hpp"

#include <string_view>
#include <stdexcept>
#include <format>

void CPU::fetch()
{
    ins = memory.read_memory(PC++);
}

void CPU::decode()
{
    switch (ins)
    {
        case 0x00:
        {   
            decoded_ins.type = "JUMP";
            decoded_ins.addr_mode = "IMP";
            decoded_ins.mnemonic = "BRK";
            break;
        }
        case 0x81:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "IND_X";
            decoded_ins.mnemonic = "STA";
            break;
        }
        case 0x84:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ZP";
            decoded_ins.mnemonic = "STY";
            break;
        }
        case 0x85:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ZP";
            decoded_ins.mnemonic = "STA";
            break;
        }
        case 0x86:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ZP";
            decoded_ins.mnemonic = "STX";
            break;
        }
        case 0x8A:
        {
            decoded_ins.type = "TRANSFER";
            decoded_ins.addr_mode = "IMP";
            decoded_ins.mnemonic = "TXA";
        }
        case 0x8C:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ABS";
            decoded_ins.mnemonic = "STY";
            break;
        }
        case 0x8D:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ABS";
            decoded_ins.mnemonic = "STA";
            break;
        }
        case 0x8E:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ABS";
            decoded_ins.mnemonic = "STX";
            break;
        }
        case 0x91:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "IND_Y";
            decoded_ins.mnemonic = "STA";
            break;
        }
        case 0x94:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ZP_X";
            decoded_ins.mnemonic = "STY";
            break;
        }
        case 0x95:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ZP_X";
            decoded_ins.mnemonic = "STA";
            break;
        }
        case 0x96:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ZP_Y";
            decoded_ins.mnemonic = "STX";
            break;
        }
        case 0x98:
        {
            decoded_ins.type = "TRANSFER";
            decoded_ins.addr_mode = "IMP";
            decoded_ins.mnemonic = "TYA";
        }
        case 0x99:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ABS_Y";
            decoded_ins.mnemonic = "STA";
            break;
        }
        case 0x9A:
        {
            decoded_ins.type = "TRANSFER";
            decoded_ins.addr_mode = "IMP";
            decoded_ins.mnemonic = "TXS";
        }
        case 0x9D:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ABS_X";
            decoded_ins.mnemonic = "STA";
            break;
        }
        case 0xA0:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "IMD";
            decoded_ins.mnemonic = "LDY";
            break;
        }
        case 0xA1:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "IND_X";
            decoded_ins.mnemonic = "LDA";
            break;
        }
        case 0xA2:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "IMD";
            decoded_ins.mnemonic = "LDX";
            break;
        }
        case 0xA4:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ZP";
            decoded_ins.mnemonic = "LDY";
            break;
        }
        case 0xA5:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ZP";
            decoded_ins.mnemonic = "LDA";
            break;
        }
        case 0xA6:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ZP";
            decoded_ins.mnemonic = "LDX";
            break;
        }
        case 0xA8:
        {
            decoded_ins.type = "TRANSFER";
            decoded_ins.addr_mode = "IMP";
            decoded_ins.mnemonic = "TAY";
        }
        case 0xA9:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "IMD";
            decoded_ins.mnemonic = "LDA";
            break;
        }
        case 0xAA:
        {
            decoded_ins.type = "TRANSFER";
            decoded_ins.addr_mode = "IMP";
            decoded_ins.mnemonic = "TAX";
        }
        case 0xAC:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ABS";
            decoded_ins.mnemonic = "LDY";
            break;
        }
        case 0xAD:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ABS";
            decoded_ins.mnemonic = "LDA";
            break;
        }
        case 0xAE:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ABS";
            decoded_ins.mnemonic = "LDX";
            break;
        }
        case 0xB1:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "IND_Y";
            decoded_ins.mnemonic = "LDA";
            break;
        }
        case 0xB4:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ZP_X";
            decoded_ins.mnemonic = "LDY";
            break;
        }
        case 0xB5:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ZP_X";
            decoded_ins.mnemonic = "LDA";
            break;
        }
        case 0xB6:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ZP_Y";
            decoded_ins.mnemonic = "LDX";
            break;
        }
        case 0xB9:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ABS_Y";
            decoded_ins.mnemonic = "LDA";
            break;
        }
        case 0xBA:
        {
            decoded_ins.type = "TRANSFER";
            decoded_ins.addr_mode = "IMP";
            decoded_ins.mnemonic = "TSX";
        }
        case 0xBC:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ABS_X";
            decoded_ins.mnemonic = "LDY";
            break;
        }
        case 0xBD:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ABS_X";
            decoded_ins.mnemonic = "LDA";
            break;
        }
        case 0xBE:
        {
            decoded_ins.type = "ACCESS";
            decoded_ins.addr_mode = "ABS_Y";
            decoded_ins.mnemonic = "LDX";
            break;
        }
        default:
        {
            if (version.WD)
            {
                decoded_ins.type = "OTHER";
                decoded_ins.addr_mode = "IMP";
                decoded_ins.mnemonic = "NOP";
            }
            else
            {
                throw std::invalid_argument("Invalid opcode");
            }
            break;
        }
    }
}

void CPU::execute()
{
    if (decoded_ins.type == "ACCESS")
    {
        access_ins();
    }
    else if (decoded_ins.type == "TRANSFER")
    {
        trasfer_ins();
    }
    else if (decoded_ins.type == "OTHER")
    {
        other_ins();
    }
    else
    {
        throw std::invalid_argument("Ivalid instruction type");
    }
}

/**
 * 
 * Access instructions are LDA, LDX, LDY, STA, STX, STY
 * 
 */
void CPU::access_ins()
{
    word addr = decode_addr();

    byte data = memory.read_memory(addr);

    if (decoded_ins.mnemonic == "LDA")
    {    
        A = data;

        set_flags("A");
    }
    else if (decoded_ins.mnemonic == "LDX")
    {
        X = data;
        set_flags("X");
    }
    else if (decoded_ins.mnemonic == "LDY")
    {
        Y = data;
        set_flags("Y");
    }
    else if (decoded_ins.mnemonic == "STA")
    {
        memory.write_memory(addr, A);
    }
    else if (decoded_ins.mnemonic == "STX")
    {
        memory.write_memory(addr, X);
    }
    else if (decoded_ins.mnemonic == "STY")
    {
        memory.write_memory(addr, Y);
    }
    else
    {
        throw std::invalid_argument("Ivalid Access instruction");
    }
}

void CPU::trasfer_ins()
{
    if (decoded_ins.mnemonic == "TAX")
    {
        X = A;
        set_flags("X");
    }
    else if (decoded_ins.mnemonic == "TAY")
    {
        Y = A;
        set_flags("Y");
    }
    else if (decoded_ins.mnemonic == "TSX")
    {
        X = SP;
        set_flags("X");
    }
    else if (decoded_ins.mnemonic == "TXA")
    {
        A = X;
        set_flags("A");
    }
    else if (decoded_ins.mnemonic == "TXS")
    {
        SP = X;
    }
    else if (decoded_ins.mnemonic == "TSX")
    {
        X = SP;
        set_flags("X");
    }
    else
    {
        throw std::invalid_argument("Invalid tansfer instruction");
    }
}

/**
 * 
 * Negative, Zero, and Carry flags are set based on the result of the compare
 * 
 */
void CPU::compare_ins()
{
    word addr = decode_addr();
    byte mem_val = memory.read_memory(addr);
    byte reg_val;

    if (decoded_ins.mnemonic == "CMP")
    {
        reg_val = A;
    }
    else if (decoded_ins.mnemonic == "CPX")
    {
        reg_val = X;
    }
    else if (decoded_ins.mnemonic == "CPY")
    {
        reg_val = Y;
    }
    else
    {
        throw std::invalid_argument("Invalid Compare instruction");
    }

    //TODO: set N, Z, C flags to 0
    if (reg_val >= mem_val)
    {
        //TODO: set carry flag
    }
     
    if (reg_val == mem_val)
    {
        //TODO: set zero flag
    }
    
    if ((reg_val - mem_val) & 0x80)
    {
        //TODO: set negative flag
    }
}

void CPU::other_ins()
{
    if (decoded_ins.mnemonic == "NOP")
    {
        // Do nothing
    }
    else
    {
        throw std::invalid_argument("Invalid Other instruction");
    }
}

/**
 * 
 * Set negative and zero flags 
 * 
 * Valid registers are A, X, Y
 * 
 */
void CPU::set_flags(std::string_view reg)
{
    if (reg == "A")
    {
        if (A == 0)
        {
            PS |= 0b10000000;
        }

        if (A & 0x80)
        {
            PS |= 0b00000001;
        }
    }
    else if (reg == "X")
    {
        if (X == 0)
        {
            PS |= 0b10000000;
        }

        if (X & 0x80)
        {
            PS |= 0b00000001;
        }
    }
    else if (reg == "Y")
    {
        if (Y == 0)
        {
            PS |= 0b10000000;
        }

        if (Y & 0x80)
        {
            PS |= 0b00000001;
        }
    }
    else
    {
        throw std::invalid_argument("Valid registers are A, X, Y");
    }
}

/**
 * 
 * Set negative, zero, and carry flags for compare instructions
 * 
 */
void CPU::set_flags(byte value, byte compare)
{
    //TODO: set N, Z, C flags to 0
    if (value >= compare)
    {
        //TODO: set carry flag
    }
     
    if (value == compare)
    {
        //TODO: set zero flag
    }
    
    if ((value - compare) & 0x80)
    {
        //TODO: set negative flag
    }
}

word CPU::decode_addr()
{
    word addr;

    if (decoded_ins.addr_mode == "IMD")
    {
        addr = PC++;
    }
    else if (decoded_ins.addr_mode == "ZP")
    {
        addr = memory.read_memory(PC++);
    }
    else if (decoded_ins.addr_mode == "ZP_X")
    {
        addr = (memory.read_memory(PC++) + X) & 0xFF;
    }
    else if (decoded_ins.addr_mode == "ABS")
    {
        byte lo = memory.read_memory(PC++);
        byte hi = memory.read_memory(PC++);

        addr = (hi << 8) | lo;
    }
    else if (decoded_ins.addr_mode == "ABS_X")
    {
        byte lo = memory.read_memory(PC++);
        byte hi = memory.read_memory(PC++);

        addr = ((hi << 8) | lo) + X;
    }
    else if (decoded_ins.addr_mode == "ABS_Y")
    {
        byte lo = memory.read_memory(PC++);
        byte hi = memory.read_memory(PC++);

        addr = ((hi << 8) | lo) + Y;
    }
    else if (decoded_ins.addr_mode == "IND_X")
    {
        byte zp = memory.read_memory(PC++);
        zp += X;

        byte lo = memory.read_memory(zp);
        byte hi = memory.read_memory((byte)(zp + 1));

        addr = (hi << 8) | lo;
    }
    else if (decoded_ins.addr_mode == "IND_Y")
    {
        byte zp = memory.read_memory(PC++);

        byte lo = memory.read_memory(zp);
        byte hi = memory.read_memory((byte)(zp + 1));

        addr = ((hi << 8) | lo) + Y;
    }
    else
    {
        throw std::invalid_argument("Invalid addressing mode.");
    }

    return addr;
}

/**
 * 
 * Valid options are WD, REV_D
 * All other options are considered the original 6502
 * 
 */
CPU::CPU(RAM& pass_memory, std::string_view option, bool INVOPS) : memory(pass_memory)
{
    if (option == "WD")
    {
        version.WD = true;
    }
    else if (option == "REV_D")
    {
        version.REV_D = true;
    }

    if (INVOPS)
    {
        version.INVOPS = true;
    }
}

CPU::~CPU()
{
    
}


void CPU::write_register(std::string_view reg, byte value)
{
    if (reg == "A")
    {
        A = value;
    }
    else if (reg == "X")
    {
        X = value;
    }
    else if (reg == "Y")
    {
        Y = value;
    }
    else if (reg == "SP")
    {
        SP = value;
    }
    else if (reg == "PS")
    {
        PS = value;
    }
    else
    {
        throw std::invalid_argument("Valid registers are A, X, Y, SP, PS\n"
                                    "PC requires a word instead of a byte");
    }
}

void CPU::write_register(std::string_view reg, word value)
{
    if (reg == "PC")
    {
        PC = value;
    }
    else
    {
        throw std::invalid_argument("Valid word register is only PC");
    }
}

byte CPU::read_register(std::string_view reg)
{
    if (reg == "A")
    {
        return A;
    }
    else if (reg == "X")
    {
        return X;
    }
    else if (reg == "Y")
    {
        return Y;
    }
    else if (reg == "SP")
    {
        return SP;
    }
    else if (reg == "PS")
    {
        return PS;
    }
    else if (reg == "ins")
    {
        return ins;
    }
    else
    {
        throw std::invalid_argument("Valid registers are A, X, Y, SP, PS\n"
                                    "Read PC with read_PC()");
    }
}

word CPU::read_PC()
{
    return PC;
}

std::string CPU::decode_PS()
{
    bool N = PS & 0b10000000;
    bool V = PS & 0b01000000;
//  bool B = PS & 0b00010000;
    bool D = PS & 0b00001000;
    bool I = PS & 0b00000100;
    bool Z = PS & 0b00000010;
    bool C = PS & 0b00000001;
    
    std::string ret = std::format(" Negative: {}\n"
                                  " Overflow: {}\n"
                                  " Reserved: Blank\n"
                                  "  Decimal: {}\n"
                                  "Interrupt: {}\n"
                                  "     Zero: {}\n"
                                  "    Carry: {}\n", 
                                  N, V, D, I, Z, C);
    return ret;
}