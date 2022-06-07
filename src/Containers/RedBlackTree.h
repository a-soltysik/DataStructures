#pragma once

#include "Utils/Utils.h"

template<typename K, typename V, typename C>
class Map;

template<typename T, typename C>
struct RedBlackTreeIterator;

template<typename T, typename C>
struct RedBlackTreeConstIterator;

template<typename T, typename C = Utils::Less<T>>
class RedBlackTree
{
public:
    friend struct RedBlackTreeIterator<T, C>;
    friend struct RedBlackTreeConstIterator<T, C>;

    template<typename K, typename V, typename U>
    friend class Map;

    using DataType = T;
    using Comparator = C;
    using Iterator = RedBlackTreeIterator<T, C>;
    using ConstIterator = RedBlackTreeConstIterator<T, C>;

    [[nodiscard]] static constexpr const char* ClassName() noexcept { return "RedBlackTree"; }

    explicit RedBlackTree(const Comparator& comparator = Comparator());
    RedBlackTree(std::initializer_list<DataType> initList, const Comparator& comparator = Comparator());
    RedBlackTree(const RedBlackTree& rhs);
    RedBlackTree(RedBlackTree&& rhs) noexcept;
    RedBlackTree& operator=(const RedBlackTree& rhs);
    RedBlackTree& operator=(RedBlackTree&& rhs) noexcept;
    ~RedBlackTree();

    Iterator Insert(const DataType& value);
    bool Remove(const DataType& value);
    void Clear();

    [[nodiscard]] ConstIterator Find(const DataType& value) const noexcept;
    [[nodiscard]] Iterator Find(const DataType& value) noexcept;

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

    template<typename U, typename V>
    friend std::ostream& operator<<(std::ostream& os, const RedBlackTree<U, V>& tree);

    template<typename U, typename V>
    friend std::istream& operator>>(std::istream& is, RedBlackTree<U, V>& tree);

public:
    struct Node
    {
        enum class Color : uint8_t
        {
            RED,
            BLACK
        };
        Color color;
        DataType value;

        Node* left;
        Node* right;
        Node* parent;
    };

    inline static constexpr int64_t NIL_VALUE = -1;

    [[nodiscard]] static Node* MakeNil();
    [[nodiscard]] Node* MakeNode(const DataType& value) const;

    void LeftRotate(Node* node) const noexcept;
    void RightRotate(Node* node) const noexcept;

    void SetRoot(Node* node) const noexcept;
    [[nodiscard]] Node* Root() const noexcept;

    [[nodiscard]] Node* Min(Node* node) const noexcept;
    [[nodiscard]] Node* Max(Node* node) const noexcept;
    [[nodiscard]] Node* Find(const DataType& value, Node* root) const noexcept;

    void InsertFix(Node* node) const noexcept;
    void RemoveFix(Node* node) const noexcept;

    void MoveSubtree(Node* from, Node* to) const noexcept;
    void RemoveSubtree(Node* root);
    [[nodiscard]] Node* CopySubtree(const RedBlackTree& tree, Node* root);

    void ToString(std::string& result, const std::string& prefix, const Node* node, bool isRight) const;
    void Serialize(std::ostream& os, Node* node) const;
    [[nodiscard]] Node* Deserialize(std::istream& is, Node* node, size_t& sizeOfTree);

    Comparator comparator;
    Node* NIL = MakeNil();
    size_t size = 0u;
};

template<typename T, typename C>
struct RedBlackTreeConstIterator
{
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = typename RedBlackTree<T, C>::DataType;
    using pointer = const value_type*;
    using reference = const value_type&;

    RedBlackTreeConstIterator() = default;
    RedBlackTreeConstIterator(const RedBlackTree<T, C>* redBlackTree, typename RedBlackTree<T, C>::Node* node) noexcept;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    RedBlackTreeConstIterator& operator++() noexcept;
    RedBlackTreeConstIterator operator++(int) noexcept;
    RedBlackTreeConstIterator& operator--() noexcept;
    RedBlackTreeConstIterator operator--(int) noexcept;

    [[nodiscard]] bool operator==(const RedBlackTreeConstIterator& rhs) const noexcept;
    [[nodiscard]] bool operator!=(const RedBlackTreeConstIterator& rhs) const noexcept;

protected:
    const RedBlackTree<T, C>* redBlackTree;
    typename RedBlackTree<T, C>::Node* node;
};

template<typename T, typename C>
struct RedBlackTreeIterator : public RedBlackTreeConstIterator<T, C>
{
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = typename RedBlackTree<T, C>::DataType;
    using pointer = value_type*;
    using reference = value_type&;

    using RedBlackTreeConstIterator<T, C>::RedBlackTreeConstIterator;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    RedBlackTreeIterator& operator++() noexcept;
    RedBlackTreeIterator operator++(int) noexcept;
    RedBlackTreeIterator& operator--() noexcept;
    RedBlackTreeIterator operator--(int) noexcept;
};

template<typename T, typename C>
RedBlackTree<T, C>::RedBlackTree(const Comparator& comparator)
    : comparator(comparator)
{ }

template<typename T, typename C>
RedBlackTree<T, C>::RedBlackTree(std::initializer_list<DataType> initList, const Comparator& comparator)
    : comparator(comparator)
{
    for (const auto& item: initList)
    {
        Insert(item);
    }
}

template<typename T, typename C>
RedBlackTree<T, C>::RedBlackTree(const RedBlackTree& rhs)
{
    SetRoot(CopySubtree(rhs, rhs.Root()));
    size = rhs.size;
    comparator = rhs.comparator;
}

template<typename T, typename C>
RedBlackTree<T, C>::RedBlackTree(RedBlackTree&& rhs) noexcept
{
    NIL = rhs.NIL;
    size = rhs.size;
    comparator = std::move(rhs.comparator);

    rhs.NIL = nullptr;
    rhs.size = 0u;
}

template<typename T, typename C>
RedBlackTree<T, C>& RedBlackTree<T, C>::operator=(const RedBlackTree& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    Clear();
    SetRoot(CopySubtree(rhs, rhs.Root()));
    size = rhs.size;
    comparator = rhs.comparator;

    return *this;
}

template<typename T, typename C>
RedBlackTree<T, C>& RedBlackTree<T, C>::operator=(RedBlackTree&& rhs) noexcept
{
    Clear();
    NIL = rhs.NIL;
    size = rhs.size;
    comparator = std::move(rhs.comparator);

    rhs.NIL = nullptr;
    rhs.size = 0u;

    return *this;
}

template<typename T, typename C>
RedBlackTree<T, C>::~RedBlackTree()
{
    Clear();
    delete NIL;
    NIL = nullptr;
}

template<typename T, typename C>
typename RedBlackTree<T, C>::Iterator RedBlackTree<T, C>::Insert(const DataType& value)
{
    Node* newNode = MakeNode(value);
    Node* parent = NIL;
    Node* iterator = Root();

    size++;

    while (iterator != NIL)
    {
        parent = iterator;
        if (comparator(newNode->value, iterator->value))
        {
            iterator = iterator->left;
        }
        else
        {
            iterator = iterator->right;
        }
    }
    newNode->parent = parent;
    if (parent == NIL)
    {
        SetRoot(newNode);
    }
    else if (comparator(newNode->value, parent->value))
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }

    newNode->color = Node::Color::RED;
    InsertFix(newNode);

    return {this, newNode};
}

template<typename T, typename C>
bool RedBlackTree<T, C>::Remove(const DataType& value)
{
    Node* nodeToRemove = Find(value, Root());
    if (nodeToRemove == NIL)
    {
        return false;
    }
    Node* successor;
    Node* node = nodeToRemove;
    auto originalColor = node->color;

    if (nodeToRemove->left == NIL)
    {
        successor = nodeToRemove->right;
        MoveSubtree(nodeToRemove, nodeToRemove->right);
    }
    else if (nodeToRemove->right == NIL)
    {
        successor = nodeToRemove->left;
        MoveSubtree(nodeToRemove, nodeToRemove->left);
    }
    else
    {
        node = Min(nodeToRemove->right);
        originalColor = node->color;
        successor = node->right;
        if (node->parent == nodeToRemove)
        {
            successor->parent = node;
        }
        else
        {
            MoveSubtree(node, node->right);
            node->right = nodeToRemove->right;
            node->right->parent = node;
        }
        MoveSubtree(nodeToRemove, node);
        node->left = nodeToRemove->left;
        node->left->parent = node;
        node->color = nodeToRemove->color;
    }

    delete nodeToRemove;
    nodeToRemove = nullptr;

    if (originalColor == Node::Color::BLACK)
    {
        RemoveFix(successor);
    }

    size--;
    return true;
}

template<typename T, typename C>
void RedBlackTree<T, C>::Clear()
{
    if (NIL != nullptr)
    {
        if (Root() != nullptr)
        {
            RemoveSubtree(Root());

        }
        NIL->left = NIL;
    }
}

template<typename T, typename C>
typename RedBlackTree<T, C>::ConstIterator RedBlackTree<T, C>::Find(const DataType& value) const noexcept
{
    return {this, Find(value, Root())};
}

template<typename T, typename C>
typename RedBlackTree<T, C>::Iterator RedBlackTree<T, C>::Find(const DataType& value) noexcept
{
    return {this, Find(value, Root())};
}

template<typename T, typename C>
const typename RedBlackTree<T, C>::DataType& RedBlackTree<T, C>::Min() const noexcept
{
    return Min(Root())->value;
}

template<typename T, typename C>
const typename RedBlackTree<T, C>::DataType& RedBlackTree<T, C>::Max() const noexcept
{
    return Max(Root())->value;
}

template<typename T, typename C>
size_t RedBlackTree<T, C>::Size() const noexcept
{
    return size;
}

template<typename T, typename C>
typename RedBlackTree<T, C>::Iterator RedBlackTree<T, C>::begin() noexcept
{
    return {this, Min(Root())};
}

template<typename T, typename C>
typename RedBlackTree<T, C>::Iterator RedBlackTree<T, C>::end() noexcept
{
    return {this, NIL};
}

template<typename T, typename C>
typename RedBlackTree<T, C>::ConstIterator RedBlackTree<T, C>::begin() const noexcept
{
    return {this, Min(Root())};
}

template<typename T, typename C>
typename RedBlackTree<T, C>::ConstIterator RedBlackTree<T, C>::end() const noexcept
{
    return {this, NIL};
}

template<typename T, typename C>
typename RedBlackTree<T, C>::ConstIterator RedBlackTree<T, C>::cbegin() const noexcept
{
    return {this, Min(Root())};
}

template<typename T, typename C>
typename RedBlackTree<T, C>::ConstIterator RedBlackTree<T, C>::cend() const noexcept
{
    return {this, NIL};
}

template<typename T, typename C>
std::string RedBlackTree<T, C>::ToString() const
{
    std::string result;
    ToString(result, "", Root(), false);
    return result;
}

template<typename T, typename C>
std::ostream& operator<<(std::ostream& os, const RedBlackTree<T, C>& tree)
{
    if (os.fail())
    {
        return os;
    }
    os << tree.Size() << "\n";
    tree.Serialize(os, tree.Root());
    return os;
}

template<typename T, typename C>
std::istream& operator>>(std::istream& is, RedBlackTree<T, C>& tree)
{
    if (is.fail())
    {
        return is;
    }
    size_t size;
    is >> size;

    tree.SetRoot(tree.Deserialize(is, tree.NIL, size));
    return is;
}

template<typename T, typename C>
typename RedBlackTree<T, C>::Node* RedBlackTree<T, C>::MakeNil()
{
    Node* nil = new Node {Node::Color::BLACK, // color
                          DataType(),         // value
                          nullptr,            // left
                          nullptr,            // right
                          nullptr};           // parent

    nil->left   = nil;
    nil->right  = nil;
    nil->parent = nil;

    return nil;
}

template<typename T, typename C>
typename RedBlackTree<T, C>::Node* RedBlackTree<T, C>::MakeNode(const DataType& value) const
{
    Node* newNode = new Node {Node::Color::BLACK, // color
                              value,              // value
                              NIL,                // left
                              NIL,                // right
                              NIL};               // parent

    return newNode;
}

template<typename T, typename C>
void RedBlackTree<T, C>::LeftRotate(Node* node) const noexcept
{
    Node* child = node->right;
    node->right = child->left;

    if (child->left != NIL)
    {
        child->left->parent = node;
    }

    child->parent = node->parent;

    if (node->parent == NIL)
    {
        SetRoot(child);
    }
    else if (node == node->parent->left)
    {
        node->parent->left = child;
    }
    else
    {
        node->parent->right = child;
    }

    child->left = node;
    node->parent = child;
}

template<typename T, typename C>
void RedBlackTree<T, C>::RightRotate(Node* node) const noexcept
{
    Node* child = node->left;
    node->left = child->right;

    if (child->right != NIL)
    {
        child->right->parent = node;
    }

    child->parent = node->parent;

    if (node->parent == NIL)
    {
        SetRoot(child);
    }
    else if (node == node->parent->right)
    {
        node->parent->right = child;
    }
    else
    {
        node->parent->left = child;
    }

    child->right = node;
    node->parent = child;
}

template<typename T, typename C>
void RedBlackTree<T, C>::SetRoot(Node* node) const noexcept
{
    NIL->left = node;
    node->parent = NIL;
}

template<typename T, typename C>
typename RedBlackTree<T, C>::Node* RedBlackTree<T, C>::Root() const noexcept
{
    return NIL->left;
}

template<typename T, typename C>
typename RedBlackTree<T, C>::Node* RedBlackTree<T, C>::Min(Node* node) const noexcept
{
    while (node->left != NIL)
    {
        node = node->left;
    }
    return node;
}

template<typename T, typename C>
typename RedBlackTree<T, C>::Node* RedBlackTree<T, C>::Max(Node* node) const noexcept
{
    while (node->right != NIL)
    {
        node = node->right;
    }
    return node;
}

template<typename T, typename C>
typename RedBlackTree<T, C>::Node* RedBlackTree<T, C>::Find(const DataType& value, Node* root) const noexcept
{
    while (root != NIL)
    {
        if (comparator(root->value, value))
        {
            root = root->right;
        }
        else if (comparator(value, root->value))
        {
            root = root->left;
        }
        else
        {
            return root;
        }
    }
    return NIL;
}

template<typename T, typename C>
void RedBlackTree<T, C>::InsertFix(Node* node) const noexcept
{
    while (node->parent->color == Node::Color::RED)
    {
        if (node->parent == node->parent->parent->left)             // Jeśli rodzic jest lewym dzieckiem i...
        {
            Node* rightUncle = node->parent->parent->right;
            if (rightUncle->color == Node::Color::RED)
            {
                node->parent->color = Node::Color::BLACK;           // Jeśli prawy stryj jest czerwony
                rightUncle->color = Node::Color::BLACK;             // przekoloruj węzły
                node->parent->parent->color = Node::Color::RED;     //
                node = node->parent->parent;                        //
            }
            else                                                    // Jeśli prawy stryj jest czarny i...
            {
                if (node == node->parent->right)                    // Jeśli węzeł jest prawym synem
                {                                                   // dokonaj obrotu wokół rodzica
                    node = node->parent;                            //
                    LeftRotate(node);                               //
                }
                node->parent->color = Node::Color::BLACK;           // Jeśli węzeł jest lewym synem
                node->parent->parent->color = Node::Color::RED;     // dokonaj obrotu wokół dziadka
                RightRotate(node->parent->parent);                  // i przekoloruj węzły
            }
        }
        else                                                        // Jeśli rodzic jest prawym dzieckiem i...
        {
            Node* leftUncle = node->parent->parent->left;
            if (leftUncle->color == Node::Color::RED)
            {
                node->parent->color = Node::Color::BLACK;           // Jeśli prawy stryj jest czerwony
                leftUncle->color = Node::Color::BLACK;              // przekoloruj węzły
                node->parent->parent->color = Node::Color::RED;     //
                node = node->parent->parent;                        //
            }
            else                                                    // Jeśli lewy stryj jest czarny i...
            {
                if (node == node->parent->left)                     // Jeśli węzeł jest lewym synem
                {                                                   // dokonaj obrotu wokół rodzica
                    node = node->parent;                            //
                    RightRotate(node);                              //
                }
                node->parent->color = Node::Color::BLACK;           // Jeśli węzeł jest prawym synem
                node->parent->parent->color = Node::Color::RED;     // dokonaj obrotu wokół dziadka
                LeftRotate(node->parent->parent);                   // i przekoloruj węzły
            }
        }
    }
    Root()->color = Node::Color::BLACK;
}

template<typename T, typename C>
void RedBlackTree<T, C>::RemoveFix(Node* node) const noexcept
{
    while (node != Root() && node->color == Node::Color::BLACK)
    {
        if (node == node->parent->left)                                 // Jeśli węzeł jest lewym dzieckiem i...
        {
            Node* rightSibling = node->parent->right;
            if (rightSibling->color == Node::Color::RED)                // Jeśli brat jest czerwony
            {                                                           // przekoloruj węzły
                rightSibling->color = Node::Color::BLACK;               // i dokonaj obrotu wokół rodzica
                node->parent->color = Node::Color::RED;                 //
                LeftRotate(node->parent);                               //
                rightSibling = node->parent->right;                     //
            }

            if (rightSibling->left->color  == Node::Color::BLACK &&     // Jeśli oboje dzieci brata są czarne
                rightSibling->right->color == Node::Color::BLACK)       // przekoloruj brata
            {                                                           //
                rightSibling->color = Node::Color::RED;                 //
                node = node->parent;                                    //
            }
            else                                                        // Jeśli któreś z dzieci brata jest czerwone
            {
                if (rightSibling->right->color == Node::Color::BLACK)   // Jeśli prawe dziecko brata jest czarne
                {                                                       // przekoloruj węzły
                    rightSibling->left->color = Node::Color::BLACK;     // i dokonaj obrotu wokół brata
                    rightSibling->color = Node::Color::RED;             //
                    RightRotate(rightSibling);                          //
                    rightSibling = node->parent->right;                 //
                }
                rightSibling->color = node->parent->color;              // przekoloruj węzły
                node->parent->color = Node::Color::BLACK;               // i dokonaj obrotu wokół rodzica
                rightSibling->right->color = Node::Color::BLACK;        //
                LeftRotate(node->parent);                               //
                node = Root();                                          //
            }
        }
        else                                                            // Jeśli węzeł jest prawym dzieckiem i...
        {
            Node* leftSibling = node->parent->left;
            if (leftSibling->color == Node::Color::RED)                 // Jeśli brat jest czerwony
            {                                                           // przekoloruj węzły
                leftSibling->color = Node::Color::BLACK;                // i dokonaj obrotu wokół rodzica
                node->parent->color = Node::Color::RED;                 //
                RightRotate(node->parent);                              //
                leftSibling = node->parent->left;                       //
            }

            if (leftSibling->right->color == Node::Color::BLACK &&      // Jeśli oboje dzieci brata są czarne
                leftSibling->left->color  == Node::Color::BLACK)        // przekoloruj brata
            {                                                           //
                leftSibling->color = Node::Color::RED;                  //
                node = node->parent;                                    //
            }
            else                                                        // Jeśli któreś z dzieci brata jest czerwone
            {
                if (leftSibling->left->color == Node::Color::BLACK)     // Jeśli prawe dziecko brata jest czarne
                {                                                       // przekoloruj węzły
                    leftSibling->right->color = Node::Color::BLACK;     // i dokonaj obrotu wokół brata
                    leftSibling->color = Node::Color::RED;              //
                    LeftRotate(leftSibling);                            //
                    leftSibling = node->parent->left;                   //
                }
                leftSibling->color = node->parent->color;               // przekoloruj węzły
                node->parent->color = Node::Color::BLACK;               // i dokonaj obrotu wokół rodzica
                leftSibling->left->color = Node::Color::BLACK;          //
                RightRotate(node->parent);                              //
                node = Root();                                          //
            }
        }
    }
    node->color = Node::Color::BLACK;
}

template<typename T, typename C>
void RedBlackTree<T, C>::MoveSubtree(Node* from, Node* to) const noexcept
{
    if (from->parent == NIL)
    {
        SetRoot(to);
    }
    else if (from == from->parent->left)
    {
        from->parent->left = to;
    }
    else
    {
        from->parent->right = to;
    }
    to->parent = from->parent;
}

template<typename T, typename C>
void RedBlackTree<T, C>::RemoveSubtree(Node* root)
{
    if (root == NIL)
    {
        return;
    }

    RemoveSubtree(root->left);
    RemoveSubtree(root->right);

    delete root;
    root = nullptr;
    size--;
}

template<typename T, typename C>
typename RedBlackTree<T, C>::Node* RedBlackTree<T, C>::CopySubtree(const RedBlackTree& tree, Node* root)
{
    if (root == tree.NIL)
    {
        return NIL;
    }

    Node* newRoot = new Node;
    newRoot->value = root->value;
    newRoot->color = root->color;
    newRoot->left = CopySubtree(tree, root->left);
    newRoot->left->parent = newRoot;

    newRoot->right = CopySubtree(tree, root->right);
    newRoot->right->parent = newRoot;
    return newRoot;
}

template<typename T, typename C>
void RedBlackTree<T, C>::ToString(std::string& result, const std::string& prefix, const Node* node, bool isRight) const
{
    if (node != NIL)
    {
        result += prefix;

        result += (isRight ? Utils::VERTICAL_BAR_RIGHT : Utils::UP_RIGHT);
        result += Utils::HORIZONTAL_BAR;

        result += Utils::Parser::NumberToString(node->value) + "\n";

        ToString(result, prefix + (isRight ? Utils::VERTICAL_BAR : " ") + " ", node->right, true);
        ToString(result, prefix + (isRight ? Utils::VERTICAL_BAR : " ") + " ", node->left, false);
    }
}

template<typename T, typename C>
void RedBlackTree<T, C>::Serialize(std::ostream& os, Node* node) const
{
    if (os.fail())
    {
        return;
    }
    if (node != NIL)
    {
        os << NIL_VALUE << " ";
    }
    else
    {
        os << node->value << " ";
        Serialize(os, node->left);
        Serialize(os, node->right);
    }
}

template<typename T, typename C>
typename RedBlackTree<T, C>::Node* RedBlackTree<T, C>::Deserialize(std::istream& is, Node* node, size_t& sizeOfTree)
{
    if (is.fail() || sizeOfTree == 0)
    {
        return NIL;
    }
    int64_t value;
    is >> value;
    if (value == NIL_VALUE)
    {
        return NIL;
    }
    Node* newNode = MakeNode(static_cast<DataType>(value));
    sizeOfTree--;

    newNode->parent = node;
    newNode->left   = Deserialize(is, newNode, sizeOfTree);
    newNode->right  = Deserialize(is, newNode, sizeOfTree);

    return newNode;
}

template<typename T, typename C>
RedBlackTreeConstIterator<T, C>::RedBlackTreeConstIterator(const RedBlackTree<T, C>* redBlackTree,
                                                           typename RedBlackTree<T, C>::Node* node) noexcept
    : redBlackTree(redBlackTree)
    , node(node)
{ }

template<typename T, typename C>
typename RedBlackTreeConstIterator<T, C>::reference RedBlackTreeConstIterator<T, C>::operator*() const noexcept
{
    return node->value;
}

template<typename T, typename C>
typename RedBlackTreeConstIterator<T, C>::pointer RedBlackTreeConstIterator<T, C>::operator->() const noexcept
{
    return &(**this);
}

template<typename T, typename C>
RedBlackTreeConstIterator<T, C>& RedBlackTreeConstIterator<T, C>::operator++() noexcept
{
    if (node->right == redBlackTree->NIL)
    {
        decltype(node) parent;
        while ((parent = node->parent) != redBlackTree->NIL && node == parent->right)
        {
            node = parent;
        }
        node = parent;
    }
    else
    {
        node = redBlackTree->Min(node->right);
    }

    return *this;
}

template<typename T, typename C>
RedBlackTreeConstIterator<T, C> RedBlackTreeConstIterator<T, C>::operator++(int) noexcept
{
    RedBlackTreeConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

template<typename T, typename C>
RedBlackTreeConstIterator<T, C>& RedBlackTreeConstIterator<T, C>::operator--() noexcept
{
    if (node == redBlackTree->NIL)
    {
        node = redBlackTree->Max(redBlackTree->Root());
    }
    else if (node->left == redBlackTree->NIL)
    {
        decltype(node) parent;
        while ((parent = node->parent) != redBlackTree->NIL && node == parent->left)
        {
            node = parent;
        }
        if (node != redBlackTree->NIL)
        {
            node = parent;
        }
    }
    else
    {
        node = redBlackTree->Max(node->left);
    }

    return *this;
}

template<typename T, typename C>
RedBlackTreeConstIterator<T, C> RedBlackTreeConstIterator<T, C>::operator--(int) noexcept
{
    RedBlackTreeConstIterator tmp = *this;
    --(*this);
    return tmp;
}

template<typename T, typename C>
bool RedBlackTreeConstIterator<T, C>::operator==(const RedBlackTreeConstIterator& rhs) const noexcept
{
    return node == rhs.node;
}

template<typename T, typename C>
bool RedBlackTreeConstIterator<T, C>::operator!=(const RedBlackTreeConstIterator& rhs) const noexcept
{
    return !(*this == rhs);
}

template<typename T, typename C>
typename RedBlackTreeIterator<T, C>::reference RedBlackTreeIterator<T, C>::operator*() const noexcept
{
    return const_cast<reference>(RedBlackTreeConstIterator<T, C>::operator*());
}

template<typename T, typename C>
typename RedBlackTreeIterator<T, C>::pointer RedBlackTreeIterator<T, C>::operator->() const noexcept
{
    return &(**this);
}

template<typename T, typename C>
RedBlackTreeIterator<T, C>& RedBlackTreeIterator<T, C>::operator++() noexcept
{
    RedBlackTreeConstIterator<T, C>::operator++();
    return *this;
}

template<typename T, typename C>
RedBlackTreeIterator<T, C> RedBlackTreeIterator<T, C>::operator++(int) noexcept
{
    RedBlackTreeIterator tmp = *this;
    RedBlackTreeConstIterator<T, C>::operator++();
    return tmp;
}

template<typename T, typename C>
RedBlackTreeIterator<T, C>& RedBlackTreeIterator<T, C>::operator--() noexcept
{
    RedBlackTreeConstIterator<T, C>::operator--();
    return *this;
}

template<typename T, typename C>
RedBlackTreeIterator<T, C> RedBlackTreeIterator<T, C>::operator--(int) noexcept
{
    RedBlackTreeIterator tmp = *this;
    RedBlackTreeConstIterator<T, C>::operator--();
    return tmp;
}