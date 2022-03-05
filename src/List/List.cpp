#include "List/List.h"

List::List(const List& rhs)
{
    Node* node = rhs.front;
    while (node != nullptr)
    {
        PushBack(node->value);
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

    if (position < size / 2)
    {
        size_t counter = 0u;
        Node* iterator = front;

        while (counter != position)
        {
            iterator = iterator->next;
            counter++;
        }
        return iterator->value;
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
        return iterator->value;
    }
}

const List::DataType& List::operator[](size_t position) const
{
    return operator[](position);
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
    front = newNode;

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
        throw std::out_of_range("Position is beyond the size of list");
    }
    if (position == 0u && size == 0u)
    {
        AddFirstElement(value);
        return Iterator(*this, front);
    }
    if (position == size)
    {
        PushBack(value);
        return Iterator(*this, back);
    }
    if (position == 0u)
    {
        PushFront(value);
        return Iterator(*this, front);
    }

    size_t counter = 0u;
    Node* iterator = front;

    while (counter != position)
    {
        iterator = iterator->next;
        counter++;
    }

    Node* newNode = new Node(value);
    newNode->next = iterator;
    newNode->previous = iterator->previous;

    iterator->previous->next = newNode;
    iterator->previous = newNode;
    size++;

    return Iterator(*this, newNode);
}

List::Iterator List::Insert(ConstIterator iterator, DataType value)
{
    if (size == 0u)
    {
        AddFirstElement(value);
        return Iterator(*this, front);
    }
    if (iterator == cend())
    {
        PushBack(value);
        return Iterator(*this, back);
    }

    Node* newNode = new Node(value);
    newNode->next = iterator.node;
    newNode->previous = iterator.node->previous;

    iterator.node->previous->next = newNode;
    iterator.node->previous = newNode;

    size++;
    return Iterator(*this, newNode);
}

bool List::Remove(DataType value)
{
    Node* toDelete = front;

    while (toDelete != nullptr)
    {
        if (toDelete->value == value)
        {
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
        delete front;
        back = nullptr;
        front = nullptr;
        size--;
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
        delete front;
        back = nullptr;
        front = nullptr;
        size--;
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
    Node* toDelete;
    if (positionToRemove < size / 2)
    {
        size_t counter = 0u;
        toDelete = front;

        while (counter != positionToRemove)
        {
            toDelete = toDelete->next;
            counter++;
        }
    }
    else
    {
        size_t counter = size - 1u;
        toDelete = back;

        while (counter != positionToRemove)
        {
            toDelete = toDelete->previous;
            counter--;
        }
    }

    toDelete->previous->next = toDelete->next;
    toDelete->next->previous = toDelete->previous;

    delete toDelete;
    size--;
}

void List::RemoveAt(ConstIterator iterator)
{
    Node* toDelete = iterator.node;

    toDelete->previous->next = toDelete->next;
    toDelete->next->previous = toDelete->previous;

    delete toDelete;
    size--;
}

void List::Clear()
{
    Node* node = front;
    while (node != nullptr)
    {
        Node* tmp = node;
        node = node->next;
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
    return Iterator(*this, front);
}

List::Iterator List::end() noexcept
{
    return Iterator(*this, back->next);
}

List::ConstIterator List::cbegin() const noexcept
{
    return ConstIterator(*this, front);
}

List::ConstIterator List::cend() const noexcept
{
    return ConstIterator(*this, back->next);
}

void List::AddFirstElement(DataType value)
{
    Node* newNode = new Node(value);
    front = newNode;
    back = newNode;
    size++;
}

bool List::Serialize(std::ostream& os, const List& list)
{
    os << list.Size() << "\n";
    Node* iterator = list.front;
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
    size_t size;
    is >> size;
    List list;
    for (size_t i = 0u; i < size; i++)
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


ListConstIterator::ListConstIterator(const List& parent, List::Node* node) noexcept
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
    node = node ? node->previous : parent.back;
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

ListIterator::ListIterator(const List& parent, List::Node* node) noexcept : ListConstIterator(parent, node)
{}

ListIterator::reference ListIterator::operator*() const noexcept
{
    return node->value;
}

ListIterator::pointer ListIterator::operator->() const noexcept
{
    return &(**this);
}

ListIterator& ListIterator::operator++() noexcept
{
    node = node->next;
    return *this;
}

ListIterator ListIterator::operator++(int) noexcept
{
    ListIterator tmp = *this;
    ++(*this);
    return tmp;
}

ListIterator& ListIterator::operator--() noexcept
{
    node = node ? node->previous : parent.back;
    return *this;
}

ListIterator ListIterator::operator--(int) noexcept
{
    ListIterator tmp = *this;
    --(*this);
    return tmp;
}

bool ListIterator::operator==(const ListIterator& rhs) const noexcept
{
    return node == rhs.node;
}

bool ListIterator::operator!=(const ListIterator& rhs) const noexcept
{
    return !(*this == rhs);
}