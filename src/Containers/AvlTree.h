#pragma once

#include "Utils/Utils.h"

#include <istream>

template<typename T, typename C>
struct AvlTreeIterator;

template<typename T, typename C>
struct AvlTreeConstIterator;

template<typename T, typename C = Utils::Less<T>>
class AvlTree
{
public:
    friend struct AvlTreeIterator<T, C>;
    friend struct AvlTreeConstIterator<T, C>;

    using DataType = T;
    using Comparator = C;
    using Iterator = AvlTreeIterator<T, C>;
    using ConstIterator = AvlTreeConstIterator<T, C>;

    [[nodiscard]] static constexpr const char* ClassName() { return "AvlTree"; }

    explicit AvlTree(const Comparator& comparator = Comparator());
    AvlTree(std::initializer_list<DataType> initList, const Comparator& comparator = Comparator());
    AvlTree(const AvlTree& rhs);
    AvlTree(AvlTree&& rhs) noexcept;
    AvlTree& operator=(const AvlTree& rhs);
    AvlTree& operator=(AvlTree&& rhs) noexcept;
    ~AvlTree();

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
    friend std::ostream& operator<<(std::ostream& os, const AvlTree<U, V>& tree);

    template<typename U, typename V>
    friend std::istream& operator>>(std::istream& is, AvlTree<U, V>& tree);

private:
    using Height = int8_t;

    struct Node
    {
        Height height;
        DataType value;

        Node* left;
        Node* right;
        Node* parent;

        [[nodiscard]] Height BalanceFactor() const noexcept;
        void UpdateHeight() noexcept;
    };

    inline static constexpr int64_t NIL_VALUE = -1;

    Node* LeftRotate(Node* node) const noexcept;
    Node* RightRotate(Node* node) const noexcept;

    [[nodiscard]] static Node* MakeNil();
    [[nodiscard]] Node* MakeNode(const DataType& value) const;

    void SetRoot(Node* node) const noexcept;
    [[nodiscard]] Node* Root() const noexcept;

    [[nodiscard]] Node* Min(Node* node) const noexcept;
    [[nodiscard]] Node* Max(Node* node) const noexcept;
    [[nodiscard]] Node* Find(const DataType& value, Node* root) const noexcept;

    void InsertFix(Node* node) const noexcept;
    void RemoveFix(Node* node) const noexcept;

    void RemoveSubtree(Node* root);
    [[nodiscard]] Node* CopySubtree(const AvlTree& tree, Node* root);

    [[nodiscard]] Node* RemoveNodeWithoutChildren(Node* node) const;
    [[nodiscard]] Node* RemoveNodeWithOneChild(Node* node) const;
    [[nodiscard]] Node* RemoveNodeWithTwoChildren(Node* node) const;

    void ToString(std::string& result, const std::string& prefix, const Node* node, bool isRight) const;
    void Serialize(std::ostream& os, Node* node) const;
    [[nodiscard]] Node* Deserialize(std::istream& is, Node* node, size_t& sizeOfTree);

    Comparator comparator;
    Node* NIL = MakeNil();
    size_t size = 0;
};

template<typename T, typename C>
struct AvlTreeConstIterator
{
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = typename AvlTree<T, C>::DataType;
    using pointer = const value_type*;
    using reference = const value_type&;

    AvlTreeConstIterator() = default;
    AvlTreeConstIterator(const AvlTree<T, C>* avlTree, typename AvlTree<T, C>::Node* node) noexcept;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    AvlTreeConstIterator& operator++() noexcept;
    AvlTreeConstIterator operator++(int) noexcept;
    AvlTreeConstIterator& operator--() noexcept;
    AvlTreeConstIterator operator--(int) noexcept;

    [[nodiscard]] bool operator==(const AvlTreeConstIterator& rhs) const noexcept;
    [[nodiscard]] bool operator!=(const AvlTreeConstIterator& rhs) const noexcept;

protected:
    const AvlTree<T, C>* avlTree;
    typename AvlTree<T, C>::Node* node;
};

template<typename T, typename C>
struct AvlTreeIterator : public AvlTreeConstIterator<T, C>
{
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = typename AvlTree<T, C>::DataType;
    using pointer = value_type*;
    using reference = value_type&;

    using AvlTreeConstIterator<T, C>::AvlTreeConstIterator;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    AvlTreeIterator& operator++() noexcept;
    AvlTreeIterator operator++(int) noexcept;
    AvlTreeIterator& operator--() noexcept;
    AvlTreeIterator operator--(int) noexcept;
};

template<typename T, typename C>
AvlTree<T, C>::AvlTree(const Comparator& comparator)
    : comparator(comparator)
{ }

template<typename T, typename C>
AvlTree<T, C>::AvlTree(std::initializer_list<DataType> initList, const Comparator& comparator)
    : comparator(comparator)
{
    for (const auto& item: initList)
    {
        Insert(item);
    }
}

template<typename T, typename C>
AvlTree<T, C>::AvlTree(const AvlTree& rhs)
{
    SetRoot(CopySubtree(rhs, rhs.Root()));
    size = rhs.size;
}

template<typename T, typename C>
AvlTree<T, C>::AvlTree(AvlTree&& rhs) noexcept
{
    NIL = rhs.NIL;
    size = rhs.size;

    rhs.NIL = nullptr;
    rhs.size = 0u;
}

template<typename T, typename C>
AvlTree<T, C>& AvlTree<T, C>::operator=(const AvlTree& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    Clear();
    SetRoot(CopySubtree(rhs, rhs.Root()));
    size = rhs.size;

    return *this;
}

template<typename T, typename C>
AvlTree<T, C>& AvlTree<T, C>::operator=(AvlTree&& rhs) noexcept
{
    Clear();
    NIL = rhs.NIL;
    size = rhs.size;

    rhs.NIL = nullptr;
    rhs.size = 0u;

    return *this;
}

template<typename T, typename C>
AvlTree<T, C>::~AvlTree()
{
    Clear();
    delete NIL;
    NIL = nullptr;
}

template<typename T, typename C>
typename AvlTree<T, C>::Iterator AvlTree<T, C>::Insert(const DataType& value)
{
    Node* newNode = MakeNode(value);
    Node* parent = NIL;
    Node* iterator = Root();

    size++;

    while (iterator != NIL)
    {
        parent = iterator;

        if (comparator(value, iterator->value))
        {
            iterator = iterator->left;
        }
        else
        {
            iterator = iterator->right;
        }
    }
    if (comparator(value, parent->value))
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }
    newNode->parent = parent;

    InsertFix(newNode);

    return {this, newNode};
}

template<typename T, typename C>
bool AvlTree<T, C>::Remove(const DataType& value)
{
    Node* nodeToRemove = Find(value, Root());
    if (nodeToRemove == NIL)
    {
        return false;
    }

    size--;

    Node* successor;
    if (nodeToRemove->left == NIL && nodeToRemove->right == NIL)
    {
        successor = RemoveNodeWithoutChildren(nodeToRemove);
    }

    else if (nodeToRemove->left == NIL || nodeToRemove->right == NIL)
    {
        successor = RemoveNodeWithOneChild(nodeToRemove);
    }

    else
    {
        successor = RemoveNodeWithTwoChildren(nodeToRemove);
    }

    RemoveFix(successor);

    return true;
}

template<typename T, typename C>
void AvlTree<T, C>::Clear()
{
    if (NIL != nullptr)
    {
        RemoveSubtree(Root());
        NIL->left = NIL;
    }
}

template<typename T, typename C>
typename AvlTree<T, C>::ConstIterator AvlTree<T, C>::Find(const DataType& value) const noexcept
{
    return {this, Find(value, Root())};
}

template<typename T, typename C>
typename AvlTree<T, C>::Iterator AvlTree<T, C>::Find(const DataType& value) noexcept
{
    return {this, Find(value, Root())};
}

template<typename T, typename C>
const typename AvlTree<T, C>::DataType& AvlTree<T, C>::Min() const noexcept
{
    return Min(Root())->value;
}

template<typename T, typename C>
const typename AvlTree<T, C>::DataType& AvlTree<T, C>::Max() const noexcept
{
    return Max(Root())->value;
}

template<typename T, typename C>
size_t AvlTree<T, C>::Size() const noexcept
{
    return size;
}

template<typename T, typename C>
typename AvlTree<T, C>::Iterator AvlTree<T, C>::begin() noexcept
{
    return {this, Min(Root())};
}

template<typename T, typename C>
typename AvlTree<T, C>::Iterator AvlTree<T, C>::end() noexcept
{
    return {this, NIL};
}

template<typename T, typename C>
typename AvlTree<T, C>::ConstIterator AvlTree<T, C>::begin() const noexcept
{
    return {this, Min(Root())};
}

template<typename T, typename C>
typename AvlTree<T, C>::ConstIterator AvlTree<T, C>::end() const noexcept
{
    return {this, NIL};
}

template<typename T, typename C>
typename AvlTree<T, C>::ConstIterator AvlTree<T, C>::cbegin() const noexcept
{
    return {this, Min(Root())};
}

template<typename T, typename C>
typename AvlTree<T, C>::ConstIterator AvlTree<T, C>::cend() const noexcept
{
    return {this, NIL};
}

template<typename T, typename C>
std::string AvlTree<T, C>::ToString() const
{
    std::string result = "\n";
    ToString(result, "", Root(), false);
    return result;
}

template<typename T, typename C>
std::ostream& operator<<(std::ostream& os, const AvlTree<T, C>& tree)
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
std::istream& operator>>(std::istream& is, AvlTree<T, C>& tree)
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
typename AvlTree<T, C>::Height AvlTree<T, C>::Node::BalanceFactor() const noexcept
{
    return static_cast<Height>(left->height - right->height);
}

template<typename T, typename C>
void AvlTree<T, C>::Node::UpdateHeight() noexcept
{
    height = static_cast<Height>(1 + Utils::Max(left->height, right->height));
}

template<typename T, typename C>
typename AvlTree<T, C>::Node* AvlTree<T, C>::LeftRotate(Node* node) const noexcept
{
    Node* child = node->right;
    Node* grandChild = child->left;

    child->left = node;
    child->parent = node->parent;

    if (node->parent->left == node)
    {
        child->parent->left = child;
    }
    else
    {
        child->parent->right = child;
    }

    node->right = grandChild;
    node->parent = child;

    if (grandChild != NIL)
    {
        grandChild->parent = node;
    }

    node->UpdateHeight();
    child->UpdateHeight();

    return child;
}

template<typename T, typename C>
typename AvlTree<T, C>::Node* AvlTree<T, C>::RightRotate(Node* node) const noexcept
{
    Node* child = node->left;
    Node* grandChild = child->right;

    child->right = node;
    child->parent = node->parent;
    if (node->parent->left == node)
    {
        child->parent->left = child;
    }
    else
    {
        child->parent->right = child;
    }
    node->left = grandChild;
    node->parent = child;

    if (grandChild != NIL)
    {
        grandChild->parent = node;
    }

    node->UpdateHeight();
    child->UpdateHeight();

    return child;
}

template<typename T, typename C>
typename AvlTree<T, C>::Node* AvlTree<T, C>::MakeNil()
{
    Node* nil = new Node {-1,           // height
                          DataType(),   // value
                          nullptr,      // left
                          nullptr,      // right
                          nullptr};     // parent

    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;

    return nil;
}

template<typename T, typename C>
typename AvlTree<T, C>::Node* AvlTree<T, C>::MakeNode(const DataType& value) const
{
    Node* node = new Node {0,       // height
                           value,   // value
                           NIL,     // left
                           NIL,     // right
                           NIL};    // parent

    return node;
}

template<typename T, typename C>
void AvlTree<T, C>::SetRoot(AvlTree::Node* node) const noexcept
{
    NIL->left = node;
    node->parent = NIL;
}

template<typename T, typename C>
typename AvlTree<T, C>::Node* AvlTree<T, C>::Root() const noexcept
{
    return NIL->left;
}

template<typename T, typename C>
typename AvlTree<T, C>::Node* AvlTree<T, C>::Min(AvlTree::Node* node) const noexcept
{
    while (node->left != NIL)
    {
        node = node->left;
    }
    return node;
}

template<typename T, typename C>
typename AvlTree<T, C>::Node* AvlTree<T, C>::Max(AvlTree::Node* node) const noexcept
{
    while (node->right != NIL)
    {
        node = node->right;
    }
    return node;
}

template<typename T, typename C>
typename AvlTree<T, C>::Node* AvlTree<T, C>::Find(const DataType& value, Node* root) const noexcept
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
void AvlTree<T, C>::InsertFix(Node* node) const noexcept
{
    Node* parent = node->parent;
    Node* child = node;
    DataType value = node->value;

    while (parent != NIL)
    {
        parent->UpdateHeight();
        Height balance = parent->BalanceFactor();

        if (balance > 1)                                    // Jeżeli ciężar jest lewej stronie
        {
            if (!comparator(parent->left->value, value))    // Jeżeli wartość jest mniejsza bądź równa
            {                                               // wartości lewego dziecka rodzica
                parent = RightRotate(parent);               // dokonaj rotacji RR na rodzicu
            }
            else                                            // W przeciwnym przypadku
            {                                               // Dokonaj rotacji LR
                parent->left = LeftRotate(parent->left);    //
                parent = RightRotate(parent);               //
            }
        }
        else if (balance < -1)                              // Jeżeli ciężar jest po prawej stronie
        {
            if (comparator(value, parent->right->value))    // Jeżeli wartość jest mniejsza od
            {                                               // wartości prawego dziecka rodzica
                parent->right = RightRotate(parent->right); // dokonaj rotacji RL
                parent = LeftRotate(parent);                //
            }
            else                                            // W przeciwnym wypadku
            {                                               // dokonaj rotacji LL
                parent = LeftRotate(parent);                //
            }                                               //
        }

        child = parent;
        parent = parent->parent;
    }
    SetRoot(child);
}

template<typename T, typename C>
void AvlTree<T, C>::RemoveFix(Node* node) const noexcept
{
    Node* child = Root();

    while (node != NIL)
    {
        node->UpdateHeight();
        Height balance = node->BalanceFactor();

        if (balance > 1)                                // Jeżeli ciężar jest lewej stronie
        {
            if (node->left->BalanceFactor() >= 0)       // Jeżeli ciężar lewego dziecka węzła
            {                                           // jest po lewej stronie lub go nie ma
                node = RightRotate(node);               // dokonaj rotacji RR
            }
            else                                        // W przeciwnym przypadku
            {                                           // dokonaj rotacji LR
                node->left = LeftRotate(node->left);    //
                node = RightRotate(node);               //
            }
        }
        else if (balance < -1)                          // Jeżeli ciężar jest po prawej stronie
        {
            if (node->right->BalanceFactor() <= 0)      // Jeżeli ciężar prawego dziecka węzła
            {                                           // jest po prawej stronie lub go nie ma
                node = LeftRotate(node);                // dokonaj rotacji LL
            }
            else                                        // W przeciwnym przypadku
            {                                           // dokonaj rotacji RL
                node->right = RightRotate(node->right); //
                node = LeftRotate(node);                //
            }
        }
        child = node;
        node = node->parent;
    }
    SetRoot(child);
}

template<typename T, typename C>
void AvlTree<T, C>::RemoveSubtree(AvlTree::Node* root)
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
typename AvlTree<T, C>::Node* AvlTree<T, C>::CopySubtree(const AvlTree& tree, AvlTree::Node* root)
{
    if (root == tree.NIL)
    {
        return NIL;
    }

    Node* newRoot = new Node {};
    newRoot->value = root->value;
    newRoot->height = root->height;

    newRoot->left = CopySubtree(tree, root->left);
    newRoot->left->parent = newRoot;

    newRoot->right = CopySubtree(tree, root->right);
    newRoot->right->parent = newRoot;

    return newRoot;
}

template<typename T, typename C>
typename AvlTree<T, C>::Node* AvlTree<T, C>::RemoveNodeWithoutChildren(Node* nodeToRemove) const
{
    Node* successor = nodeToRemove->parent;

    if (nodeToRemove->parent->left == nodeToRemove)
    {
        nodeToRemove->parent->left = NIL;
    }
    else
    {
        nodeToRemove->parent->right = NIL;
    }

    delete nodeToRemove;
    nodeToRemove = nullptr;

    return successor;
}

template<typename T, typename C>
typename AvlTree<T, C>::Node* AvlTree<T, C>::RemoveNodeWithOneChild(Node* nodeToRemove) const
{
    Node* successor = nodeToRemove->left != NIL ? nodeToRemove->left : nodeToRemove->right;
    successor->parent = nodeToRemove->parent;

    if (nodeToRemove->parent->left == nodeToRemove)
    {
        successor->parent->left = successor;
    }
    else
    {
        successor->parent->right = successor;
    }

    delete nodeToRemove;
    nodeToRemove = nullptr;

    return successor;
}

template<typename T, typename C>
typename AvlTree<T, C>::Node* AvlTree<T, C>::RemoveNodeWithTwoChildren(Node* node) const
{
    Node* successor = Max(node->left);
    Utils::Swap(successor->value, node->value);

    if (successor->left == NIL && successor->right == NIL)
    {
        successor = RemoveNodeWithoutChildren(successor);
    }

    else if (successor->left == NIL || successor->right == NIL)
    {
        successor = RemoveNodeWithOneChild(successor);
    }
    return successor;
}

template<typename T, typename C>
void AvlTree<T, C>::ToString(std::string& result, const std::string& prefix, const Node* node, bool isRight) const
{
    if (node != NIL)
    {
        result += prefix;

        result += (isRight ? Utils::VERTICAL_BAR_RIGHT : Utils::HALF_VERTICAL_BAR_RIGHT);
        result += Utils::HORIZONTAL_BAR;

        result += Utils::Parser::NumberToString(node->value) + "\n";

        ToString(result, prefix + (isRight ? Utils::VERTICAL_BAR : " ") + " ", node->right, true);
        ToString(result, prefix + (isRight ? Utils::VERTICAL_BAR : " ") + " ", node->left, false);
    }
}

template<typename T, typename C>
void AvlTree<T, C>::Serialize(std::ostream& os, AvlTree::Node* node) const
{
    if (os.fail())
    {
        return;
    }
    if (node == NIL)
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
typename AvlTree<T, C>::Node* AvlTree<T, C>::Deserialize(std::istream& is, AvlTree::Node* node, size_t& sizeOfTree)
{
    if (is.fail())
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
AvlTreeConstIterator<T, C>::AvlTreeConstIterator(const AvlTree<T, C>* avlTree, typename AvlTree<T, C>::Node* node) noexcept
    : avlTree(avlTree)
    , node(node)
{ }

template<typename T, typename C>
typename AvlTreeConstIterator<T, C>::reference AvlTreeConstIterator<T, C>::operator*() const noexcept
{
    return node->value;
}

template<typename T, typename C>
typename AvlTreeConstIterator<T, C>::pointer AvlTreeConstIterator<T, C>::operator->() const noexcept
{
    return &(**this);
}

template<typename T, typename C>
AvlTreeConstIterator<T, C>& AvlTreeConstIterator<T, C>::operator++() noexcept
{
    if (node->right == avlTree->NIL)
    {
        decltype(node) parent;
        while ((parent = node->parent) != avlTree->NIL && node == parent->right)
        {
            node = parent;
        }
        node = parent;
    }
    else
    {
        node = avlTree->Min(node->right);
    }

    return *this;
}

template<typename T, typename C>
AvlTreeConstIterator<T, C> AvlTreeConstIterator<T, C>::operator++(int) noexcept
{
    AvlTreeConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

template<typename T, typename C>
AvlTreeConstIterator<T, C>& AvlTreeConstIterator<T, C>::operator--() noexcept
{
    if (node == avlTree->NIL)
    {
        node = avlTree->Max(avlTree->Root());
    }
    else if (node->left == avlTree->NIL)
    {
        decltype(node) parent;
        while ((parent = node->parent) != avlTree->NIL && node == parent->left)
        {
            node = parent;
        }
        if (node != avlTree->NIL)
        {
            node = parent;
        }
    }
    else
    {
        node = avlTree->Max(node->left);
    }

    return *this;
}

template<typename T, typename C>
AvlTreeConstIterator<T, C> AvlTreeConstIterator<T, C>::operator--(int) noexcept
{
    AvlTreeConstIterator tmp = *this;
    --(*this);
    return tmp;
}

template<typename T, typename C>
bool AvlTreeConstIterator<T, C>::operator==(const AvlTreeConstIterator& rhs) const noexcept
{
    return node == rhs.node;
}

template<typename T, typename C>
bool AvlTreeConstIterator<T, C>::operator!=(const AvlTreeConstIterator& rhs) const noexcept
{
    return !(*this == rhs);
}

template<typename T, typename C>
typename AvlTreeIterator<T, C>::reference AvlTreeIterator<T, C>::operator*() const noexcept
{
    return const_cast<reference>(AvlTreeConstIterator<T, C>::operator*());
}

template<typename T, typename C>
typename AvlTreeIterator<T, C>::pointer AvlTreeIterator<T, C>::operator->() const noexcept
{
    return &(**this);
}

template<typename T, typename C>
AvlTreeIterator<T, C>& AvlTreeIterator<T, C>::operator++() noexcept
{
    AvlTreeConstIterator<T, C>::operator++();
    return *this;
}

template<typename T, typename C>
AvlTreeIterator<T, C> AvlTreeIterator<T, C>::operator++(int) noexcept
{
    AvlTreeIterator tmp = *this;
    AvlTreeConstIterator<T, C>::operator++();
    return tmp;
}

template<typename T, typename C>
AvlTreeIterator<T, C>& AvlTreeIterator<T, C>::operator--() noexcept
{
    AvlTreeConstIterator<T, C>::operator--();
    return *this;
}

template<typename T, typename C>
AvlTreeIterator<T, C> AvlTreeIterator<T, C>::operator--(int) noexcept
{
    AvlTreeIterator tmp = *this;
    AvlTreeConstIterator<T, C>::operator--();
    return tmp;
}