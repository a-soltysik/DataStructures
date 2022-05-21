#pragma once

#include <optional>
#include <charconv>
#include <limits>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iomanip>

namespace Utils::Parser
{

template<typename T>
std::string ToString(const T& value);

/**
*  Returns maximum length of decimal representation of the given type
*/
template<typename T>
constexpr uint32_t MaxLengthOfType();

template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
std::optional<T> StringToNumber(const std::string& number);

template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
std::optional<T> StringToNumber(const std::string& number);

template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
std::string NumberToString(T number);

template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
std::string NumberToString(T number);

template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
std::string NumberToString(T number, int32_t precision);


/**
 * DEFINITONS
 */

template<typename T>
std::string ToString(const T& value)
{
    if constexpr(std::is_arithmetic_v<T>)
    {
        return NumberToString(value);
    }
    else if constexpr(std::is_same_v<char*, std::decay_t<T>> ||
                      std::is_same_v<const char*, std::decay_t<T>> ||
                      std::is_same_v<std::string, std::decay_t<T>>)
    {
        return value;
    }
    else
    {
        return value.ToString();
    }
}


template<typename T>
constexpr uint32_t MaxLengthOfType()
{
    static_assert(std::is_arithmetic_v<T>);
    if constexpr (std::is_integral<T>::value)
    {
        return std::numeric_limits<T>::digits10 + 2;
    }
    return std::numeric_limits<T>::max_exponent10 +
           std::numeric_limits<T>::max_digits10 + 2;
}

template<typename T, std::enable_if_t<std::is_integral_v<T>, bool>>
std::optional<T> StringToNumber(const std::string& number)
{
    T result;
    auto const[ptr, code] {std::from_chars(number.data(), number.data() + number.length(), result)};

    if (code == std::errc::invalid_argument || code == std::errc::result_out_of_range)
    {
        return {};
    }

    return result;
}

/**
 * GCC does not support std::from_chars for floating point types (although it is standardized
 */

#if defined(__clang__) || defined(_MSC_VER)

template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool>>
std::optional<T> StringToNumber(const std::string& number)
{
    T result;
    auto const[ptr, code] {std::from_chars(number.data(), number.data() + number.length(), result)};

    if (code == std::errc::invalid_argument || code == std::errc::result_out_of_range)
    {
        return {};
    }

    return result;
}

#else

template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool>>
std::optional<T> StringToNumber(const std::string& number)
{
    try
    {
        return std::stof(number);
    }
    catch (const std::out_of_range& e)
    {
        return {};
    }
    catch (const std::invalid_argument& e)
    {
        return {};
    }
}

#endif

template<typename T, std::enable_if_t<std::is_integral_v<T>, bool>>
std::string NumberToString(T number)
{
    static_assert(std::is_integral_v<T>);
    constexpr int size = MaxLengthOfType<T>();
    char buffer[size] = {0};
    std::to_chars(buffer, buffer + size, number);
    std::string result {buffer};
    result.erase(std::find(result.begin(), result.end(), '\0'), result.end());
    return result;
}

template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool>>
std::string NumberToString(T number)
{
    std::stringstream stream;
    stream << number;
    return stream.str();
}

template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool>>
std::string NumberToString(T number, int32_t precision)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << number;
    return stream.str();
}

}