#pragma once
#include <istream>
#include <optional>

class List
{
public:
    using DataType = int32_t;
    struct Node
    {
        Node() = default;
        Node(const DataType& value) : value(value) {}

        DataType value;
        Node* previous = nullptr;
        Node* next = nullptr;
    };

    List() = default;
    List(const List& rhs);
    List(List&& rhs) noexcept;
    List& operator=(const List& rhs);
    List& operator=(List&& rhs) noexcept;
    ~List();

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

    size_t Find(DataType value, size_t start = 0u) const noexcept;

    [[nodiscard]]
    size_t Size() const noexcept;

    [[nodiscard]]
    Node* Front();
    [[nodiscard]]
    const Node* Front() const;

    [[nodiscard]]
    Node* Back();
    [[nodiscard]]
    const Node* Back() const;

    static bool Serialize(std::ostream& os, const List& array);
    static std::optional<List> Deserialize(std::istream& is);

    static constexpr size_t INVALID_INDEX = SIZE_MAX;

private:
    void AddFirstElement(DataType value);

    size_t size = 0u;
    Node* front = nullptr;
    Node* back = nullptr;
};

std::ostream& operator<<(std::ostream& os, const List& array);