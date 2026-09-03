#pragma once

#include "types.hpp"

#include <cstdint>
#include <memory>

class RAM
{
private:
    std::unique_ptr<byte[]> memory = std::make_unique<byte[]>(0xFFFF);

public:
    RAM();
    ~RAM();

    byte read_memory(word address);
    void write_memory(word address, byte data);
};
