#pragma once

#include "Utils/Parser.h"

#include <istream>

template<typename T>
struct ListIterator;

template<typename T>
struct ListConstIterator;

template<typename T>
class List
{
public:
    friend struct ListIterator<T>;
    friend struct ListConstIterator<T>;

    using DataType = T;
    using Iterator = ListIterator<T>;
    using ConstIterator = ListConstIterator<T>;

    [[nodiscard]] static constexpr const char* ClassName() { return "List"; }

    List() = default;
    List(std::initializer_list<DataType> initList);

    template<typename It>
    List(It first, It last);

    List(const List& rhs);
    List(List&& rhs) noexcept;
    List& operator=(const List& rhs);
    List& operator=(List&& rhs) noexcept;
    ~List();

    [[nodiscard]] DataType& operator[](size_t position);
    [[nodiscard]] const DataType& operator[](size_t position) const;

    void PushBack(const DataType& value);
    void PushFront(const DataType& value);
    Iterator Insert(size_t position, const DataType& value);
    Iterator Insert(ConstIterator iterator, const DataType& value);

    bool Remove(const DataType& value);
    void RemoveBack();
    void RemoveFront();
    void RemoveAt(size_t positionToRemove);
    void RemoveAt(ConstIterator iterator);

    void Clear();

    [[nodiscard]] ConstIterator Find(const DataType& value) const noexcept;
    [[nodiscard]] Iterator Find(const DataType& value) noexcept;

    [[nodiscard]] size_t Size() const noexcept;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;
    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;
    [[nodiscard]] ConstIterator cbegin() const noexcept;
    [[nodiscard]] ConstIterator cend() const noexcept;

    [[nodiscard]] std::string ToString() const;
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const List<U>& list);

    template<typename U>
    friend std::istream& operator>>(std::istream& is, List<U>& list);

private:
    struct Node
    {
        DataType value;
        Node* previous;
        Node* next;
    };

    void AddFirstElement(const DataType& value);
    void RemoveLastElement();
    [[nodiscard]] Node* GetNodeAt(size_t position) const noexcept;

    size_t size = 0u;
    Node* front = nullptr;
    Node* back = nullptr;
};

template<typename T>
struct ListConstIterator
{
    friend class List<T>;

    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = typename List<T>::DataType;
    using pointer = const value_type*;
    using reference = const value_type&;

    ListConstIterator() = default;
    ListConstIterator(const List<T>* parent, typename List<T>::Node* node) noexcept;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    ListConstIterator& operator++() noexcept;
    ListConstIterator operator++(int) noexcept;
    ListConstIterator& operator--() noexcept;
    ListConstIterator operator--(int) noexcept;

    [[nodiscard]] bool operator==(const ListConstIterator& rhs) const noexcept;
    [[nodiscard]] bool operator!=(const ListConstIterator& rhs) const noexcept;

protected:
    const List<T>* parent;
    typename List<T>::Node* node;
};

template<typename T>
struct ListIterator : public ListConstIterator<T>
{
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = typename List<T>::DataType;
    using pointer = value_type*;
    using reference = value_type&;

    using ListConstIterator<T>::ListConstIterator;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    ListIterator& operator++() noexcept;
    ListIterator operator++(int) noexcept;
    ListIterator& operator--() noexcept;
    ListIterator operator--(int) noexcept;
};

template<typename T>
List<T>::List(std::initializer_list<DataType> initList)
{
    for (const auto& item: initList)
    {
        PushBack(item);
    }
}

template<typename T>
template<typename It>
List<T>::List(It first, It last)
{
    while (first != last)
    {
        PushBack(*first);
        first++;
    }
}

template<typename T>
List<T>::List(const List& rhs)
{
    Node* node = rhs.front;
    while (node != nullptr)
    {
        PushBack(node->value);
        node = node->next;
    }
}

template<typename T>
List<T>::List(List&& rhs) noexcept
{
    front = rhs.front;
    back = rhs.back;
    size = rhs.size;

    rhs.front = nullptr;
    rhs.back = nullptr;
    rhs.size = 0u;
}

template<typename T>
List<T>& List<T>::operator=(const List& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    Clear();
    Node* node = rhs.front;
    while (node != nullptr)
    {
        PushBack(node->value);
        node = node->next;
    }
    return *this;
}

template<typename T>
List<T>& List<T>::operator=(List&& rhs) noexcept
{
    Clear();
    front = rhs.front;
    back = rhs.back;
    size = rhs.size;

    rhs.front = nullptr;
    rhs.back = nullptr;
    rhs.size = 0u;
    return *this;
}

template<typename T>
List<T>::~List()
{
    Clear();
}

template<typename T>
typename List<T>::DataType& List<T>::operator[](size_t position)
{
    if (position >= size)
    {
        throw std::out_of_range("Index is out of range");
    }
    if (position == 0u)
    {
        return front->value;
    }
    if (position == size - 1u)
    {
        return back->value;
    }

    return GetNodeAt(position)->value;
}

template<typename T>
const typename List<T>::DataType& List<T>::operator[](size_t position) const
{
    if (position >= size)
    {
        throw std::out_of_range("Index is out of range");
    }
    if (position == 0u)
    {
        return front->value;
    }
    if (position == size - 1u)
    {
        return back->value;
    }

    return GetNodeAt(position)->value;
}

template<typename T>
void List<T>::PushBack(const DataType& value)
{
    if (size == 0u)
    {
        AddFirstElement(value);
        return;
    }
    Node* newNode = new Node {};
    newNode->value = value;
    newNode->previous = back;
    back->next = newNode;
    back = newNode;

    size++;
}

template<typename T>
void List<T>::PushFront(const DataType& value)
{
    if (size == 0u)
    {
        AddFirstElement(value);
        return;
    }
    Node* newNode = new Node {};
    newNode->value = value;
    newNode->next = front;
    front->previous = newNode;
    front = newNode;

    size++;
}

template<typename T>
typename List<T>::Iterator List<T>::Insert(size_t position, const DataType& value)
{
    if (position > size)
    {
        throw std::out_of_range("Index is out of range");
    }
    if (size == 0u)
    {
        AddFirstElement(value);
        return {this, front};
    }
    if (position == size)
    {
        PushBack(value);
        return {this, back};
    }
    if (position == 0u)
    {
        PushFront(value);
        return {this, front};
    }

    Node* iterator = GetNodeAt(position);

    Node* newNode = new Node {};
    newNode->value = value;
    newNode->next = iterator;
    newNode->previous = iterator->previous;

    iterator->previous->next = newNode;
    iterator->previous = newNode;
    size++;

    return {this, newNode};
}

template<typename T>
typename List<T>::Iterator List<T>::Insert(ConstIterator iterator, const DataType& value)
{
    if (size == 0u)
    {
        AddFirstElement(value);
        return {this, front};
    }
    if (iterator == cend())
    {
        PushBack(value);
        return {this, back};
    }
    if (iterator == cbegin())
    {
        PushFront(value);
        return {this, front};
    }

    Node* newNode = new Node {};
    newNode->value = value;
    newNode->next = iterator.node;
    newNode->previous = iterator.node->previous;

    iterator.node->previous->next = newNode;
    iterator.node->previous = newNode;

    size++;
    return {this, newNode};
}

template<typename T>
bool List<T>::Remove(const DataType& value)
{
    Node* toDelete = front;

    while (toDelete != nullptr)
    {
        if (toDelete->value == value)
        {
            if (size == 1u)
            {
                RemoveLastElement();
                return true;
            }
            if (toDelete == front)
            {
                RemoveFront();
                return true;
            }
            if (toDelete == back)
            {
                RemoveBack();
                return true;
            }
            toDelete->previous->next = toDelete->next;
            toDelete->next->previous = toDelete->previous;

            delete toDelete;
            toDelete = nullptr;
            size--;

            return true;
        }
        toDelete = toDelete->next;
    }

    return false;
}

template<typename T>
void List<T>::RemoveBack()
{
    if (size == 0u)
    {
        return;
    }
    if (size == 1u)
    {
        RemoveLastElement();
        return;
    }

    Node* toDelete = back;

    back = back->previous;
    back->next = nullptr;

    delete toDelete;
    size--;
}

template<typename T>
void List<T>::RemoveFront()
{
    if (size == 0u)
    {
        return;
    }
    if (size == 1u)
    {
        RemoveLastElement();
        return;
    }

    Node* toDelete = front;

    front = front->next;
    front->previous = nullptr;

    delete toDelete;
    size--;
}

template<typename T>
void List<T>::RemoveAt(size_t position)
{
    if (position == 0u && size == 1u)
    {
        RemoveLastElement();
        return;
    }
    if (position == size - 1)
    {
        RemoveBack();
        return;
    }
    if (position == 0u)
    {
        RemoveFront();
        return;
    }
    Node* toDelete = GetNodeAt(position);

    toDelete->previous->next = toDelete->next;
    toDelete->next->previous = toDelete->previous;

    delete toDelete;
    size--;
}

template<typename T>
void List<T>::RemoveAt(ConstIterator iterator)
{
    if (size == 1u)
    {
        RemoveLastElement();
        return;
    }
    if (iterator == --cend())
    {
        RemoveBack();
        return;
    }
    if (iterator == cbegin())
    {
        RemoveFront();
        return;
    }
    Node* toDelete = iterator.node;

    toDelete->previous->next = toDelete->next;
    toDelete->next->previous = toDelete->previous;

    delete toDelete;
    size--;
}

template<typename T>
void List<T>::Clear()
{
    while (front != nullptr)
    {
        Node* tmp = front;
        front = front->next;
        delete tmp;
        tmp = nullptr;
    }
    size = 0u;
}

template<typename T>
typename List<T>::ConstIterator List<T>::Find(const DataType& value) const noexcept
{
    Node* iterator = front;

    while (iterator != nullptr && iterator->value != value)
    {
        iterator = iterator->next;
    }
    return {this, iterator};
}

template<typename T>
typename List<T>::Iterator List<T>::Find(const DataType& value) noexcept
{
    Node* iterator = front;

    while (iterator != nullptr && iterator->value != value)
    {
        iterator = iterator->next;
    }
    return {this, iterator};
}

template<typename T>
size_t List<T>::Size() const noexcept
{
    return size;
}

template<typename T>
typename List<T>::Iterator List<T>::begin() noexcept
{
    return {this, front};
}

template<typename T>
typename List<T>::Iterator List<T>::end() noexcept
{
    return {this, nullptr};
}

template<typename T>
typename List<T>::ConstIterator List<T>::begin() const noexcept
{
    return {this, front};
}

template<typename T>
typename List<T>::ConstIterator List<T>::end() const noexcept
{
    return {this, nullptr};
}

template<typename T>
typename List<T>::ConstIterator List<T>::cbegin() const noexcept
{
    return {this, front};
}

template<typename T>
typename List<T>::ConstIterator List<T>::cend() const noexcept
{
    return {this, nullptr};
}

template<typename T>
void List<T>::AddFirstElement(const DataType& value)
{
    Node* newNode = new Node {};
    newNode->value = value;
    front = newNode;
    back = newNode;
    size++;
}

template<typename T>
void List<T>::RemoveLastElement()
{
    delete front;
    back = nullptr;
    front = nullptr;
    size = 0u;
}

template<typename T>
typename List<T>::Node* List<T>::GetNodeAt(size_t position) const noexcept
{
    if (position < size / 2)
    {
        size_t counter = 0u;
        Node* iterator = front;

        while (counter != position)
        {
            iterator = iterator->next;
            counter++;
        }
        return iterator;
    }
    else
    {
        size_t counter = size - 1u;
        Node* iterator = back;

        while (counter != position)
        {
            iterator = iterator->previous;
            counter--;
        }
        return iterator;
    }
}

template<typename T>
std::string List<T>::ToString() const
{
    const List::Node* iterator = front;
    std::string result = "[";
    while (iterator != nullptr)
    {
        result += Utils::Parser::NumberToString(iterator->value);
        if (iterator->next != nullptr)
        {
            result += ", ";
        }
        iterator = iterator->next;
    }

    return result + "]";
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list)
{
    if (os.fail())
    {
        return os;
    }
    os << list.Size() << "\n";
    auto* iterator = list.front;
    while (iterator != nullptr && !os.fail())
    {
        os << iterator->value << " ";
        iterator = iterator->next;
    }
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, List<T>& list)
{
    if (is.fail())
    {
        return is;
    }
    size_t size;
    is >> size;
    for (size_t i = 0u; i < size && !is.fail(); i++)
    {
        typename List<T>::DataType value;
        is >> value;
        list.PushBack(value);
    }

    return is;
}

template<typename T>
ListConstIterator<T>::ListConstIterator(const List<T>* parent, typename List<T>::Node* node) noexcept
    : parent(parent)
    , node(node) { }

template<typename T>
typename ListConstIterator<T>::reference ListConstIterator<T>::operator*() const noexcept
{
    return node->value;
}

template<typename T>
typename ListConstIterator<T>::pointer ListConstIterator<T>::operator->() const noexcept
{
    return &(**this);
}

template<typename T>
ListConstIterator<T>& ListConstIterator<T>::operator++() noexcept
{
    node = node->next;
    return *this;
}

template<typename T>
ListConstIterator<T> ListConstIterator<T>::operator++(int) noexcept
{
    ListConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

template<typename T>
ListConstIterator<T>& ListConstIterator<T>::operator--() noexcept
{
    node = node ? node->previous : parent->back;
    return *this;
}

template<typename T>
ListConstIterator<T> ListConstIterator<T>::operator--(int) noexcept
{
    ListConstIterator tmp = *this;
    --(*this);
    return tmp;
}

template<typename T>
bool ListConstIterator<T>::operator==(const ListConstIterator<T>& rhs) const noexcept
{
    return node == rhs.node;
}

template<typename T>
bool ListConstIterator<T>::operator!=(const ListConstIterator<T>& rhs) const noexcept
{
    return !(*this == rhs);
}

template<typename T>
typename ListIterator<T>::reference ListIterator<T>::operator*() const noexcept
{
    return const_cast<reference>(ListConstIterator<T>::operator*());
}

template<typename T>
typename ListIterator<T>::pointer ListIterator<T>::operator->() const noexcept
{
    return &(**this);
}

template<typename T>
ListIterator<T>& ListIterator<T>::operator++() noexcept
{
    ListConstIterator<T>::operator++();
    return *this;
}

template<typename T>
ListIterator<T> ListIterator<T>::operator++(int) noexcept
{
    ListIterator tmp = *this;
    ListConstIterator<T>::operator++();
    return tmp;
}

template<typename T>
ListIterator<T>& ListIterator<T>::operator--() noexcept
{
    ListConstIterator<T>::operator--();
    return *this;
}

template<typename T>
ListIterator<T> ListIterator<T>::operator--(int) noexcept
{
    ListIterator tmp = *this;
    ListConstIterator<T>::operator--();
    return tmp;
}