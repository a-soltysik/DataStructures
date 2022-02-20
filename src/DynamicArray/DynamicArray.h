#pragma once
#include <cstdint>

class DynamicArray
{
public:
    using DataType = int32_t;
    static constexpr size_t INVALID_INDEX = SIZE_MAX;

    DynamicArray() = default;
    DynamicArray(const DynamicArray& rhs);
    DynamicArray(DynamicArray&& rhs);
    DynamicArray& operator=(const DynamicArray& rhs);
    DynamicArray& operator=(DynamicArray&& rhs);
    ~DynamicArray();

    DataType& operator[](size_t position);
    const DataType& operator[](size_t position) const;

    void PushBack(DataType value);
    void PushFront(DataType value);
    void Insert(size_t position, DataType value);

    bool Remove(DataType value);
    bool RemoveAll(DataType value);

    void RemoveBack();
    void RemoveFront();
    void RemoveAt(size_t positionToRemove);

    size_t Find(DataType value, size_t start = 0u) const noexcept;

    size_t Size() const noexcept;

private:
    DataType* data = nullptr;
    size_t size = 0u;
};
