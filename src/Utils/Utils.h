#pragma once

#include "Utils/Parser.h"

#include <fstream>

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

    [[nodiscard]] uint32_t GetChoiceFromMenu(const std::string& menu, uint32_t min, uint32_t max);

    template<typename T>
    struct RemoveReference { using Type = T; };

    template<typename T>
    struct RemoveReference<T&> { using Type = T; };

    template<typename T>
    struct RemoveReference<T&&> { using Type = T; };

    /**
    *  Indicates that value T can be moved (own implementation of std::move)
    */
    template<typename T>
    [[nodiscard]] constexpr decltype(auto) Move(T&& val) noexcept;

    /**
    *  Swaps two values (own implementation of std::swap)
    */
    template<typename T>
    constexpr void Swap(T& val1, T& val2) noexcept(std::is_nothrow_move_constructible_v<T> &&
                                                   std::is_nothrow_move_assignable_v<T>);

    /**
    *  Retuns maximum of two values (own implementation of std::max)
    */
    template<typename T>
    [[nodiscard]] constexpr const T& Max(const T& val1, const T& val2) noexcept(noexcept(val1 > val2));

    template<typename T>
    [[nodiscard]] std::optional<T> getInput(std::istream& is, bool isEofAcceptable);

    /**
     * DEFINITIONS
     */


    template<typename T>
    constexpr decltype(auto) Move(T&& val) noexcept
    {
        using ReturnType = typename RemoveReference<T>::Type &&;
        return static_cast<ReturnType>(val);
    }

    template<typename T>
    constexpr void Swap(T& val1, T& val2) noexcept(std::is_nothrow_move_constructible_v<T> &&
                                                   std::is_nothrow_move_assignable_v<T>)
    {
        T tmp = Move(val1);
        val1 = Move(val2);
        val2 = Move(tmp);
    }

    template<typename T>
    constexpr const T& Max(const T& val1, const T& val2) noexcept(noexcept(val1 > val2))
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
        if (!is.fail())
        {
            return value;
        }
        return {};
    }
}