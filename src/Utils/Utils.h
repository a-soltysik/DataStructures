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

constexpr char HORIZONTAL_BAR[]                     = "\xE2\x94\x80";
constexpr char VERTICAL_BAR[]                       = "\xE2\x94\x82";
constexpr char VERTICAL_BAR_RIGHT[]                 = "\xE2\x94\x9C";
constexpr char VERTICAL_BAR_LEFT[]                  = "\xE2\x94\xA4";
constexpr char UP_RIGHT[]                           = "\xE2\x94\x94";
constexpr char UP_LEFT[]                            = "\xE2\x94\x98";
constexpr char CROSS[]                              = "\xE2\x94\xBC";
constexpr char DOUBLE_CROSS[]                       = "\xE2\x95\xAC";
constexpr char HORIZONTAL_BAR_UP[]                  = "\xE2\x94\xB4";
constexpr char DOUBLE_HORIZONTAL_BAR[]              = "\xE2\x95\x90";
constexpr char DOUBLE_VERTICAL_BAR[]                = "\xE2\x95\x91";
constexpr char VERTICAL_BAR_DOUBLE_LEFT[]           = "\xE2\x95\xA1";
constexpr char DOUBLE_VERTICAL_BAR_HORIZONTAL_BAR[] = "\xE2\x95\xAB";
constexpr char HORIZONTAL_BAR_DOUBLE_UP[]           = "\xE2\x95\xA8";
constexpr char DOUBLE_HORIZONTAL_BAR_VERTICAL_BAR[] = "\xE2\x95\xAA";

template<typename Derived, typename Base>
struct DerivedFrom
{
    static constexpr bool Value = std::is_base_of_v<Base, Derived> &&
                                  std::is_convertible_v<const volatile Derived*, const volatile Base*>;
};

template<typename T>
struct Less
{
    [[nodiscard]] constexpr bool operator()(const T& lhs, const T& rhs) const noexcept
    {
        return lhs < rhs;
    }
};

template<typename T>
struct Greater
{
    [[nodiscard]] constexpr bool operator()(const T& lhs, const T& rhs) const noexcept
    {
        return lhs > rhs;
    }
};

/**
 * Enables console to utf-8 mode
 */
void SetUtf8();

/**
 * @param menu text to be printed
 * @param min minimal value to retrieve
 * @param max maximal value to retrieve
 * @return a value given from user from range [min, max]
 */
[[nodiscard]] uint32_t GetChoiceFromMenu(const std::string& menu, uint32_t min, uint32_t max);

/**
 * @tparam T integral type of a number
 * @param from minimal value
 * @param to maximal value
 * @return a pseudo-random number from range [min, max]
 */
template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
[[nodiscard]] T GetRandomNumber(T from, T to);

/**
 * @tparam T unsigned integral type of numbers
 * @param x first number to add
 * @param y second number to add
 * @return x + y if it is smaller than maximum of the type, otherwise maximum of the type
 */
template<typename T, std::enable_if_t<std::is_integral_v<T> && std::is_unsigned_v<T>, bool> = true>
[[nodiscard]] T SaturatingAdd(T x, T y);

/**
 * @tparam T type of an object
 * @param object an object to be printed
 * @param width width of a string
 * @param space chars among which object is to be written
 * @return string with centered object
 */
template<typename T>
[[nodiscard]] std::string PutInStringCenter(const T& object, size_t width, char space = ' ');

/**
 * Own implementation of std::swap
 */
template<typename T>
constexpr void Swap(T& val1, T& val2) noexcept(std::is_nothrow_move_constructible_v<T> &&
                                               std::is_nothrow_move_assignable_v<T>);

/**
 * Own implementation of std::max
 * @return maximum of two values
 */
template<typename T>
[[nodiscard]] constexpr const T& Max(const T& val1, const T& val2) noexcept(noexcept(val1 > val2));

/**
 * @tparam T type of object to be retrieved
 * @param is stream
 * @return object T if input was successful otherwise, std::nullopt
 */
template<typename T>
[[nodiscard]] std::optional<T> GetInput(std::istream& is);

template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, bool> = true>
[[nodiscard]] constexpr T Abs(T number) noexcept;

template<typename T, std::enable_if_t<std::is_integral_v<T>, bool>>
T GetRandomNumber(T from, T to)
{
    static std::random_device device;
    static std::mt19937 rng(device());

    std::uniform_int_distribution<T> distribution(from, to);
    return distribution(rng);
}

template<typename T, std::enable_if_t<std::is_integral_v<T> && std::is_unsigned_v<T>, bool>>
T SaturatingAdd(T x, T y)
{
    T result = x + y;
    result |= -(result < x);

    return result;
}

template<typename T>
std::string PutInStringCenter(const T& object, size_t width, char space)
{
    std::string objectStr = Parser::ToString(object);
    if (width <= objectStr.length())
    {
        return objectStr;
    }

    size_t halfSpaces = (width - objectStr.length()) / 2;

    return std::string(halfSpaces, space) + objectStr + std::string(width - halfSpaces - objectStr.length(), space);
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

template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, bool>>
[[nodiscard]] constexpr T Abs(T number) noexcept
{
    return number >= 0 ? number : -number;
}

template<typename T>
std::optional<T> GetInput(std::istream& is)
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