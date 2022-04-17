﻿#pragma once

#include <istream>

struct DynamicArrayIterator;
struct DynamicArrayConstIterator;

class DynamicArray
{
public:
    using DataType = int32_t;
    using Iterator = DynamicArrayIterator;
    using ConstIterator = DynamicArrayConstIterator;

    [[nodiscard]] static constexpr const char* ClassName() { return "DynamicArray"; }

    DynamicArray() = default;
    explicit DynamicArray(size_t size);
    DynamicArray(std::initializer_list<DataType> initList);
    DynamicArray(const DynamicArray& rhs);
    DynamicArray(DynamicArray&& rhs) noexcept;
    DynamicArray& operator=(const DynamicArray& rhs);
    DynamicArray& operator=(DynamicArray&& rhs) noexcept;
    ~DynamicArray();

    [[nodiscard]] DataType& operator[](size_t position);
    [[nodiscard]] const DataType& operator[](size_t position) const;

    void PushBack(DataType value);
    void PushFront(DataType value);
    Iterator Insert(size_t position, DataType value);
    Iterator Insert(ConstIterator iterator, DataType value);

    bool Remove(DataType value);
    void RemoveBack();
    void RemoveFront();
    void RemoveAt(size_t position);
    void RemoveAt(ConstIterator iterator);

    void Clear();
    void Resize(size_t newSize);

    [[nodiscard]] Iterator Find(DataType value) noexcept;
    [[nodiscard]] ConstIterator Find(DataType value) const noexcept;

    [[nodiscard]] size_t Size() const noexcept;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;
    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;
    [[nodiscard]] ConstIterator cbegin() const noexcept;
    [[nodiscard]] ConstIterator cend() const noexcept;

    [[nodiscard]] std::string ToString() const;
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& array);
    friend std::istream& operator>>(std::istream& is, DynamicArray& array);

private:
    [[nodiscard]] DataType* BasicFind(DataType value) const noexcept;

    DataType* data = nullptr;
    size_t size = 0u;
};

struct DynamicArrayConstIterator
{
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = DynamicArray::DataType;
    using pointer = const DynamicArray::DataType*;
    using reference = const DynamicArray::DataType&;

    DynamicArrayConstIterator() = default;
    DynamicArrayConstIterator(DynamicArray::DataType* ptr) noexcept;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    DynamicArrayConstIterator& operator++() noexcept;
    DynamicArrayConstIterator operator++(int) noexcept;
    DynamicArrayConstIterator& operator--() noexcept;
    DynamicArrayConstIterator operator--(int) noexcept;

    DynamicArrayConstIterator& operator+=(difference_type offset) noexcept;
    [[nodiscard]] DynamicArrayConstIterator operator+(difference_type offset) const noexcept;
    DynamicArrayConstIterator& operator-=(difference_type offset) noexcept;
    [[nodiscard]] DynamicArrayConstIterator operator-(difference_type offset) const noexcept;

    [[nodiscard]] difference_type operator-(const DynamicArrayConstIterator& rhs) const noexcept;

    [[nodiscard]] reference operator[](difference_type offset) const noexcept;

    [[nodiscard]] bool operator==(const DynamicArrayConstIterator& rhs) const noexcept;
    [[nodiscard]] bool operator!=(const DynamicArrayConstIterator& rhs) const noexcept;
    [[nodiscard]] bool operator<(const DynamicArrayConstIterator& rhs) const noexcept;
    [[nodiscard]] bool operator>(const DynamicArrayConstIterator& rhs) const noexcept;
    [[nodiscard]] bool operator<=(const DynamicArrayConstIterator& rhs) const noexcept;
    [[nodiscard]] bool operator>=(const DynamicArrayConstIterator& rhs) const noexcept;

protected:
    DynamicArray::DataType* ptr;
};

[[nodiscard]] DynamicArrayConstIterator operator+(DynamicArrayConstIterator::difference_type offset,
                                                  DynamicArrayConstIterator iterator) noexcept;

struct DynamicArrayIterator : public DynamicArrayConstIterator
{
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = DynamicArray::DataType;
    using pointer = value_type*;
    using reference = value_type&;

    using DynamicArrayConstIterator::DynamicArrayConstIterator;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    DynamicArrayIterator& operator++() noexcept;
    DynamicArrayIterator operator++(int) noexcept;
    DynamicArrayIterator& operator--() noexcept;
    DynamicArrayIterator operator--(int) noexcept;

    DynamicArrayIterator& operator+=(difference_type offset) noexcept;
    [[nodiscard]] DynamicArrayIterator operator+(difference_type offset) const noexcept;
    DynamicArrayIterator& operator-=(difference_type offset) noexcept;
    [[nodiscard]] DynamicArrayIterator operator-(difference_type offset) const noexcept;

    [[nodiscard]] difference_type operator-(const DynamicArrayConstIterator& rhs) const noexcept;

    [[nodiscard]] reference operator[](const difference_type offset) const noexcept;
};

[[nodiscard]] DynamicArrayIterator operator+(DynamicArrayIterator::difference_type offset,
                                             DynamicArrayIterator iterator) noexcept;