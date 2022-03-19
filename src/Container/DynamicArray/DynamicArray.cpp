#include "Container/DynamicArray/DynamicArray.h"
#include "Utils/Parser.h"

#include <cstring>

DynamicArray::DynamicArray(size_t size) : size(size)
{
    data = new DataType[size];
}

DynamicArray::DynamicArray(std::initializer_list<DataType> initList)
{
    data = new DataType[initList.size()];
    size_t counter = 0u;
    for (const auto& item : initList)
    {
        data[counter] = item;
        counter++;
    }
    size = initList.size();
}

DynamicArray::DynamicArray(const DynamicArray& rhs)
{
    if (rhs.size == 0u)
    {
        return;
    }
    data = new DataType[rhs.size];
    std::memcpy(data, rhs.data, rhs.size * sizeof(DataType));
    size = rhs.size;
}

DynamicArray::DynamicArray(DynamicArray&& rhs) noexcept
{
    if (rhs.size == 0u)
    {
        return;
    }
    data = rhs.data;
    size = rhs.size;

    rhs.data = nullptr;
    rhs.size = 0u;
}

DynamicArray& DynamicArray::operator=(const DynamicArray& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    if (rhs.size != 0u) {
        DataType* newData = new DataType[rhs.size];

        delete[] data;

        data = newData;
        std::memcpy(data, rhs.data, rhs.size * sizeof(DataType));
    }
    size = rhs.size;

    return *this;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& rhs) noexcept
{
    delete[] data;

    data = rhs.data;
    size = rhs.size;

    rhs.data = nullptr;
    rhs.size = 0u;

    return *this;
}

DynamicArray::~DynamicArray()
{
    Clear();
}

DynamicArray::DataType& DynamicArray::operator[](size_t position)
{
    if (position >= size)
    {
        throw std::out_of_range("Index is out of range");
    }
    return data[position];
}

const DynamicArray::DataType& DynamicArray::operator[](size_t position) const
{
    if (position >= size)
    {
        throw std::out_of_range("Index is out of range");
    }
    return data[position];
}

void DynamicArray::PushBack(DataType value)
{
    DataType* newData = new DataType[size + 1];

    std::memcpy(newData, data, size * sizeof(DataType));

    newData[size] = value;

    delete[] data;
    data = newData;

    size++;
}

void DynamicArray::PushFront(DataType value)
{
    DataType* newData = new DataType[size + 1];

    std::memcpy(newData + 1, data, size * sizeof(DataType));
    newData[0] = value;

    delete[] data;
    data = newData;

    size++;
}

DynamicArray::Iterator DynamicArray::Insert(size_t position, DataType value)
{
    if (position > size)
    {
        throw std::out_of_range("Index is out of range");
    }
    if (position == size)
    {
        PushBack(value);
        return {data + size - 1u};
    }
    if (position == 0u)
    {
        PushFront(value);
        return {data};
    }

    DataType* newData = new DataType[size + 1];

    std::memcpy(newData, data, position * sizeof(DataType));
    std::memcpy(newData + position + 1, data + position, (size - position) * sizeof(DataType));
    newData[position] = value;

    delete[] data;
    data = newData;

    size++;
    return {data + position};
}

DynamicArray::Iterator DynamicArray::Insert(ConstIterator iterator, DataType value)
{
    return Insert(iterator - cbegin(), value);
}

bool DynamicArray::Remove(DataType value)
{
    auto positionToRemove = Find(value);

    if (positionToRemove == end())
    {
        return false;
    }

    RemoveAt(positionToRemove);
    return true;
}

void DynamicArray::RemoveBack()
{
    if (size == 0u)
    {
        return;
    }
    if (size == 1u)
    {
        Clear();
        return;
    }
    DataType* newData = new DataType[size - 1];

    std::memcpy(newData, data, (size - 1) * sizeof(DataType));

    delete[] data;
    data = newData;

    size--;
}

void DynamicArray::RemoveFront()
{
    if (size == 0u)
    {
        return;
    }
    if (size == 1u)
    {
        Clear();
        return;
    }
    DataType* newData = new DataType[size - 1];

    std::memcpy(newData, data + 1, (size - 1) * sizeof(DataType));

    delete[] data;
    data = newData;

    size--;
}

void DynamicArray::RemoveAt(size_t positionToRemove)
{
    if (positionToRemove >= size)
    {
        return;
    }
    if (size == 0u)
    {
        return;
    }
    if (size == 1u)
    {
        Clear();
        return;
    }

    DataType* newData = new DataType[size - 1];

    std::memcpy(newData, data, positionToRemove * sizeof(DataType));
    std::memcpy(newData + positionToRemove, data + positionToRemove + 1, (size - positionToRemove - 1) * sizeof(DataType));

    delete[] data;
    data = newData;

    size--;
}

void DynamicArray::RemoveAt(ConstIterator iterator)
{
    RemoveAt(iterator - cbegin());
}

void DynamicArray::Clear()
{
    delete[] data;
    data = nullptr;
    size = 0u;
}

DynamicArray::ConstIterator DynamicArray::Find(DataType value) const noexcept
{
    for (auto it = cbegin(); it != cend(); it++)
    {
        if (value == *it)
        {
            return it;
        }
    }
    return cend();
}

DynamicArray::Iterator DynamicArray::Find(DataType value) noexcept
{
    for (auto it = begin(); it != end(); it++)
    {
        if (value == *it)
        {
            return it;
        }
    }
    return end();
}

size_t DynamicArray::Size() const noexcept
{
    return size;
}

DynamicArray::Iterator DynamicArray::begin() noexcept
{
    return {data};
}

DynamicArray::Iterator DynamicArray::end() noexcept
{
    return {data + size};
}

DynamicArray::ConstIterator DynamicArray::begin() const noexcept
{
    return {data};
}

DynamicArray::ConstIterator DynamicArray::end() const noexcept
{
    return {data + size};
}

DynamicArray::ConstIterator DynamicArray::cbegin() const noexcept
{
    return {data};
}

DynamicArray::ConstIterator DynamicArray::cend() const noexcept
{
    return {data + size};
}

void DynamicArray::Resize(size_t newSize)
{
    DataType* newData = new DataType[newSize];

    std::memcpy(newData, data, size);
    delete[] data;
    data = newData;
    size = newSize;
}

std::string DynamicArray::ToString() const
{
    std::string result = "[";
    for (size_t i = 0u; i < size; i++)
    {
        result += Utils::Parser::number_to_string(data[i]);
        if (i != size - 1u)
        {
            result += ", ";
        }
    }
    return result + "]";
}

std::ostream& operator<<(std::ostream& os, const DynamicArray& array)
{
    if (!os.good())
    {
        return os;
    }
    os << array.Size() << "\n";
    for (size_t i = 0u; i < array.Size() && os.good(); i++)
    {
        os << array[i] << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, DynamicArray& array)
{
    if (!is.good())
    {
        return is;
    }
    size_t size;
    is >> size;
    array.Resize(size);
    for (size_t i = 0u; i < size && is.good(); i++)
    {
        is >> array[i];
    }

    return is;
}

std::string DynamicArray::ClassName()
{
    return "DynamicArray";
}

DynamicArrayConstIterator::DynamicArrayConstIterator(DynamicArray::DataType* ptr) noexcept
    : ptr(ptr)
{}

DynamicArrayConstIterator::reference DynamicArrayConstIterator::operator*() const noexcept
{
    return *ptr;
}

DynamicArrayConstIterator::pointer DynamicArrayConstIterator::operator->() const noexcept
{
    return ptr;
}

DynamicArrayConstIterator& DynamicArrayConstIterator::operator++() noexcept
{
    ptr++;
    return *this;
}

DynamicArrayConstIterator DynamicArrayConstIterator::operator++(int) noexcept
{
    DynamicArrayConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

DynamicArrayConstIterator& DynamicArrayConstIterator::operator--() noexcept
{
    ptr--;
    return *this;
}

DynamicArrayConstIterator DynamicArrayConstIterator::operator--(int) noexcept
{
    DynamicArrayConstIterator tmp = *this;
    --(*this);
    return tmp;
}

DynamicArrayConstIterator& DynamicArrayConstIterator::operator+=(const difference_type offset) noexcept
{
    ptr += offset;
    return *this;
}

DynamicArrayConstIterator DynamicArrayConstIterator::operator+(const difference_type offset) const noexcept
{
    DynamicArrayConstIterator tmp = *this;
    tmp += offset;
    return tmp;
}

DynamicArrayConstIterator& DynamicArrayConstIterator::operator-=(const difference_type offset) noexcept
{
    return *this += -offset;
}

DynamicArrayConstIterator DynamicArrayConstIterator::operator-(const difference_type offset) const noexcept
{
    DynamicArrayConstIterator tmp = *this;
    tmp -= offset;
    return tmp;
}

DynamicArrayConstIterator::difference_type DynamicArrayConstIterator::operator-(const DynamicArrayConstIterator& rhs) const noexcept
{
    return ptr - rhs.ptr;
}

DynamicArrayConstIterator::reference DynamicArrayConstIterator::operator[](const difference_type offset) const noexcept
{
    return *(*this + offset);
}

bool DynamicArrayConstIterator::operator==(const DynamicArrayConstIterator& rhs) const noexcept
{
    return ptr == rhs.ptr;
}

bool DynamicArrayConstIterator::operator!=(const DynamicArrayConstIterator& rhs) const noexcept
{
    return !(*this == rhs);
}

bool DynamicArrayConstIterator::operator<(const DynamicArrayConstIterator& rhs) const noexcept
{
    return ptr < rhs.ptr;
}

bool DynamicArrayConstIterator::operator>(const DynamicArrayConstIterator& rhs) const noexcept
{
    return rhs < *this;
}

bool DynamicArrayConstIterator::operator<=(const DynamicArrayConstIterator& rhs) const noexcept
{
    return !(rhs < *this);
}
bool DynamicArrayConstIterator::operator>=(const DynamicArrayConstIterator& rhs) const noexcept
{
    return !(*this < rhs);
}

DynamicArrayConstIterator operator+(DynamicArrayConstIterator::difference_type offset, DynamicArrayConstIterator iterator) noexcept
{
    iterator += offset;
    return iterator;
}


DynamicArrayIterator::reference DynamicArrayIterator::operator*() const noexcept
{
    return const_cast<reference>(DynamicArrayConstIterator::operator*());
}

DynamicArrayIterator::pointer DynamicArrayIterator::operator->() const noexcept
{
    return ptr;
}

DynamicArrayIterator& DynamicArrayIterator::operator++() noexcept
{
    DynamicArrayConstIterator::operator++();
    return *this;
}

DynamicArrayIterator DynamicArrayIterator::operator++(int) noexcept
{
    DynamicArrayIterator tmp = *this;
    DynamicArrayConstIterator::operator++();
    return tmp;
}

DynamicArrayIterator& DynamicArrayIterator::operator--() noexcept
{
    DynamicArrayConstIterator::operator--();
    return *this;
}

DynamicArrayIterator DynamicArrayIterator::operator--(int) noexcept
{
    DynamicArrayIterator tmp = *this;
    DynamicArrayConstIterator::operator--();
    return tmp;
}

DynamicArrayIterator& DynamicArrayIterator::operator+=(const difference_type offset) noexcept
{
    DynamicArrayConstIterator::operator+=(offset);
    return *this;
}

DynamicArrayIterator DynamicArrayIterator::operator+(const difference_type offset) const noexcept
{
    DynamicArrayIterator tmp = *this;
    tmp += offset;
    return tmp;
}

DynamicArrayIterator& DynamicArrayIterator::operator-=(const difference_type offset) noexcept
{
    DynamicArrayConstIterator::operator-=(offset);
    return *this;
}

DynamicArrayIterator DynamicArrayIterator::operator-(const difference_type offset) const noexcept
{
    DynamicArrayIterator tmp = *this;
    tmp -= offset;
    return tmp;
}

DynamicArrayIterator::reference DynamicArrayIterator::operator[](const difference_type offset) const noexcept
{
    return const_cast<reference>(DynamicArrayConstIterator::operator[](offset));
}

DynamicArrayIterator::difference_type DynamicArrayIterator::operator-(const DynamicArrayConstIterator& rhs) const noexcept
{
    return DynamicArrayConstIterator::operator-(rhs);
}

DynamicArrayIterator operator+(DynamicArrayIterator::difference_type offset, DynamicArrayIterator iterator) noexcept
{
    iterator += offset;
    return iterator;
}