#pragma once

#include <string>
#include <span>
#include <optional>


namespace inputHandlers
{
    int promptSelection(std::string_view question, 
                        std::span<const std::string> options, 
                        std::optional<int> defaultIndex = std::nullopt);

    bool query_yes_no(std::optional<bool> defualt_yes, std::string_view prompt);
}