#pragma once

#include "Utils/Parser.h"

#include <iostream>

namespace Utils
{
    [[nodiscard]] int32_t GetRandomInt(int32_t from, int32_t to);



    /**
    *  Indicates that value T can be moved (own implementation of std::move)
    */
    template<typename T>
    [[nodiscard]] constexpr T&& Move(T&& val) noexcept;

    /**
    *  Indicates that value T can be moved (own implementation of std::move)
    */
    template<typename T>
    [[nodiscard]] constexpr T&& Move(T& val) noexcept;

    template<typename T>
    constexpr void Swap(T& val1, T& val2) noexcept;

    template<typename T>
    std::optional<T> getInput();





    template<typename T>
    [[nodiscard]] constexpr T&& Move(T&& val) noexcept
    {
        return static_cast<T&&>(val);
    }

    template<typename T>
    [[nodiscard]] constexpr T&& Move(T& val) noexcept
    {
        return static_cast<T&&>(val);
    }

    template<typename T>
    constexpr void Swap(T& val1, T& val2) noexcept
    {
        T tmp = Move(val1);
        val1  = Move(val2);
        val2  = Move(tmp);
    }

    template<typename T>
    std::optional<T> getInput()
    {
        static_assert(std::is_same_v<T, std::string> ||std::is_same_v<T, char> || std::is_arithmetic_v<T>);
        std::string input;
        std::cin >> input;
        if constexpr(std::is_same_v<T, std::string>)
        {
            return input;
        }
        else if (std::is_same_v<T, char>)
        {
            return input[0];
        }
        else if (std::is_arithmetic_v<T>)
        {
            return Parser::string_to_number<T>(input);
        }
    }
}