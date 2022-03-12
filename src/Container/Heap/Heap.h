#pragma once

#include "Container/DynamicArray/DynamicArray.h"

class Heap
{
public:
    using DataType = DynamicArray::DataType;

    Heap() = default;
    Heap(std::initializer_list<DataType> initList);

    void Insert(const DataType& value);
    bool Remove(const DataType& value);
    void Pop();
    void Clear();

    [[nodiscard]] const DataType* Find(const DataType& value) const;

    [[nodiscard]] DataType& Max();
    [[nodiscard]] const DataType& Max() const;

    [[nodiscard]] const DynamicArray& Array() const;
    [[nodiscard]] size_t Size() const;

private:
    void RemoveAt(size_t node);
    void RestoreDown(size_t node);

    [[nodiscard]] size_t Find(const DataType& value, size_t root) const;

    [[nodiscard]] size_t Left(size_t parent) const;
    [[nodiscard]] size_t Right(size_t parent) const;
    [[nodiscard]] static size_t Parent(size_t node) ;

    DynamicArray data;
};