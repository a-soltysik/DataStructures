#pragma once

#include <istream>
#include <optional>
#include <iterator>

class DynamicArray
{
public:
    using DataType = int32_t;
    struct Iterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = DataType;
        using pointer           = DataType*;
        using reference         = DataType&;

        Iterator() = default;

        Iterator(pointer ptr) noexcept : ptr(ptr) {}

        [[nodiscard]] reference operator*() const noexcept { return *ptr; }

        [[nodiscard]] pointer operator->() const noexcept { return ptr; }

        Iterator& operator++() noexcept { ptr++; return *this; }
        Iterator operator++(int) noexcept { Iterator tmp = *this; ++(*this); return tmp; }
        Iterator& operator--() noexcept { ptr--; return *this; }
        Iterator operator--(int) noexcept { Iterator tmp = *this; --(*this); return tmp; }

        Iterator& operator+=(const difference_type offset) noexcept { ptr += offset; return *this; }
        [[nodiscard]] Iterator operator+(const difference_type offset) const noexcept { 
            Iterator tmp = *this;
            tmp += offset;
            return tmp;
        }

        Iterator& operator-=(const difference_type offset) noexcept { return *this += -offset; }
        [[nodiscard]] Iterator operator-(const difference_type offset) const noexcept {
            Iterator tmp = *this;
            tmp -= offset;
            return tmp;
        }

        [[nodiscard]] difference_type operator-(const Iterator rhs) const noexcept { return ptr - rhs.ptr; }

        [[nodiscard]] reference operator[](const difference_type offset) const noexcept { return *(*this + offset); }

        [[nodiscard]] bool operator==(const Iterator& rhs) const noexcept { return ptr == rhs.ptr; }
        [[nodiscard]] bool operator!=(const Iterator& rhs) const noexcept { return !(*this == rhs); }
        [[nodiscard]] bool operator<(const Iterator& rhs) const noexcept { return ptr < rhs.ptr; }
        [[nodiscard]] bool operator>(const Iterator& rhs) const noexcept { return rhs < *this; }
        [[nodiscard]] bool operator<=(const Iterator& rhs) const noexcept { return !(rhs < *this); }
        [[nodiscard]] bool operator>=(const Iterator& rhs) const noexcept { return !(*this < rhs); }
    private:
        pointer ptr;
    };

    constexpr static size_t INVALID_INDEX = SIZE_MAX;

    DynamicArray() = default;
    DynamicArray(size_t size);
    DynamicArray(const DynamicArray& rhs);
    DynamicArray(DynamicArray&& rhs) noexcept;
    DynamicArray& operator=(const DynamicArray& rhs);
    DynamicArray& operator=(DynamicArray&& rhs) noexcept;
    ~DynamicArray();

    [[nodiscard]]
    DataType& operator[](size_t position);

    [[nodiscard]]
    const DataType& operator[](size_t position) const;

    void PushBack(DataType value);
    void PushFront(DataType value);
    void Insert(size_t position, DataType value);

    bool Remove(DataType value);
    bool RemoveAll(DataType value);

    void RemoveBack();
    void RemoveFront();
    void RemoveAt(size_t positionToRemove);

    void Clear();

    [[nodiscard]] size_t Find(DataType value, size_t start = 0u) const noexcept;

    [[nodiscard]] size_t Size() const noexcept;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;
    


    static bool Serialize(std::ostream& os, const DynamicArray& array);
    static std::optional<DynamicArray> Deserialize(std::istream& is);

private:
    DataType* data = nullptr;
    size_t size = 0u;
};

std::ostream& operator<<(std::ostream& os, const DynamicArray& array);


