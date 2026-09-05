#include "CPU.hpp"
#include "RAM.hpp"
#include "types.hpp"
#include "inputHandlers.hpp"

#include <iostream>
#include <print>

std::pair<std::string, bool> handle_CPU_options();


int main()
{
    const std::pair<std::string, bool> CPU_options = handle_CPU_options();

    RAM _RAM = RAM();
    CPU _CPU = CPU(_RAM, CPU_options.first, CPU_options.second);

    // printf("Debug\n");
    return 0;
}

std::pair<std::string, bool> handle_CPU_options()
{
    std::array<std::string, 3> CPU_options = {"6502", "REV_D", "WD"};
    
    std::string_view CPU_option_prompt = "Choose CPU version (Options are 6502, REV_D, WD): ";
    std::string_view INVOPS_prompt = "Enable invalid opcodes?";

    int optionIndex = inputHandlers::promptSelection(CPU_option_prompt, CPU_options, 0);
    bool INVOPS = inputHandlers::query_yes_no(false, INVOPS_prompt);

    if(INVOPS && CPU_options[optionIndex] == "WD")
    {
        std::println(std::cerr, "The W65C02 does not have invalid opcodes.");
        std::exit(EXIT_FAILURE);
    }

    return {CPU_options[optionIndex], INVOPS};
}