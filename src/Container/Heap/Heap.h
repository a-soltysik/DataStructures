#pragma once

#include "Container/DynamicArray/DynamicArray.h"

class Heap
{
public:
    using DataType = DynamicArray::DataType;

    Heap() = default;
    Heap(std::initializer_list<DataType> initList);
    explicit Heap(const DynamicArray& array);

    void Insert(const DataType& value);
    bool Remove(const DataType& value);
    void Pop();
    void Clear();

    [[nodiscard]] const DataType* Find(const DataType& value) const;

    [[nodiscard]] DataType& Max();
    [[nodiscard]] const DataType& Max() const;

    [[nodiscard]] const DynamicArray& Array() const;
    [[nodiscard]] size_t Size() const;

    [[nodiscard]] std::string ToString() const;
    friend std::ostream& operator<<(std::ostream& os, const Heap& heap);
    friend std::istream& operator>>(std::istream& is, Heap& heap);

private:
    void RemoveAt(size_t node);
    void RestoreDown(size_t node);

    void ToString(std::string& result, const std::string& prefix, size_t node, bool isLeft) const;

    [[nodiscard]] size_t Find(const DataType& value, size_t root) const;

    [[nodiscard]] size_t Left(size_t parent) const;
    [[nodiscard]] size_t Right(size_t parent) const;
    [[nodiscard]] static size_t Parent(size_t node) ;

    DynamicArray data;
};