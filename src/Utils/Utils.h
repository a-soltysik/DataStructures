#pragma once

#include "Utils/Parser.h"

#include <fstream>
#include <type_traits>
#include <random>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Utils
{

constexpr char HORIZONTAL_BAR[] = "\xE2\x94\x80";
constexpr char VERTICAL_BAR[] = "\xE2\x94\x82";
constexpr char VERTICAL_BAR_RIGHT[] = "\xE2\x94\x9C";
constexpr char HALF_VERTICAL_BAR_RIGHT[] = "\xE2\x94\x94";

void SetUtf8();

template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
[[nodiscard]] T GetRandomNumber(T from, T to);

[[nodiscard]] uint32_t GetChoiceFromMenu(const std::string& menu, uint32_t min, uint32_t max);

template<typename T>
struct Less
{
    constexpr bool operator()(const T& lhs, const T& rhs) const noexcept
    {
        return lhs < rhs;
    }
};

template<typename T>
struct Greater
{
    constexpr bool operator()(const T& lhs, const T& rhs) const noexcept
    {
        return lhs > rhs;
    }
};

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

template<typename Derived, typename Base>
struct DerivedFrom
{
    static constexpr bool Value = std::is_base_of_v<Base, Derived> &&
                                  std::is_convertible_v<const volatile Derived*, const volatile Base*>;
};
/**
 * DEFINITIONS
 */

template<typename T, std::enable_if_t<std::is_integral_v<T>, bool>>
[[nodiscard]] T GetRandomNumber(T from, T to)
{
    static std::random_device device;
    static std::mt19937 rng(device());

    std::uniform_int_distribution<T> distribution(from, to);
    return distribution(rng);
}

template<typename T>
constexpr void Swap(T& val1, T& val2) noexcept(std::is_nothrow_move_constructible_v<T> &&
                                               std::is_nothrow_move_assignable_v<T>)
{
    T tmp = std::move(val1);
    val1 = std::move(val2);
    val2 = std::move(tmp);
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