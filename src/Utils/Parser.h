#pragma once

#include <optional>
#include <charconv>
#include <limits>
#include <string>
#include <algorithm>

namespace Utils::Parser
{
    /**
    *  Returns maximum length of decimal representation of the given type
    */
    template<typename T>
    constexpr uint32_t max_length_of_number();

    template<typename T>
    std::optional<T> string_to_number(const std::string& number);

    template<typename T>
    std::string number_to_string(T number);

    template<typename T>
    constexpr uint32_t max_length_of_number() {
        static_assert(std::is_arithmetic_v<T>);
        if constexpr (std::is_integral<T>::value) {
            return std::numeric_limits<T>::digits10 + 2;
        }
        return std::numeric_limits<T>::max_exponent10 +
               std::numeric_limits<T>::max_digits10 + 2;
    }

    template<typename T>
    std::optional<T> string_to_number(const std::string& number) {
        T result;
        auto const [ptr, code] { std::from_chars(number.data(), number.data() + number.length(), result) };

        if (code == std::errc::invalid_argument || code == std::errc::result_out_of_range) {
            return {};
        }

        return result;
    }

    template<typename T>
    std::string number_to_string(T number) {
        static_assert(std::is_integral_v<T>);
        constexpr int size = max_length_of_number<T>();
        char buffer[size] = {0};
        if (std::is_integral<T>::value) {
            std::to_chars(buffer, buffer + size, number);
        }
        std::string result {buffer};
        result.erase(std::find(result.begin(), result.end(), '\0'), result.end());
        return result;
    }
}