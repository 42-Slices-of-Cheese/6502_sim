#pragma once

#include "types.hpp"
#include "RAM.hpp"

#include <string_view>

struct instruction
{
    std::string type;
    std::string addr_mode;
    std::string mnemonic;
};

struct PS_status
{
    bool negative;
    bool overflow;
    bool brk_stack;
    
};

struct CPU_TYPE
{
        bool WD     = false;
        bool REV_D  = false;
        bool INVOPS = false;
};

class CPU
{
    private:
        CPU_TYPE version;

        RAM& memory;

        instruction decoded_ins;

        word PC;
        byte SP;

        byte A;
        
        byte X;
        byte Y;

        byte PS = 0b00100000;

        byte ins;

        void fetch();
        void decode();
        void execute();

        void access_ins();
        void trasfer_ins();
        void other_ins();
        void set_flags(std::string_view reg);
        void set_flags(std::string_view reg, byte compare);
        word decode_addr();
 
    public:
        byte data_bus = 0;
        word addr_bus = 0;
        bool reset_low = true;
        bool irq_low = true;

        // WDC 65C02S
        bool nmi_low = true;

        // Sally
        bool halt_low = true;

        CPU(RAM& pass_memory, std::string_view option, bool INVOPS);
        ~CPU();

        void write_register(std::string_view reg, byte value);
        void write_register(std::string_view reg, word value);
        void write_PS(std::string_view status); //TODO: figure this out (and the PS break flag as well)
        byte read_register(std::string_view reg);
        word read_PC();
        std::string decode_PS();
};