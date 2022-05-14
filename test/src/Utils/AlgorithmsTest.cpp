#include <gtest/gtest.h>

#include "Utils/Algorithms.h"
#include "Containers/DynamicArray.h"

#include <algorithm>

TEST(AlgorithmsTest, QuickSortTest)
{
    DynamicArray<int32_t> array;

    for (size_t i = 0; i < 100; i++)
    {
        array.PushBack(Utils::GetRandomNumber<int32_t>(INT32_MIN, INT32_MAX));
    }

    Utils::QuickSort(array.begin(), array.end());

    std::is_sorted(array.begin(), array.end());
}


TEST(AlgorithmsTest, QuickSortCustomStructureTest)
{
    struct B
    {
        int number1;
        int number2;
    };

    struct A
    {
        B object;
        int number;
    };

    DynamicArray<A> array;

    for (size_t i = 0; i < 100; i++)
    {
        A a;
        a.object.number1 = Utils::GetRandomNumber<int32_t>(0, 10);
        a.object.number2 = Utils::GetRandomNumber<int32_t>(0, 10);
        a.number = Utils::GetRandomNumber<int32_t>(0, 10);
        array.PushBack(a);
    }

    Utils::QuickSort(array.begin(), array.end(), [] (const auto& a1, const auto& a2) {
        return a1.number < a2.number;
    });

    std::is_sorted(array.begin(), array.end(), [] (const auto& a1, const auto& a2) {
        return a1.number < a2.number;
    });
}