#pragma once

#include <utility>

namespace Utils
{
    template<typename T1, typename T2>
    struct Pair
    {
        T1 first = T1();
        T2 second = T2();

        [[nodiscard]] constexpr bool operator==(const Pair& rhs) const noexcept
        {
            return first == rhs.first && second == rhs.second;
        }

        [[nodiscard]] constexpr bool operator!=(const Pair& rhs) const noexcept
        {
            return !(*this == rhs);
        }
    };

    template<typename T1, typename T2>
    Pair<T1, T2> MakePair(T1&& value1, T2&& value2)
    {
        return {std::forward<T1>(value1), std::forward<T2>(value2)};
    }
}