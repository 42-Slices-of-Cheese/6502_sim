#include "RAM.hpp"

#include <cstdint>

RAM::RAM()
{

}

RAM::~RAM()
{
    
}

byte RAM::read_memory(word address)
{
    return memory[address];
}

void RAM::write_memory(word address, byte data)
{
    memory[address] = data;
}