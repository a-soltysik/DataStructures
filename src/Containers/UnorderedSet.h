#pragma once

#include "List.h"

template<typename T>
class UnorderedSet
{
public:
    using DataType = T;
    using Iterator = typename List<DataType>::Iterator;
    using ConstIterator = typename List<DataType>::ConstIterator;

    [[nodiscard]] static constexpr const char* ClassName() { return "UnorderedSet"; }

    UnorderedSet() = default;
    UnorderedSet(std::initializer_list<DataType> initList);

    template<typename It>
    UnorderedSet(It first, It last);

    Iterator Insert(const DataType& value);
    bool Remove(const DataType& value);
    void Clear();

    [[nodiscard]] ConstIterator Find(const DataType& value) const;
    [[nodiscard]] Iterator Find(const DataType& value);

    [[nodiscard]] const DataType& Min() const;
    [[nodiscard]] const DataType& Max() const;

    [[nodiscard]] size_t Size() const;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;
    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;
    [[nodiscard]] ConstIterator cbegin() const noexcept;
    [[nodiscard]] ConstIterator cend() const noexcept;

    [[nodiscard]] std::string ToString() const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const UnorderedSet<U>& set);

    template<typename U>
    friend std::istream& operator>>(std::istream& is, UnorderedSet<U>& set);

private:
    List<T> list;
};

template<typename T>
UnorderedSet<T>::UnorderedSet(std::initializer_list<DataType> initList)
    : list(initList)
{ }

template<typename T>
template<typename It>
UnorderedSet<T>::UnorderedSet(It first, It last)
    : list(first, last)
{ }


template<typename T>
typename UnorderedSet<T>::Iterator UnorderedSet<T>::Insert(const DataType& value)
{
    if (list.Find(value) != list.end())
    {
        return list.end();
    }
    list.PushBack(value);

    return --list.end();
}

template<typename T>
bool UnorderedSet<T>::Remove(const DataType& value)
{
    return list.Remove(value);
}

template<typename T>
void UnorderedSet<T>::Clear()
{
    list.Clear();
}

template<typename T>
typename UnorderedSet<T>::ConstIterator UnorderedSet<T>::Find(const DataType& value) const
{
    return list.Find(value);
}

template<typename T>
typename UnorderedSet<T>::Iterator UnorderedSet<T>::Find(const DataType& value)
{
    return list.Find(value);
}

template<typename T>
const typename UnorderedSet<T>::DataType& UnorderedSet<T>::Min() const
{
    return list.Min();
}

template<typename T>
const typename UnorderedSet<T>::DataType&  UnorderedSet<T>::Max() const
{
    return list.Max();
}

template<typename T>
size_t UnorderedSet<T>::Size() const
{
    return list.Size();
}

template<typename T>
typename UnorderedSet<T>::Iterator UnorderedSet<T>::begin() noexcept
{
    return list.begin();
}

template<typename T>
typename UnorderedSet<T>::Iterator UnorderedSet<T>::end() noexcept
{
    return list.end();
}

template<typename T>
typename UnorderedSet<T>::ConstIterator UnorderedSet<T>::begin() const noexcept
{
    return list.begin();
}

template<typename T>
typename UnorderedSet<T>::ConstIterator UnorderedSet<T>::end() const noexcept
{
    return list.end();
}

template<typename T>
typename UnorderedSet<T>::ConstIterator UnorderedSet<T>::cbegin() const noexcept
{
    return list.cbegin();
}

template<typename T>
typename UnorderedSet<T>::ConstIterator UnorderedSet<T>::cend() const noexcept
{
    return list.cend();
}

template<typename T>
std::string UnorderedSet<T>::ToString() const
{
    return list.ToString();
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const UnorderedSet<T>& set)
{
    return os << set.list;
}

template<typename T>
std::istream& operator>>(std::istream& is, UnorderedSet<T>& set)
{
    return is >> set.list;
}