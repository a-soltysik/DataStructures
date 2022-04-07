#include "Container/AvlTree/AvlTree.h"

#include "Utils/Utils.h"

AvlTree::AvlTree(std::initializer_list <DataType> initList)
{
    for (const auto& item: initList)
    {
        Insert(item);
    }
}

AvlTree::AvlTree(const AvlTree& rhs)
{
    SetRoot(CopySubtree(rhs, rhs.Root()));
    size = rhs.size;
}

AvlTree::AvlTree(AvlTree&& rhs) noexcept
{
    NIL = rhs.NIL;
    size = rhs.size;

    rhs.NIL = nullptr;
    rhs.size = 0u;
}

AvlTree& AvlTree::operator=(const AvlTree& rhs)
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

AvlTree& AvlTree::operator=(AvlTree&& rhs) noexcept
{
    Clear();
    NIL = rhs.NIL;
    size = rhs.size;

    rhs.NIL = nullptr;
    rhs.size = 0u;

    return *this;
}

AvlTree::~AvlTree()
{
    Clear();
    delete NIL;
    NIL = nullptr;
}

AvlTree::Iterator AvlTree::Insert(DataType value)
{
    Node* newNode = MakeNode(value);
    Node* parent = NIL;
    Node* iterator = Root();

    size++;

    while (iterator != NIL)
    {
        parent = iterator;

        if (value < iterator->value)
        {
            iterator = iterator->left;
        }
        else
        {
            iterator = iterator->right;
        }
    }
    if (value < parent->value)
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

bool AvlTree::Remove(DataType value)
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

void AvlTree::Clear()
{
    if (NIL != nullptr)
    {
        RemoveSubtree(Root());
        NIL->left = NIL;
    }
}

AvlTree::ConstIterator AvlTree::Find(DataType value) const
{
    return {this, Find(value, Root())};
}

AvlTree::Iterator AvlTree::Find(DataType value)
{
    return {this, Find(value, Root())};
}

AvlTree::DataType AvlTree::Min() const
{
    return Min(Root())->value;
}

AvlTree::DataType AvlTree::Max() const
{
    return Max(Root())->value;
}

size_t AvlTree::Size() const noexcept
{
    return size;
}

AvlTree::Iterator AvlTree::begin() noexcept
{
    return {this, Min(Root())};
}

AvlTree::Iterator AvlTree::end() noexcept
{
    return {this, NIL};
}

AvlTree::ConstIterator AvlTree::begin() const noexcept
{
    return {this, Min(Root())};
}

AvlTree::ConstIterator AvlTree::end() const noexcept
{
    return {this, NIL};
}

AvlTree::ConstIterator AvlTree::cbegin() const noexcept
{
    return {this, Min(Root())};
}

AvlTree::ConstIterator AvlTree::cend() const noexcept
{
    return {this, NIL};
}

std::string AvlTree::ToString() const
{
    std::string result = "\n";
    ToString(result, "", Root(), false);
    return result;
}

std::ostream& operator<<(std::ostream& os, const AvlTree& tree)
{
    if (!os.good())
    {
        return os;
    }
    os << tree.Size() << "\n";
    tree.Serialize(os, tree.Root());
    return os;
}

std::istream& operator>>(std::istream& is, AvlTree& tree)
{
    if (!is.good())
    {
        return is;
    }
    size_t size;
    is >> size;
    tree.SetRoot(tree.Deserialize(is, tree.NIL, size));
    return is;
}

AvlTree::Height AvlTree::Node::BalanceFactor() const noexcept
{
    return static_cast<Height>(left->height - right->height);
}

void AvlTree::Node::UpdateHeight() noexcept
{
    height = static_cast<Height>(1 + Utils::Max(left->height, right->height));
}

AvlTree::Node* AvlTree::LeftRotate(Node* node) const noexcept
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

AvlTree::Node* AvlTree::RightRotate(Node* node) const noexcept
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

AvlTree::Node* AvlTree::MakeNil()
{
    Node* nil = new Node {};

    nil->height = -1;
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;

    return nil;
}

AvlTree::Node* AvlTree::MakeNode(DataType value) const
{
    Node* node = new Node {};

    node->height = 0;
    node->value = value;
    node->left = NIL;
    node->right = NIL;

    return node;
}

void AvlTree::SetRoot(AvlTree::Node* node) const noexcept
{
    NIL->left = node;
    node->parent = NIL;
}

AvlTree::Node* AvlTree::Root() const noexcept
{
    return NIL->left;
}

AvlTree::Node* AvlTree::Min(AvlTree::Node* node) const noexcept
{
    while (node->left != NIL)
    {
        node = node->left;
    }
    return node;
}

AvlTree::Node* AvlTree::Max(AvlTree::Node* node) const noexcept
{
    while (node->right != NIL)
    {
        node = node->right;
    }
    return node;
}

AvlTree::Node* AvlTree::Find(const DataType& value, Node* root) const noexcept
{
    while (root != NIL)
    {
        if (value > root->value)
        {
            root = root->right;
        }
        else if (value < root->value)
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

void AvlTree::InsertFix(Node* node) const noexcept
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
            if (value <= parent->left->value)               // Jeżeli wartość jest mniejsza bądź równa
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
            if (value < parent->right->value)               // Jeżeli wartość jest mniejsza od
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

void AvlTree::RemoveFix(Node* node) const noexcept
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

void AvlTree::RemoveSubtree(AvlTree::Node* root)
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

AvlTree::Node* AvlTree::CopySubtree(const AvlTree& tree, AvlTree::Node* root)
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

AvlTree::Node* AvlTree::RemoveNodeWithoutChildren(Node* nodeToRemove) const
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

AvlTree::Node* AvlTree::RemoveNodeWithOneChild(Node* nodeToRemove) const
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

AvlTree::Node* AvlTree::RemoveNodeWithTwoChildren(Node* node) const
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

void AvlTree::ToString(std::string& result, const std::string& prefix, const Node* node, bool isRight) const
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

void AvlTree::Serialize(std::ostream& os, AvlTree::Node* node) const
{
    if (!os.good())
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

AvlTree::Node* AvlTree::Deserialize(std::istream& is, AvlTree::Node* node, size_t& sizeOfTree)
{
    if (!is.good())
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

AvlTreeConstIterator::AvlTreeConstIterator(const AvlTree* avlTree, AvlTree::Node* node) noexcept
    : avlTree(avlTree)
    , node(node) { }

AvlTreeConstIterator::reference AvlTreeConstIterator::operator*() const noexcept
{
    return node->value;
}

AvlTreeConstIterator::pointer AvlTreeConstIterator::operator->() const noexcept
{
    return &(**this);
}

AvlTreeConstIterator& AvlTreeConstIterator::operator++() noexcept
{
    if (node->right == avlTree->NIL)
    {
        AvlTree::Node* parent;
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

AvlTreeConstIterator AvlTreeConstIterator::operator++(int) noexcept
{
    AvlTreeConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

AvlTreeConstIterator& AvlTreeConstIterator::operator--() noexcept
{
    if (node == avlTree->NIL)
    {
        node = avlTree->Max(avlTree->Root());
    }
    else if (node->left == avlTree->NIL)
    {
        AvlTree::Node* parent;
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

AvlTreeConstIterator AvlTreeConstIterator::operator--(int) noexcept
{
    AvlTreeConstIterator tmp = *this;
    --(*this);
    return tmp;
}

bool AvlTreeConstIterator::operator==(const AvlTreeConstIterator& rhs) const noexcept
{
    return node == rhs.node;
}

bool AvlTreeConstIterator::operator!=(const AvlTreeConstIterator& rhs) const noexcept
{
    return !(*this == rhs);
}

AvlTreeIterator::reference AvlTreeIterator::operator*() const noexcept
{
    return const_cast<reference>(AvlTreeConstIterator::operator*());
}

AvlTreeIterator::pointer AvlTreeIterator::operator->() const noexcept
{
    return &(**this);
}

AvlTreeIterator& AvlTreeIterator::operator++() noexcept
{
    AvlTreeConstIterator::operator++();
    return *this;
}

AvlTreeIterator AvlTreeIterator::operator++(int) noexcept
{
    AvlTreeIterator tmp = *this;
    AvlTreeConstIterator::operator++();
    return tmp;
}

AvlTreeIterator& AvlTreeIterator::operator--() noexcept
{
    AvlTreeConstIterator::operator--();
    return *this;
}

AvlTreeIterator AvlTreeIterator::operator--(int) noexcept
{
    AvlTreeIterator tmp = *this;
    AvlTreeConstIterator::operator--();
    return tmp;
}