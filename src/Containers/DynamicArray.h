#pragma once

template<typename T>
struct DynamicArrayIterator;

template<typename T>
struct DynamicArrayConstIterator;

template<typename T>
class DynamicArray
{
public:
    using DataType = T;
    using Iterator = DynamicArrayIterator<T>;
    using ConstIterator = DynamicArrayConstIterator<T>;

    [[nodiscard]] static constexpr const char* ClassName() { return "DynamicArray"; }

    DynamicArray() = default;
    explicit DynamicArray(size_t size);
    DynamicArray(std::initializer_list<DataType> initList);
    DynamicArray(size_t count, const DataType& value);
    DynamicArray(const DynamicArray& rhs);
    DynamicArray(DynamicArray&& rhs) noexcept;
    DynamicArray& operator=(const DynamicArray& rhs);
    DynamicArray& operator=(DynamicArray&& rhs) noexcept;
    ~DynamicArray();

    [[nodiscard]] DataType& operator[](size_t position);
    [[nodiscard]] const DataType& operator[](size_t position) const;

    void PushBack(const DataType& value);
    void PushFront(const DataType& value);
    Iterator Insert(size_t position, const DataType& value);
    Iterator Insert(ConstIterator iterator, const DataType& value);

    bool Remove(const DataType& value);
    void RemoveBack();
    void RemoveFront();
    void RemoveAt(size_t position);
    void RemoveAt(ConstIterator iterator);

    void Clear();
    void Resize(size_t newSize);

    [[nodiscard]] Iterator Find(const DataType& value) noexcept;
    [[nodiscard]] ConstIterator Find(const DataType& value) const noexcept;

    [[nodiscard]] size_t Size() const noexcept;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;
    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;
    [[nodiscard]] ConstIterator cbegin() const noexcept;
    [[nodiscard]] ConstIterator cend() const noexcept;

    [[nodiscard]] std::string ToString() const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& array);

    template<typename U>
    friend std::istream& operator>>(std::istream& is, DynamicArray<U>& array);

private:
    [[nodiscard]] DataType* BasicFind(const DataType& value) const noexcept;

    DataType* data = nullptr;
    size_t size = 0u;
};

template<typename T>
struct DynamicArrayConstIterator
{
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = typename DynamicArray<T>::DataType;
    using pointer = const value_type*;
    using reference = const value_type&;

    DynamicArrayConstIterator() = default;
    DynamicArrayConstIterator(typename DynamicArray<T>::DataType* ptr) noexcept;

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
    typename DynamicArray<T>::DataType* ptr;
};

template<typename T>
[[nodiscard]] DynamicArrayConstIterator<T> operator+(typename DynamicArrayConstIterator<T>::difference_type offset,
                                                     DynamicArrayConstIterator<T> iterator) noexcept;

template<typename T>
struct DynamicArrayIterator : public DynamicArrayConstIterator<T>
{
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = typename DynamicArray<T>::DataType;
    using pointer = value_type*;
    using reference = value_type&;

    using DynamicArrayConstIterator<T>::DynamicArrayConstIterator;

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

    [[nodiscard]] difference_type operator-(const DynamicArrayConstIterator<T>& rhs) const noexcept;

    [[nodiscard]] reference operator[](const difference_type offset) const noexcept;
};

template<typename T>
[[nodiscard]] DynamicArrayIterator<T> operator+(typename DynamicArrayIterator<T>::difference_type offset,
                                                DynamicArrayIterator<T> iterator) noexcept;

template<typename T>
DynamicArray<T>::DynamicArray(size_t size) : size(size)
{
    data = new DataType[size];
}

template<typename T>
DynamicArray<T>::DynamicArray(std::initializer_list<DataType> initList)
{
    data = new DataType[initList.size()];
    size_t counter = 0u;
    for (const auto& item: initList)
    {
        data[counter] = item;
        counter++;
    }
    size = initList.size();
}

template<typename T>
DynamicArray<T>::DynamicArray(size_t count, const DataType& value)
{
    data = new DataType[count];

    for (size_t i = 0; i < count; i++)
    {
        data[i] = value;
    }

    size = count;
}


template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& rhs)
{
    if (rhs.size == 0u)
    {
        return;
    }
    data = new DataType[rhs.size];
    std::copy(rhs.data, rhs.data + rhs.size, data);
    size = rhs.size;
}

template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& rhs) noexcept
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

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    if (rhs.size != 0u)
    {
        DataType* newData = new DataType[rhs.size];

        delete[] data;

        data = newData;
        std::copy(rhs.data, rhs.data + rhs.size, data);
    }
    size = rhs.size;

    return *this;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& rhs) noexcept
{
    delete[] data;

    data = rhs.data;
    size = rhs.size;

    rhs.data = nullptr;
    rhs.size = 0u;

    return *this;
}

template<typename T>
DynamicArray<T>::~DynamicArray()
{
    Clear();
}

template<typename T>
typename DynamicArray<T>::DataType& DynamicArray<T>::operator[](size_t position)
{
    if (position >= size)
    {
        throw std::out_of_range("Index is out of range");
    }
    return data[position];
}

template<typename T>
const typename DynamicArray<T>::DataType& DynamicArray<T>::operator[](size_t position) const
{
    if (position >= size)
    {
        throw std::out_of_range("Index is out of range");
    }
    return data[position];
}

template<typename T>
void DynamicArray<T>::PushBack(const DataType& value)
{
    DataType* newData = new DataType[size + 1u];

    std::copy(data, data + size, newData);

    newData[size] = value;

    delete[] data;
    data = newData;

    size++;
}

template<typename T>
void DynamicArray<T>::PushFront(const DataType& value)
{
    DataType* newData = new DataType[size + 1u];

    std::copy(data, data + size, newData + 1u);
    newData[0] = value;

    delete[] data;
    data = newData;

    size++;
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::Insert(size_t position, const DataType& value)
{
    if (position > size)
    {
        throw std::out_of_range("Index is out of range");
    }
    if (position == size)
    {
        PushBack(value);
        return {data + size - 1};
    }
    if (position == 0u)
    {
        PushFront(value);
        return {data};
    }

    DataType* newData = new DataType[size + 1u];

    std::copy(data, data + position, newData);
    std::copy(data + position, data + size, newData + position + 1u);
    newData[position] = value;

    delete[] data;
    data = newData;

    size++;
    return {data + position};
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::Insert(ConstIterator iterator, const DataType& value)
{
    return Insert(iterator - cbegin(), value);
}

template<typename T>
bool DynamicArray<T>::Remove(const DataType& value)
{
    auto positionToRemove = Find(value);

    if (positionToRemove == end())
    {
        return false;
    }

    RemoveAt(positionToRemove);
    return true;
}

template<typename T>
void DynamicArray<T>::RemoveBack()
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

    std::copy(data, data + size - 1, newData);

    delete[] data;
    data = newData;

    size--;
}

template<typename T>
void DynamicArray<T>::RemoveFront()
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

    std::copy(data + 1, data + size, newData);

    delete[] data;
    data = newData;

    size--;
}

template<typename T>
void DynamicArray<T>::RemoveAt(size_t position)
{
    if (position >= size)
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

    std::copy(data, data + position, newData);
    std::copy(data + position + 1, data + size, newData + position);

    delete[] data;
    data = newData;

    size--;
}

template<typename T>
void DynamicArray<T>::RemoveAt(ConstIterator iterator)
{
    RemoveAt(iterator - cbegin());
}

template<typename T>
void DynamicArray<T>::Clear()
{
    delete[] data;
    data = nullptr;
    size = 0u;
}

template<typename T>
typename DynamicArray<T>::ConstIterator DynamicArray<T>::Find(const DataType& value) const noexcept
{
    return BasicFind(value);
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::Find(const DataType& value) noexcept
{
    return BasicFind(value);
}

template<typename T>
size_t DynamicArray<T>::Size() const noexcept
{
    return size;
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::begin() noexcept
{
    return {data};
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::end() noexcept
{
    return {data + size};
}

template<typename T>
typename DynamicArray<T>::ConstIterator DynamicArray<T>::begin() const noexcept
{
    return {data};
}

template<typename T>
typename DynamicArray<T>::ConstIterator DynamicArray<T>::end() const noexcept
{
    return {data + size};
}

template<typename T>
typename DynamicArray<T>::ConstIterator DynamicArray<T>::cbegin() const noexcept
{
    return {data};
}

template<typename T>
typename DynamicArray<T>::ConstIterator DynamicArray<T>::cend() const noexcept
{
    return {data + size};
}

template<typename T>
void DynamicArray<T>::Resize(size_t newSize)
{
    DataType* newData = new DataType[newSize];

    std::copy(data, data + size, newData);
    delete[] data;
    data = newData;
    size = newSize;
}

template<typename T>
std::string DynamicArray<T>::ToString() const
{
    std::string result = "[";
    for (size_t i = 0u; i < size; i++)
    {
        result += Utils::Parser::NumberToString(data[i]);
        if (i != size - 1)
        {
            result += ", ";
        }
    }
    return result + "]";
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& array)
{
    if (!os.fail())
    {
        return os;
    }
    os << array.Size() << "\n";
    for (size_t i = 0u; i < array.Size() && !os.fail(); i++)
    {
        os << array[i] << " ";
    }
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, DynamicArray<T>& array)
{
    if (is.fail())
    {
        return is;
    }
    size_t size;
    is >> size;
    array.Resize(size);
    for (size_t i = 0u; i < size && !is.fail(); i++)
    {
        is >> array[i];
    }

    return is;
}

template<typename T>
typename DynamicArray<T>::DataType* DynamicArray<T>::BasicFind(const DataType& value) const noexcept
{
    DataType* it = data;
    DataType* last = data + size;

    for (size_t i = size / 4; i > 0; i--)
    {
        if (*it == value)
        {
            return it;
        }
        ++it;

        if (*it == value)
        {
            return it;
        }
        ++it;

        if (*it == value)
        {
            return it;
        }
        ++it;

        if (*it == value)
        {
            return it;
        }
        ++it;
    }

    switch (last - it)
    {
    case 3:
        if (*it == value)
        {
            return it;
        }
        ++it;
        [[fallthrough]];
    case 2:
        if (*it == value)
        {
            return it;
        }
        ++it;
        [[fallthrough]];
    case 1:
        if (*it == value)
        {
            return it;
        }
        ++it;
        [[fallthrough]];
    case 0:
        [[fallthrough]];
    default:
        return it;
    }
}

template<typename T>
DynamicArrayConstIterator<T>::DynamicArrayConstIterator(typename DynamicArray<T>::DataType* ptr) noexcept
    : ptr(ptr) { }

template<typename T>
typename DynamicArrayConstIterator<T>::reference DynamicArrayConstIterator<T>::operator*() const noexcept
{
    return *ptr;
}

template<typename T>
typename DynamicArrayConstIterator<T>::pointer DynamicArrayConstIterator<T>::operator->() const noexcept
{
    return ptr;
}

template<typename T>
DynamicArrayConstIterator<T>& DynamicArrayConstIterator<T>::operator++() noexcept
{
    ptr++;
    return *this;
}

template<typename T>
DynamicArrayConstIterator<T> DynamicArrayConstIterator<T>::operator++(int) noexcept
{
    DynamicArrayConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

template<typename T>
DynamicArrayConstIterator<T>& DynamicArrayConstIterator<T>::operator--() noexcept
{
    ptr--;
    return *this;
}

template<typename T>
DynamicArrayConstIterator<T> DynamicArrayConstIterator<T>::operator--(int) noexcept
{
    DynamicArrayConstIterator tmp = *this;
    --(*this);
    return tmp;
}

template<typename T>
DynamicArrayConstIterator<T>& DynamicArrayConstIterator<T>::operator+=(const difference_type offset) noexcept
{
    ptr += offset;
    return *this;
}

template<typename T>
DynamicArrayConstIterator<T> DynamicArrayConstIterator<T>::operator+(const difference_type offset) const noexcept
{
    DynamicArrayConstIterator tmp = *this;
    tmp += offset;
    return tmp;
}

template<typename T>
DynamicArrayConstIterator<T>& DynamicArrayConstIterator<T>::operator-=(const difference_type offset) noexcept
{
    return *this += -offset;
}

template<typename T>
DynamicArrayConstIterator<T> DynamicArrayConstIterator<T>::operator-(const difference_type offset) const noexcept
{
    DynamicArrayConstIterator tmp = *this;
    tmp -= offset;
    return tmp;
}

template<typename T>
typename DynamicArrayConstIterator<T>::difference_type
DynamicArrayConstIterator<T>::operator-(const DynamicArrayConstIterator& rhs) const noexcept
{
    return ptr - rhs.ptr;
}

template<typename T>
typename DynamicArrayConstIterator<T>::reference
DynamicArrayConstIterator<T>::operator[](const difference_type offset) const noexcept
{
    return *(*this + offset);
}

template<typename T>
bool DynamicArrayConstIterator<T>::operator==(const DynamicArrayConstIterator& rhs) const noexcept
{
    return ptr == rhs.ptr;
}

template<typename T>
bool DynamicArrayConstIterator<T>::operator!=(const DynamicArrayConstIterator& rhs) const noexcept
{
    return !(*this == rhs);
}

template<typename T>
bool DynamicArrayConstIterator<T>::operator<(const DynamicArrayConstIterator& rhs) const noexcept
{
    return ptr < rhs.ptr;
}

template<typename T>
bool DynamicArrayConstIterator<T>::operator>(const DynamicArrayConstIterator& rhs) const noexcept
{
    return rhs < *this;
}

template<typename T>
bool DynamicArrayConstIterator<T>::operator<=(const DynamicArrayConstIterator& rhs) const noexcept
{
    return !(rhs < *this);
}

template<typename T>
bool DynamicArrayConstIterator<T>::operator>=(const DynamicArrayConstIterator& rhs) const noexcept
{
    return !(*this < rhs);
}

template<typename T>
DynamicArrayConstIterator<T>
operator+(typename DynamicArrayConstIterator<T>::difference_type offset, DynamicArrayConstIterator<T> iterator) noexcept
{
    iterator += offset;
    return iterator;
}

template<typename T>
typename DynamicArrayIterator<T>::reference DynamicArrayIterator<T>::operator*() const noexcept
{
    return const_cast<reference>(DynamicArrayConstIterator<T>::operator*());
}

template<typename T>
typename DynamicArrayIterator<T>::pointer DynamicArrayIterator<T>::operator->() const noexcept
{
    return this->ptr;
}

template<typename T>
DynamicArrayIterator<T>& DynamicArrayIterator<T>::operator++() noexcept
{
    DynamicArrayConstIterator<T>::operator++();
    return *this;
}

template<typename T>
DynamicArrayIterator<T> DynamicArrayIterator<T>::operator++(int) noexcept
{
    DynamicArrayIterator tmp = *this;
    DynamicArrayConstIterator<T>::operator++();
    return tmp;
}

template<typename T>
DynamicArrayIterator<T>& DynamicArrayIterator<T>::operator--() noexcept
{
    DynamicArrayConstIterator<T>::operator--();
    return *this;
}

template<typename T>
DynamicArrayIterator<T> DynamicArrayIterator<T>::operator--(int) noexcept
{
    DynamicArrayIterator tmp = *this;
    DynamicArrayConstIterator<T>::operator--();
    return tmp;
}

template<typename T>
DynamicArrayIterator<T>& DynamicArrayIterator<T>::operator+=(const difference_type offset) noexcept
{
    DynamicArrayConstIterator<T>::operator+=(offset);
    return *this;
}

template<typename T>
DynamicArrayIterator<T> DynamicArrayIterator<T>::operator+(const difference_type offset) const noexcept
{
    DynamicArrayIterator tmp = *this;
    tmp += offset;
    return tmp;
}

template<typename T>
DynamicArrayIterator<T>& DynamicArrayIterator<T>::operator-=(const difference_type offset) noexcept
{
    DynamicArrayConstIterator<T>::operator-=(offset);
    return *this;
}

template<typename T>
DynamicArrayIterator<T> DynamicArrayIterator<T>::operator-(const difference_type offset) const noexcept
{
    DynamicArrayIterator tmp = *this;
    tmp -= offset;
    return tmp;
}

template<typename T>
typename DynamicArrayIterator<T>::reference
DynamicArrayIterator<T>::operator[](const difference_type offset) const noexcept
{
    return const_cast<reference>(DynamicArrayConstIterator<T>::operator[](offset));
}

template<typename T>
typename DynamicArrayIterator<T>::difference_type
DynamicArrayIterator<T>::operator-(const DynamicArrayConstIterator<T>& rhs) const noexcept
{
    return DynamicArrayConstIterator<T>::operator-(rhs);
}

template<typename T>
DynamicArrayIterator<T>
operator+(typename DynamicArrayIterator<T>::difference_type offset, DynamicArrayIterator<T> iterator) noexcept
{
    iterator += offset;
    return iterator;
}