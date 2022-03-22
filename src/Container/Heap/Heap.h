#pragma once

#include "Container/DynamicArray/DynamicArray.h"

class Heap
{
public:
    using DataType = DynamicArray::DataType;
    using Iterator = DynamicArrayIterator;
    using ConstIterator = DynamicArrayConstIterator;

    [[nodiscard]] static constexpr const char* ClassName() { return "Heap"; }

    Heap() = default;
    Heap(std::initializer_list<DataType> initList);
    explicit Heap(const DynamicArray& array);

    void Assign(const DynamicArray& array);
    void Insert(DataType value);
    bool Remove(DataType value);
    void Pop();
    void Clear();

    [[nodiscard]] Iterator Find(DataType value) noexcept;
    [[nodiscard]] ConstIterator Find(DataType value) const noexcept;

    [[nodiscard]] DataType& Max();
    [[nodiscard]] const DataType& Max() const;

    [[nodiscard]] const DynamicArray& Array() const;
    [[nodiscard]] size_t Size() const noexcept;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;
    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;
    [[nodiscard]] ConstIterator cbegin() const noexcept;
    [[nodiscard]] ConstIterator cend() const noexcept;

    [[nodiscard]] std::string ToString() const;
    friend std::ostream& operator<<(std::ostream& os, const Heap& heap);
    friend std::istream& operator>>(std::istream& is, Heap& heap);

private:
    [[nodiscard]] static size_t Parent(size_t node) noexcept;

    void RemoveAt(size_t node);
    void RestoreDown(size_t node);

    [[nodiscard]] size_t Find(const DataType& value, size_t root) const;

    [[nodiscard]] size_t Left(size_t parent) const noexcept;
    [[nodiscard]] size_t Right(size_t parent) const noexcept;

    void ToString(std::string& result, const std::string& prefix, size_t node, bool isRight) const;

    DynamicArray data;
};