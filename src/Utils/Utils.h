#pragma once

#include "Utils/Parser.h"

#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#endif


namespace Utils
{
    constexpr char HORIZONTAL_BAR[]          = "\xE2\x94\x80";
    constexpr char VERTICAL_BAR[]            = "\xE2\x94\x82";
    constexpr char VERTICAL_BAR_RIGHT[]      = "\xE2\x94\x9C";
    constexpr char HALF_VERTICAL_BAR_RIGHT[] = "\xE2\x94\x94";

    void SetUtf8();

    [[nodiscard]] int32_t GetRandomInt(int32_t from, int32_t to);
    [[nodiscard]] std::filesystem::path GetPathFromResources(const std::filesystem::path& path);

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

    /**
    *  Swaps to values (own implementation of std::swap)
    */
    template<typename T>
    constexpr void Swap(T& val1, T& val2) noexcept;

    template<typename T>
    [[nodiscard]] constexpr T Max(const T& ...) noexcept;

    template<typename T>
    std::optional<T> getInput(std::istream& is);


    /**
     * DEFINITIONS
     */


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
        val1 = Move(val2);
        val2 = Move(tmp);
    }

    template<typename T>
    [[nodiscard]] T Max(const T& val1, const T& val2) noexcept
    {
        return val1 > val2 ? val1 : val2;
    }

    template<typename T>
    std::optional<T> getInput(std::istream& is)
    {
        static_assert(std::is_default_constructible_v<T>);

        T value;

        if constexpr(std::is_same_v<T, char>)
        {
            std::string input;
            is >> input;
            value = input[0];
        }
        else if constexpr(std::is_arithmetic_v<T>)
        {
            std::string input;
            is >> input;
            auto opt = Parser::StringToNumber<T>(input);
            if (opt.has_value())
            {
                value = opt.value();
            }
            else
            {
                return {};
            }
        }
        else
        {
            is >> value;
        }
        if (is.good())
        {
            return value;
        }
        return {};
    }
}