#pragma once
#include <istream>
#include <optional>
#include <list>

class List
{
public:
    using DataType = int32_t;
private:
    struct Node
    {
        Node() = default;
        Node(const DataType& value) : value(value) {}

        DataType value;
        Node* previous = nullptr;
        Node* next = nullptr;
    };
public:
    struct Iterator
    {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = DataType;
        using pointer = DataType*;
        using reference = DataType&;

        Iterator(const List& parent) : parent(parent), node() {};

        Iterator(const List& parent, Node* node) noexcept : parent(parent), node(node) {}

        [[nodiscard]] reference operator*() const noexcept { return node->value; }

        [[nodiscard]] pointer operator->() const noexcept { return &(**this); }

        Iterator& operator++() noexcept 
        { 
            node = node->next; 
            return *this; 
        }
        Iterator operator++(int) noexcept 
        { 
            Iterator tmp = *this; 
            ++(*this); 
            return tmp; 
        }
        Iterator& operator--() noexcept 
        { 
            node = node ? node->previous : parent.back; 
            return *this; 
        }
        Iterator operator--(int) noexcept 
        { 
            Iterator tmp = *this;
            --(*this); 
            return tmp; 
        }

        [[nodiscard]] bool operator==(const Iterator & rhs) const noexcept { return node == rhs.node; }
        [[nodiscard]] bool operator!=(const Iterator & rhs) const noexcept { return !(*this == rhs); }
    private:
        Node* node;
        const List& parent;
    };

    List() = default;
    List(const List& rhs);
    List(List&& rhs) noexcept;
    List& operator=(const List& rhs);
    List& operator=(List&& rhs) noexcept;
    ~List();

    [[nodiscard]] DataType& operator[](size_t position);
    [[nodiscard]] const DataType& operator[](size_t position) const;

    void PushBack(DataType value);
    void PushFront(DataType value);
    void Insert(size_t position, DataType value);

    bool Remove(DataType value);
    bool RemoveAll(DataType value);

    void RemoveBack();
    void RemoveFront();
    void RemoveAt(size_t positionToRemove);

    void Clear();

    size_t Find(DataType value, size_t start = 0u) const noexcept;

    [[nodiscard]] size_t Size() const noexcept;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;

    static bool Serialize(std::ostream& os, const List& array);
    static std::optional<List> Deserialize(std::istream& is);
    friend std::ostream& operator<<(std::ostream& os, List& array);

    static constexpr size_t INVALID_INDEX = SIZE_MAX;

private:

    void AddFirstElement(DataType value);

    size_t size = 0u;
    Node* front = nullptr;
    Node* back = nullptr;
};

