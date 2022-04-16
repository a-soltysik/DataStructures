#pragma once

#include <istream>

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

    [[nodiscard]] static constexpr const char* ClassName() { return "List"; }

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

    [[nodiscard]] ConstIterator Find(DataType value) const noexcept;
    [[nodiscard]] Iterator Find(DataType value) noexcept;

    [[nodiscard]] size_t Size() const noexcept;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;
    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;
    [[nodiscard]] ConstIterator cbegin() const noexcept;
    [[nodiscard]] ConstIterator cend() const noexcept;

    [[nodiscard]] std::string ToString() const;
    friend std::ostream& operator<<(std::ostream& os, const List& list);
    friend std::istream& operator>>(std::istream& is, List& list);

private:
    struct Node
    {
        DataType value;
        Node* previous;
        Node* next;
    };

    void AddFirstElement(DataType value);
    void RemoveLastElement();
    [[nodiscard]] Node* GetNodeAt(size_t position) const noexcept;

    size_t size = 0u;
    Node* front = nullptr;
    Node* back = nullptr;
};

struct ListConstIterator
{
    friend class List;

    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = List::DataType;
    using pointer = const value_type*;
    using reference = const value_type&;

    ListConstIterator() = default;
    ListConstIterator(const List* parent, List::Node* node) noexcept;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    ListConstIterator& operator++() noexcept;
    ListConstIterator operator++(int) noexcept;
    ListConstIterator& operator--() noexcept;
    ListConstIterator operator--(int) noexcept;

    [[nodiscard]] bool operator==(const ListConstIterator& rhs) const noexcept;
    [[nodiscard]] bool operator!=(const ListConstIterator& rhs) const noexcept;

protected:
    const List* parent;
    List::Node* node;
};

struct ListIterator : public ListConstIterator
{
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = List::DataType;
    using pointer = value_type*;
    using reference = value_type&;

    using ListConstIterator::ListConstIterator;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    ListIterator& operator++() noexcept;
    ListIterator operator++(int) noexcept;
    ListIterator& operator--() noexcept;
    ListIterator operator--(int) noexcept;
};