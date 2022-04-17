#pragma once

#include "Containers/DynamicArray.h"

#include "Utils/Utils.h"

template<typename T>
class Heap
{
public:
    using DataType = typename DynamicArray<T>::DataType;
    using Iterator = DynamicArrayIterator<T>;
    using ConstIterator = DynamicArrayConstIterator<T>;

    [[nodiscard]] static constexpr const char* ClassName() { return "Heap"; }

    Heap() = default;
    Heap(std::initializer_list<DataType> initList);
    explicit Heap(const DynamicArray<T>& array);

    void Assign(const DynamicArray<T>& array);
    void Insert(const DataType& value);
    bool Remove(const DataType& value);
    void Pop();
    void Clear();

    [[nodiscard]] Iterator Find(const DataType& value) noexcept;
    [[nodiscard]] ConstIterator Find(const DataType& value) const noexcept;

    [[nodiscard]] const DataType& Max() const;

    [[nodiscard]] const DynamicArray<T>& Array() const;
    [[nodiscard]] size_t Size() const noexcept;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;
    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;
    [[nodiscard]] ConstIterator cbegin() const noexcept;
    [[nodiscard]] ConstIterator cend() const noexcept;

    [[nodiscard]] std::string ToString() const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Heap<U>& heap);

    template<typename U>
    friend std::istream& operator>>(std::istream& is, Heap<U>& heap);

private:
    [[nodiscard]] static size_t Parent(size_t node) noexcept;

    void RemoveAt(size_t node);
    void RestoreDown(size_t node);

    [[nodiscard]] size_t Find(const DataType& value, size_t root) const;

    [[nodiscard]] size_t Left(size_t parent) const noexcept;
    [[nodiscard]] size_t Right(size_t parent) const noexcept;

    void ToString(std::string& result, const std::string& prefix, size_t node, bool isRight) const;

    DynamicArray<T> data;
};

template<typename T>
Heap<T>::Heap(std::initializer_list<DataType> initList)
{
    for (const auto& element: initList)
    {
        Insert(element);
    }
}

template<typename T>
Heap<T>::Heap(const DynamicArray<T>& array)
{
    Assign(array);
}

template<typename T>
void Heap<T>::Assign(const DynamicArray<T>& array)
{
    data = array;
    for (size_t i = array.Size() / 2 - 1; i-- > 0;)
    {
        RestoreDown(i);
    }
}

template<typename T>
void Heap<T>::Insert(const DataType& value)
{
    data.PushBack(value);
    size_t position = data.Size() - 1;
    size_t nextPosition = (position - 1) / 2;

    while (position != 0u && data[nextPosition] < value)
    {
        Utils::Swap(data[position], data[nextPosition]);
        position = nextPosition;
        nextPosition = Parent(position);
    }
}

template<typename T>
bool Heap<T>::Remove(const DataType& value)
{
    size_t position = Find(value, 0u);

    if (position == data.Size())
    {
        return false;
    }

    RemoveAt(position);
    return true;
}

template<typename T>
void Heap<T>::Pop()
{
    RemoveAt(0u);
}

template<typename T>
typename Heap<T>::ConstIterator Heap<T>::Find(const DataType& value) const noexcept
{
    return data.Find(value);
}

template<typename T>
typename Heap<T>::Iterator Heap<T>::Find(const DataType& value) noexcept
{
    return data.Find(value);
}

template<typename T>
const DynamicArray<T>& Heap<T>::Array() const
{
    return data;
}

template<typename T>
const typename Heap<T>::DataType& Heap<T>::Max() const
{
    return data[0];
}

template<typename T>
void Heap<T>::Clear()
{
    data.Clear();
}

template<typename T>
size_t Heap<T>::Size() const noexcept
{
    return data.Size();
}

template<typename T>
size_t Heap<T>::Find(const DataType& value, size_t root) const
{
    if (root >= data.Size())
    {
        return data.Size();
    }
    if (data[root] < value)
    {
        return data.Size();
    }
    if (data[root] == value)
    {
        return root;
    }

    size_t leftFind = Find(value, Left(root));
    size_t rightFind = Find(value, Right(root));

    return leftFind != data.Size() ? leftFind : rightFind;
}

template<typename T>
size_t Heap<T>::Left(size_t parent) const noexcept
{
    size_t left = 2u * parent + 1u;
    if (left >= data.Size())
    {
        return data.Size();
    }
    return left;
}

template<typename T>
size_t Heap<T>::Right(size_t parent) const noexcept
{
    size_t right = 2u * parent + 2u;
    if (right >= data.Size())
    {
        return data.Size();
    }
    return right;
}

template<typename T>
size_t Heap<T>::Parent(size_t node) noexcept
{
    return (node - 1) / 2;
}

template<typename T>
void Heap<T>::RemoveAt(size_t node)
{
    if (node >= Size())
    {
        return;
    }
    if (Size() == 1u)
    {
        data.RemoveBack();
        return;
    }

    data[node] = data[Size() - 1];
    data.RemoveBack();

    RestoreDown(node);
}

template<typename T>
void Heap<T>::RestoreDown(size_t node)
{
    size_t current_position = node;

    size_t left = Left(current_position);
    bool isLeft = left != data.Size();

    size_t right = Right(current_position);
    bool isRight = right != data.Size();

    while ((isLeft && data[current_position] < data[left]) || (isRight && data[current_position] < data[right]))
    {
        size_t next_position;
        if (isLeft && isRight)
        {
            next_position = data[left] > data[right] ? left : right;
        }
        else
        {
            next_position = isLeft ? left : right;
        }
        Utils::Swap(data[current_position], data[next_position]);
        current_position = next_position;

        left = Left(current_position);
        isLeft = left != data.Size();

        right = Right(current_position);
        isRight = right != data.Size();
    }
}

template<typename T>
typename Heap<T>::Iterator Heap<T>::begin() noexcept
{
    return data.begin();
}

template<typename T>
typename Heap<T>::Iterator Heap<T>::end() noexcept
{
    return data.end();
}

template<typename T>
typename Heap<T>::ConstIterator Heap<T>::begin() const noexcept
{
    return data.begin();
}

template<typename T>
typename Heap<T>::ConstIterator Heap<T>::end() const noexcept
{
    return data.end();
}

template<typename T>
typename Heap<T>::ConstIterator Heap<T>::cbegin() const noexcept
{
    return data.cbegin();
}

template<typename T>
typename Heap<T>::ConstIterator Heap<T>::cend() const noexcept
{
    return data.cend();
}

template<typename T>
void Heap<T>::ToString(std::string& result, const std::string& prefix, size_t node, bool isRight) const
{
    if (node != data.Size())
    {
        result += prefix;

        result += (isRight ? Utils::VERTICAL_BAR_RIGHT : Utils::HALF_VERTICAL_BAR_RIGHT);
        result += Utils::HORIZONTAL_BAR;

        result += Utils::Parser::NumberToString(data[node]) + "\n";

        ToString(result, prefix + (isRight ? Utils::VERTICAL_BAR : " ") + " ", Right(node), true);
        ToString(result, prefix + (isRight ? Utils::VERTICAL_BAR : " ") + " ", Left(node), false);
    }
}

template<typename T>
std::string Heap<T>::ToString() const
{
    std::string result;
    ToString(result, "", 0, false);
    return result;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Heap<T>& heap)
{
    return os << heap.data;
}

template<typename T>
std::istream& operator>>(std::istream& is, Heap<T>& array)
{
    return is >> array.data;
}