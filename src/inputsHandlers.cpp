#include "inputHandlers.hpp"

#include <iostream>
#include <print>
#include <vector>
#include <memory>
#include <sstream>

namespace inputHandlers
{
    int promptSelection(std::string_view question, 
                        std::span<const std::string> options, 
                        std::optional<int> defaultIndex)
    {
        if (defaultIndex.has_value() && static_cast<size_t>(*defaultIndex) >= options.size())
        {
            std::println(std::cerr, "default index is larger than the max index");
            std::exit(EXIT_FAILURE);
        }

        while (true) {
            std::cout << "\n? " << question << "\n";
            for (size_t i = 0; i < options.size(); ++i) {
                std::cout << "  " << (i + 1) << ") " << options[i] << "\n";
            }

            bool hasValidDefault = defaultIndex.has_value() && 
                                *defaultIndex >= 0 && 
                                *defaultIndex < static_cast<int>(options.size());

            if (hasValidDefault) {
                std::cout << "Select an option [default: " << (*defaultIndex + 1) << "]: ";
            } else {
                std::cout << "Select an option [1-" << options.size() << "]: ";
            }
            
            std::string input;
            std::getline(std::cin, input);

            if (input.empty()) {
                if (hasValidDefault) {
                    return *defaultIndex;
                }
                // std::cout << "Selection required. Please try again.\n";
                // continue; 
            }

            std::stringstream ss(input);
            int choice = -1;
            if (ss >> choice && choice >= 1 && choice <= static_cast<int>(options.size())) {
                return choice - 1;
            }

            // std::cout << "Invalid selection. Please try again.\n";
        }
    }

    bool query_yes_no(std::optional<bool> defualt_yes, std::string_view prompt)
    {
        std::string kprompt{prompt};
        std::string response;

        if (!defualt_yes.has_value())
        {
            kprompt += " (y/n): ";

            while (true)
            {
                std::print("{}", kprompt);
                std::getline(std::cin, response);

                if (response == "y"  || response ==  "Y" || response == "Yes" || response == "yes")
                {
                    return true;
                }
                else if (response == "n" || response ==  "N" || response == "No" || response == "No")
                {
                    return false;
                }
            }
        }
        else if (*defualt_yes)
        {
            kprompt += " [Y/n]: ";

            while (true)
            {
                std::print("{}", kprompt);
                std::getline(std::cin, response);

                if (response == "y"  || response ==  "Y" || response == "Yes" || response == "yes" || response == "")
                {
                    return true;
                }
                else if (response == "n" || response ==  "N" || response == "No" || response == "No")
                {
                    return false;
                }
            }
            
        }
        else
        {
            kprompt += " [y/N]: ";

            while (true)
            {
                std::print("{}", kprompt);
                std::getline(std::cin, response);

                if (response == "y"  || response ==  "Y" || response == "Yes" || response == "yes")
                {
                    return true;
                }
                else if (response == "n" || response ==  "N" || response == "No" || response == "no" || response == "")
                {
                    return false;
                }
            }
            
        }
    }
}