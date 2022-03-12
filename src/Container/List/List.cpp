#include "Container/List/List.h"

List::List(std::initializer_list<DataType> initList)
{
    for (const auto& item : initList)
    {
        PushBack(item);
    }
}

List::List(const List& rhs)
{
    Node* node = rhs.front;
    while (node != nullptr)
    {
        PushBack(node->value);
        node = node->next;
    }
}

List::List(List&& rhs) noexcept
{
    front = rhs.front;
    back = rhs.back;
    size = rhs.size;

    rhs.front = nullptr;
    rhs.back = nullptr;
    rhs.size = 0u;
}

List& List::operator=(const List& rhs)
{
    Clear();
    Node* node = rhs.front;
    while (node != nullptr)
    {
        PushBack(node->value);
        node = node->next;
    }
    return *this;
}

List& List::operator=(List&& rhs) noexcept
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

List::~List()
{
    Clear();
}

List::DataType& List::operator[](size_t position)
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

const List::DataType& List::operator[](size_t position) const
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

void List::PushBack(DataType value)
{
    if (size == 0u)
    {
        AddFirstElement(value);
        return;
    }
    Node* newNode = new Node(value);
    newNode->previous = back;
    back->next = newNode;
    back = newNode;

    size++;
}

void List::PushFront(DataType value)
{
    if (size == 0u)
    {
        AddFirstElement(value);
        return;
    }
    Node* newNode = new Node(value);
    newNode->next = front;
    front->previous = newNode;
    front = newNode;

    size++;
}

List::Iterator List::Insert(size_t position, DataType value)
{
    if (position > size)
    {
        throw std::out_of_range("Index is out of range");
    }
    if (size == 0u)
    {
        AddFirstElement(value);
        return Iterator(this, front);
    }
    if (position == size)
    {
        PushBack(value);
        return Iterator(this, back);
    }
    if (position == 0u)
    {
        PushFront(value);
        return Iterator(this, front);
    }

    Node* iterator = GetNodeAt(position);

    Node* newNode = new Node(value);
    newNode->next = iterator;
    newNode->previous = iterator->previous;

    iterator->previous->next = newNode;
    iterator->previous = newNode;
    size++;

    return Iterator(this, newNode);
}

List::Iterator List::Insert(ConstIterator iterator, DataType value)
{
    if (size == 0u)
    {
        AddFirstElement(value);
        return Iterator(this, front);
    }
    if (iterator == cend())
    {
        PushBack(value);
        return Iterator(this, back);
    }
    if (iterator == cbegin())
    {
        PushFront(value);
        return Iterator(this, front);
    }

    Node* newNode = new Node(value);
    newNode->next = iterator.node;
    newNode->previous = iterator.node->previous;

    iterator.node->previous->next = newNode;
    iterator.node->previous = newNode;

    size++;
    return Iterator(this, newNode);
}

bool List::Remove(DataType value)
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

void List::RemoveBack()
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

void List::RemoveFront()
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

void List::RemoveAt(size_t positionToRemove)
{
    if (positionToRemove == 0u && size == 1u)
    {
        RemoveLastElement();
        return;
    }
    if (positionToRemove == size - 1)
    {
        RemoveBack();
        return;
    }
    if (positionToRemove == 0u)
    {
        RemoveFront();
        return;
    }
    Node* toDelete = GetNodeAt(positionToRemove);

    toDelete->previous->next = toDelete->next;
    toDelete->next->previous = toDelete->previous;

    delete toDelete;
    size--;
}

void List::RemoveAt(ConstIterator iterator)
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

void List::Clear()
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

List::ConstIterator List::Find(DataType value) const noexcept
{
    for (auto it = cbegin(); it != cend(); it++)
    {
        if (value == *it)
        {
            return it;
        }
    }
    return cend();
}

List::Iterator List::Find(DataType value) noexcept
{
    for (auto it = begin(); it != end(); it++)
    {
        if (value == *it)
        {
            return it;
        }
    }
    return end();
}

size_t List::Size() const noexcept
{
    return size;
}

List::Iterator List::begin() noexcept
{
    return Iterator(this, front);
}

List::Iterator List::end() noexcept
{
    return Iterator(this, nullptr);
}

List::ConstIterator List::cbegin() const noexcept
{
    return ConstIterator(this, front);
}

List::ConstIterator List::cend() const noexcept
{
    return ConstIterator(this, nullptr);
}

void List::AddFirstElement(DataType value)
{
    Node* newNode = new Node(value);
    front = newNode;
    back = newNode;
    size++;
}

void List::RemoveLastElement()
{
    delete front;
    back = nullptr;
    front = nullptr;
    size = 0u;
}

List::Node* List::GetNodeAt(size_t position) const
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

bool List::Serialize(std::ostream& os) const
{
    if (!os.good())
    {
        return false;
    }
    os << size << "\n";
    Node* iterator = front;
    while (iterator != nullptr)
    {
        os << iterator->value << " ";
        iterator = iterator->next;
    }
    if (os.good())
    {
        return true;
    }
    return false;
}

std::optional<List> List::Deserialize(std::istream& is)
{
    if (!is.good())
    {
        return {};
    }
    size_t size;
    is >> size;
    List list;
    for (size_t i = 0u; i < size && is.good(); i++)
    {
        List::DataType value;
        is >> value;
        list.PushBack(value);
    }

    if (is.good())
    {
        return list;
    }
    return {};
}

std::ostream& operator<<(std::ostream& os, List& list)
{
    const List::Node* iterator = list.front;
    os << "[";
    while (iterator != nullptr)
    {
        os << iterator->value;
        if (iterator->next != nullptr)
        {
            os << ", ";
        }
        iterator = iterator->next;
    }
    os << "]";
    return os;
}


ListConstIterator::ListConstIterator(const List* parent, List::Node* node) noexcept
    : parent(parent)
    , node(node)
{}

ListConstIterator::reference ListConstIterator::operator*() const noexcept
{
    return node->value;
}

ListConstIterator::pointer ListConstIterator::operator->() const noexcept
{
    return &(**this);
}

ListConstIterator& ListConstIterator::operator++() noexcept
{
    node = node->next;
    return *this;
}

ListConstIterator ListConstIterator::operator++(int) noexcept
{
    ListConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

ListConstIterator& ListConstIterator::operator--() noexcept
{
    node = node ? node->previous : parent->back;
    return *this;
}

ListConstIterator ListConstIterator::operator--(int) noexcept
{
    ListConstIterator tmp = *this;
    --(*this);
    return tmp;
}

bool ListConstIterator::operator==(const ListConstIterator& rhs) const noexcept
{
    return node == rhs.node;
}

bool ListConstIterator::operator!=(const ListConstIterator& rhs) const noexcept
{
    return !(*this == rhs);
}

ListIterator::reference ListIterator::operator*() const noexcept
{
    return const_cast<reference>(ListConstIterator::operator*());
}

ListIterator::pointer ListIterator::operator->() const noexcept
{
    return &(**this);
}

ListIterator& ListIterator::operator++() noexcept
{
    ListConstIterator::operator++();
    return *this;
}

ListIterator ListIterator::operator++(int) noexcept
{
    ListIterator tmp = *this;
    ListConstIterator::operator++();
    return tmp;
}

ListIterator& ListIterator::operator--() noexcept
{
    ListConstIterator::operator--();
    return *this;
}

ListIterator ListIterator::operator--(int) noexcept
{
    ListIterator tmp = *this;
    ListConstIterator::operator--();
    return tmp;
}