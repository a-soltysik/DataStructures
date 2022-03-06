#pragma once

#include <istream>
#include <optional>
#include <iterator>

struct ListIterator;
struct ListConstIterator;

class List
{
public:
    friend struct ListIterator;
    friend struct ListConstIterator;

    using DataType = int32_t;
    using Iterator = ListIterator;
    using ConstIterator = ListConstIterator;

    List() = default;
    List(std::initializer_list<DataType> initList);
    List(const List& rhs);
    List(List&& rhs) noexcept;
    List& operator=(const List& rhs);
    List& operator=(List&& rhs) noexcept;
    ~List();

    [[nodiscard]] DataType& operator[](size_t position);
    [[nodiscard]] const DataType& operator[](size_t position) const;

    void PushBack(DataType value);
    void PushFront(DataType value);
    Iterator Insert(size_t position, DataType value);
    Iterator Insert(ConstIterator iterator, DataType value);

    bool Remove(DataType value);
    void RemoveBack();
    void RemoveFront();
    void RemoveAt(size_t positionToRemove);
    void RemoveAt(ConstIterator iterator);

    void Clear();

    ConstIterator Find(DataType value) const noexcept;
    Iterator Find(DataType value) noexcept;

    [[nodiscard]] size_t Size() const noexcept;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;

    [[nodiscard]] ConstIterator cbegin() const noexcept;
    [[nodiscard]] ConstIterator cend() const noexcept;

    static bool Serialize(std::ostream& os, const List& array);
    static std::optional<List> Deserialize(std::istream& is);
    friend std::ostream& operator<<(std::ostream& os, List& array);

private:
    struct Node
    {
        Node() = default;
        Node(const DataType& value) : value(value) {}

        DataType value;
        Node* previous = nullptr;
        Node* next = nullptr;
    };

    void AddFirstElement(DataType value);
    void RemoveLastElement();
    Node* GetNodeAt(size_t position) const;

    size_t size = 0u;
    Node* front = nullptr;
    Node* back = nullptr;
};

struct ListConstIterator
{
    friend class List;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = List::DataType;
    using pointer = const List::DataType*;
    using reference = const List::DataType&;

    ListConstIterator() = default;
    ListConstIterator(const List& parent, List::Node* node) noexcept;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    ListConstIterator& operator++() noexcept;
    ListConstIterator operator++(int) noexcept;
    ListConstIterator& operator--() noexcept;
    ListConstIterator operator--(int) noexcept;

    [[nodiscard]] bool operator==(const ListConstIterator& rhs) const noexcept;
    [[nodiscard]] bool operator!=(const ListConstIterator& rhs) const noexcept;

protected:
    List::Node* node;
    const List& parent;
};

struct ListIterator : public ListConstIterator
{
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = List::DataType;
    using pointer = List::DataType*;
    using reference = List::DataType&;

    using ListConstIterator::ListConstIterator;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    ListIterator& operator++() noexcept;
    ListIterator operator++(int) noexcept;
    ListIterator& operator--() noexcept;
    ListIterator operator--(int) noexcept;

    [[nodiscard]] bool operator==(const ListIterator& rhs) const noexcept;
    [[nodiscard]] bool operator!=(const ListIterator& rhs) const noexcept;
};