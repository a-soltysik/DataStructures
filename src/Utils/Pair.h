#pragma once

#include <utility>

namespace Utils
{
    template<typename T1, typename T2>
    struct Pair
    {
        T1 first;
        T2 second;
    };

    template<typename T1, typename T2>
    Pair<T1, T2> MakePair(T1&& value1, T2&& value2)
    {
        return {std::forward<T1>(value1), std::forward<T2>(value2)};
    }
}