#pragma once

#include "RedBlackTree.h"
#include "Utils/Pair.h"

template<typename T>
struct MapComparator
{
    constexpr bool operator()(const T& lhs, const T& rhs) const noexcept
    {
        return lhs.first < rhs.first;
    }
};

template<typename K, typename V, typename C = MapComparator<Utils::Pair<const K, V>>>
class Map
{
public:
    using KeyType = K;
    using ValueType = V;
    using Comparator = C;
    using DataType = Utils::Pair<const K, V>;
    using Iterator = typename RedBlackTree<DataType, C>::Iterator;
    using ConstIterator = typename RedBlackTree<DataType, C>::ConstIterator;

    [[nodiscard]] static constexpr const char* ClassName() noexcept { return "Map"; }

    Map(const Comparator& comparator = Comparator());
    Map(std::initializer_list<DataType> initList, const Comparator& comparator = Comparator());

    [[nodiscard]] ValueType& operator[](const KeyType& key);
    [[nodiscard]] ValueType& at(const KeyType& key);
    [[nodiscard]] const ValueType& at(const KeyType& key) const;

    Iterator Insert(const DataType& value);
    bool Remove(const KeyType& key);
    void Clear();

    [[nodiscard]] ConstIterator Find(const KeyType& key) const noexcept;
    [[nodiscard]] Iterator Find(const KeyType& key) noexcept;

    [[nodiscard]] const DataType& Min() const noexcept;
    [[nodiscard]] const DataType& Max() const noexcept;

    [[nodiscard]] size_t Size() const noexcept;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;
    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;
    [[nodiscard]] ConstIterator cbegin() const noexcept;
    [[nodiscard]] ConstIterator cend() const noexcept;

    [[nodiscard]] std::string ToString() const;

    template<typename T, typename U>
    friend std::ostream& operator<<(std::ostream& os, const Map<T, U>& set);

    template<typename T, typename U>
    friend std::istream& operator>>(std::istream& is, Map<T, U>& set);

private:

    RedBlackTree<DataType, C> tree;
};

template<typename K, typename V, typename C>
Map<K, V, C>::Map(const Comparator& comparator)
    : tree(comparator)
{}

template<typename K, typename V, typename C>
Map<K, V, C>::Map(std::initializer_list<DataType> initList, const Comparator& comparator)
    : tree(initList, comparator)
{ }

template<typename K, typename V, typename C>
typename Map<K, V, C>::ValueType& Map<K, V, C>::operator[](const KeyType& key)
{
    auto it = Find(key);
    if (it != end())
    {
        return it->second;
    }

    return Insert({key, ValueType()})->second;
}

template<typename K, typename V, typename C>
typename Map<K, V, C>::ValueType& Map<K, V, C>::at(const KeyType& key)
{
    auto it = Find(key);
    if (it != end())
    {
        return it->second;
    }

    throw std::out_of_range("No such element exists");
}

template<typename K, typename V, typename C>
const typename Map<K, V, C>::ValueType& Map<K, V, C>::at(const KeyType& key) const
{
    auto it = Find(key);
    if (it != end())
    {
        return it->second;
    }

    throw std::out_of_range("No such element exists");
}

template<typename K, typename V, typename C>
typename Map<K, V, C>::Iterator Map<K, V, C>::Insert(const DataType& value)
{
    if (Find(value.first) != end())
    {
        return end();
    }
    tree.Insert(value);

    return --end();
}

template<typename K, typename V, typename C>
bool Map<K, V, C>::Remove(const KeyType& key)
{
    auto it = Find(key);
    if (it == end())
    {
        return false;
    }
    return tree.Remove({key, it->second});
}

template<typename K, typename V, typename C>
void Map<K, V, C>::Clear()
{
    tree.Clear();
}

template<typename K, typename V, typename C>
typename Map<K, V, C>::ConstIterator Map<K, V, C>::Find(const KeyType& key) const noexcept
{
    return tree.Find({key, ValueType()});
}

template<typename K, typename V, typename C>
typename Map<K, V, C>::Iterator Map<K, V, C>::Find(const KeyType& key) noexcept
{
    return tree.Find({key, ValueType()});
}

template<typename K, typename V, typename C>
const typename Map<K, V, C>::DataType& Map<K, V, C>::Min() const noexcept
{
    return tree.Min();
}

template<typename K, typename V, typename C>
const typename Map<K, V, C>::DataType& Map<K, V, C>::Max() const noexcept
{
    return tree.Max();
}

template<typename K, typename V, typename C>
size_t Map<K, V, C>::Size() const noexcept
{
    return tree.Size();
}

template<typename K, typename V, typename C>
typename Map<K, V, C>::Iterator Map<K, V, C>::begin() noexcept
{
    return tree.begin();
}

template<typename K, typename V, typename C>
typename Map<K, V, C>::Iterator Map<K, V, C>::end() noexcept
{
    return tree.end();
}

template<typename K, typename V, typename C>
typename Map<K, V, C>::ConstIterator Map<K, V, C>::begin() const noexcept
{
    return tree.begin();
}

template<typename K, typename V, typename C>
typename Map<K, V, C>::ConstIterator Map<K, V, C>::end() const noexcept
{
    return tree.end();
}

template<typename K, typename V, typename C>
typename Map<K, V, C>::ConstIterator Map<K, V, C>::cbegin() const noexcept
{
    return tree.cbegin();
}

template<typename K, typename V, typename C>
typename Map<K, V, C>::ConstIterator Map<K, V, C>::cend() const noexcept
{
    return tree.cend();
}

template<typename K, typename V, typename C>
std::string Map<K, V, C>::ToString() const
{
    size_t i = 0;
    std::string result = "{";
    for (const auto& pair : tree)
    {
        result += pair.first + ": " + pair.second;
        if (i < tree.Size() - 1)
        {
            result += ", ";
        }
    }
    result += "}";

    return result;
}

template<typename K, typename V, typename C>
std::ostream& operator<<(std::ostream& os, const Map<K, V, C>& map)
{
    return os << map.tree;
}

template<typename K, typename V, typename C>
std::istream& operator>>(std::istream& is, Map<K, V, C>& map)
{
    return is >> map.tree;
}