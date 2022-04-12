#include "Containers/Heap.h"
#include "Utils/Parser.h"
#include "Utils/Utils.h"

Heap::Heap(std::initializer_list<DataType> initList)
{
    for (const auto& element: initList)
    {
        Insert(element);
    }
}

Heap::Heap(const DynamicArray& array)
{
    Assign(array);
}

void Heap::Assign(const DynamicArray& array)
{
    data = array;
    for (size_t i = array.Size() / 2 - 1; i-- > 0;)
    {
        RestoreDown(i);
    }
}

void Heap::Insert(DataType value)
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

bool Heap::Remove(DataType value)
{
    size_t position = Find(value, 0u);

    if (position == data.Size())
    {
        return false;
    }

    RemoveAt(position);
    return true;
}

void Heap::Pop()
{
    RemoveAt(0u);
}

Heap::ConstIterator Heap::Find(DataType value) const noexcept
{
    return data.Find(value);
}

Heap::Iterator Heap::Find(DataType value) noexcept
{
    return data.Find(value);
}

const DynamicArray& Heap::Array() const
{
    return data;
}

Heap::DataType& Heap::Max()
{
    return data[0];
}

const Heap::DataType& Heap::Max() const
{
    return data[0];
}

void Heap::Clear()
{
    data.Clear();
}

size_t Heap::Size() const noexcept
{
    return data.Size();
}

size_t Heap::Find(const DataType& value, size_t root) const
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

size_t Heap::Left(size_t parent) const noexcept
{
    size_t left = 2u * parent + 1u;
    if (left >= data.Size())
    {
        return data.Size();
    }
    return left;
}

size_t Heap::Right(size_t parent) const noexcept
{
    size_t right = 2u * parent + 2u;
    if (right >= data.Size())
    {
        return data.Size();
    }
    return right;
}

size_t Heap::Parent(size_t node) noexcept
{
    return (node - 1) / 2;
}

void Heap::RemoveAt(size_t node)
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

void Heap::RestoreDown(size_t node)
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

Heap::Iterator Heap::begin() noexcept
{
    return data.begin();
}

Heap::Iterator Heap::end() noexcept
{
    return data.end();
}

Heap::ConstIterator Heap::begin() const noexcept
{
    return data.begin();
}

Heap::ConstIterator Heap::end() const noexcept
{
    return data.end();
}

Heap::ConstIterator Heap::cbegin() const noexcept
{
    return data.cbegin();
}

Heap::ConstIterator Heap::cend() const noexcept
{
    return data.cend();
}

void Heap::ToString(std::string& result, const std::string& prefix, size_t node, bool isRight) const
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

std::string Heap::ToString() const
{
    std::string result;
    ToString(result, "", 0, false);
    return result;
}

std::ostream& operator<<(std::ostream& os, const Heap& heap)
{
    return os << heap.data;
}

std::istream& operator>>(std::istream& is, Heap& array)
{
    return is >> array.data;
}