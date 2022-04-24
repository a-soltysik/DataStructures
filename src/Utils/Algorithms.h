#pragma once

#include "Utils/Utils.h"

#include <algorithm>
namespace Utils
{

template<typename It>
It Previous(It it);

template<typename It>
It Next(It it);

template<typename It, typename Comparator>
void QuickSort(It first, It last, Comparator comparator);

template<typename It>
void QuickSort(It first, It last);

/**
 * DEFINITIONS
 */

namespace Impl
{

template<typename It, typename Comparator>
It Partition(It first, It last, Comparator comparator);

}

template<typename It>
It Previous(It it)
{
    return --it;
}

template<typename It>
It Next(It it)
{
    return ++it;
}

template<typename It, typename Comparator>
void QuickSort(It first, It last, Comparator comparator)
{
    if (first < last)
    {
        It mid = Impl::Partition(first, last, comparator);
        QuickSort(first, mid, comparator);
        QuickSort(Next(mid), last, comparator);
    }
}

template<typename It>
void QuickSort(It first, It last)
{
    QuickSort(first, last, Less<decltype(*first)>());
}

namespace Impl
{

template<typename It, typename Comparator>
It Partition(It first, It last, Comparator comparator)
{
    auto pivot = Previous(last);
    auto i = first;
    for (auto j = first; j != pivot; j++)
    {
        if (comparator(*j, *pivot))
        {
            Swap(*i++, *j);
        }
    }
    Swap(*i, *pivot);
    return i;
}

}}