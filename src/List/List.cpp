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

void List::Insert(size_t position, DataType value)
{
    if (position > size)
    {
        throw std::out_of_range("Position is beyond the size of list");
    }
    if (position == 0u && size == 0u)
    {
        AddFirstElement(value);
        return;
    }
    if (position == size)
    {
        PushBack(value);
        return;
    }
    if (position == 0u)
    {
        PushFront(value);
        return;
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

            return true;
        }
        toDelete = toDelete->next;
    }

    return false;
}

bool List::RemoveAll(DataType value)
{
    Node* toDelete = front;
    bool deleted = false;

    while (toDelete != nullptr)
    {
        if (toDelete->value == value)
        {
            Node* next = toDelete->next;
            toDelete->previous->next = toDelete->next;
            toDelete->next->previous = toDelete->previous;

            delete toDelete;
            deleted = true;

            toDelete = next;
        }
        else
        {
            toDelete = toDelete->next;
        }
    }

    return deleted;
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
        return;
    }

    Node* toDelete = back;

    back = back->previous;
    back->next = nullptr;

    delete toDelete;
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
        return;
    }

    Node* toDelete = front;

    front = front->next;
    front->previous = nullptr;

    delete toDelete;
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

size_t List::Find(DataType value, size_t start) const noexcept
{
    Node* iterator = front;
    size_t position = 0u;
    while (iterator != nullptr)
    {
        if (iterator->value == value && position >= start)
        {
            return position;
        }
        position++;
        iterator = iterator->next;
    }
    return INVALID_INDEX;
}

inline size_t List::Size() const noexcept
{
    return size;
}

List::Node* List::Front()
{
    return front;
}

const List::Node* List::Front() const
{
    return front;
}

List::Node* List::Back()
{
    return back;
}

const List::Node* List::Back() const
{
    return back;
}

void List::AddFirstElement(DataType value)
{
    Node* newNode = new Node(value);
    front = newNode;
    back = newNode;
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

std::ostream& operator<<(std::ostream& os, const List& list)
{
    const List::Node* iterator = list.Front();
    os << "[";
    while (iterator != nullptr)
    {
        os << iterator->value;
        if (iterator->next != nullptr)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
