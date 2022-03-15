#include "Utils/Parser.h"

namespace Utils::Parser
{
    template<>
    std::string number_to_string<float>(float number) {
        constexpr int size = max_length_of_number<float>();
        char buffer[size] = {0};
        std::to_chars(buffer, buffer + size, number, std::chars_format::fixed);

        return {buffer};
    }

    template<>
    std::string number_to_string<double>(double number) {
        constexpr int size = max_length_of_number<double>();
        char buffer[size] = {0};
        std::to_chars(buffer, buffer + size, number, std::chars_format::fixed);

        return {buffer};
    }

    template<>
    std::string number_to_string<long double>(long double number) {
        constexpr int size = max_length_of_number<long double>();
        char buffer[size] = {0};
        std::to_chars(buffer, buffer + size, number, std::chars_format::fixed);

        return {buffer};
    }
}