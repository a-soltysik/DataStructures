#include "Container/RedBlackTree/RedBlackTree.h"
#include "Exception/FileException.h"

RedBlackTree::RedBlackTree(std::initializer_list<DataType> initList)
{
    for (const auto& item : initList)
    {
        Insert(item);
    }
}

RedBlackTree::RedBlackTree(const RedBlackTree& rhs)
{
    SetRoot(CopySubtree(rhs, rhs.root()));
    size = rhs.size;
}

RedBlackTree::RedBlackTree(RedBlackTree&& rhs) noexcept
{
    NIL = rhs.NIL;
    size = rhs.size;

    rhs.NIL = nullptr;
    rhs.size = 0u;
}

RedBlackTree& RedBlackTree::operator=(const RedBlackTree& rhs)
{
    Clear();
    SetRoot(CopySubtree(rhs, rhs.root()));
    size = rhs.size;

    return *this;
}

RedBlackTree& RedBlackTree::operator=(RedBlackTree&& rhs) noexcept
{
    Clear();
    NIL = rhs.NIL;
    size = rhs.size;

    rhs.NIL = nullptr;
    rhs.size = 0u;

    return *this;
}

RedBlackTree::~RedBlackTree()
{ 
    Clear();
    delete NIL;
    NIL = nullptr;
}

RedBlackTree::Iterator RedBlackTree::Insert(const DataType& value)
{
    Node* newNode = MakeNode(value);
    Node* parent = NIL;
    Node* iterator = root();

    size++;

    while (iterator != NIL)
    {
        parent = iterator;
        if (newNode->value < iterator->value)
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
    else if (newNode->value < parent->value)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }

    newNode->color = Node::Color::RED;
    InsertFix(newNode);

    return Iterator(this, newNode);
}

bool RedBlackTree::Remove(const DataType& value)
{
    Node* nodeToRemove = Find(value, root());
    if (nodeToRemove == NIL)
    {
        return false;
    }
    Node* successor;
    Node* node = nodeToRemove;
    Node::Color originalColor = node->color;

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

RedBlackTree::ConstIterator RedBlackTree::Find(const DataType& value) const
{
    return ConstIterator(this, Find(value, root()));
}

RedBlackTree::Iterator RedBlackTree::Find(const DataType& value)
{
    return Iterator(this, Find(value, root()));
}

void RedBlackTree::Clear()
{
    if (NIL != nullptr) {
        if (root() != nullptr)
        {
            RemoveSubtree(root());
            
        }
        NIL->left = NIL;
    }
}

RedBlackTree::DataType RedBlackTree::Min() const
{
    return Min(root())->value;
}

RedBlackTree::DataType RedBlackTree::Max() const
{
    return Max(root())->value;
}

size_t RedBlackTree::Size() const
{
    return size;
}

RedBlackTree::Iterator RedBlackTree::begin() noexcept
{
    return Iterator(this, Min(root()));
}

RedBlackTree::Iterator RedBlackTree::end() noexcept
{
    return Iterator(this, NIL);
}

RedBlackTree::ConstIterator RedBlackTree::begin() const noexcept
{
    return ConstIterator(this, Min(root()));
}

RedBlackTree::ConstIterator RedBlackTree::end() const noexcept
{
    return ConstIterator(this, NIL);
}

RedBlackTree::ConstIterator RedBlackTree::cbegin() const noexcept
{
    return ConstIterator(this, Min(root()));
}

RedBlackTree::ConstIterator RedBlackTree::cend() const noexcept
{
    return ConstIterator(this, NIL);
}

bool RedBlackTree::Serialize(std::ostream& os) const
{
    if (!os.good())
    {
        return false;
    }
    Serialize(os, root());
    if (os.good())
    {
        return true;
    }
    return false;
}

std::optional<RedBlackTree> RedBlackTree::Deserialize(std::istream& is)
{
    if (!is.good())
    {
        return {};
    }
    RedBlackTree tree;
    tree.SetRoot(tree.Deserialize(is, tree.NIL));
    if (is.good())
    {
        return tree;
    }
    return {};
}

void RedBlackTree::SetRoot(Node* node) const
{
    NIL->left = node;
    node->parent = NIL;
}

RedBlackTree::Node* RedBlackTree::MakeNode(const DataType& value) const
{
    Node* newNode = new Node(value);

    newNode->left  = NIL;
    newNode->right = NIL;

    return newNode;
}

void RedBlackTree::Print(std::ostream& os, const std::string& prefix, const Node* node, bool isLeft) const
{
    if (node != NIL)
    {
        os << prefix;

        os << (isLeft ? "\xC3\xC4" : "\xC0\xC4");

        os << node->value << "\n";

        Print(os, prefix + (isLeft ? "| " : "  "), node->left, true);
        Print(os, prefix + (isLeft ? "| " : "  "), node->right, false);
    }
}

void RedBlackTree::Serialize(std::ostream& os, Node* node) const
{
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

RedBlackTree::Node* RedBlackTree::Deserialize(std::istream& is, Node* node)
{
    int64_t value;
    is >> value;
    if (value == NIL_VALUE)
    {
        return NIL;
    }
    Node* newNode = MakeNode(static_cast<DataType>(value));

    newNode->parent = node;
    newNode->left   = Deserialize(is, newNode);
    newNode->right  = Deserialize(is, newNode);

    return newNode;
}

RedBlackTree::Node* RedBlackTree::MakeNil()
{
    Node* nil = new Node(0);

    nil->parent = nil;
    nil->left   = nil;
    nil->right  = nil;

    return nil;
}

RedBlackTree::Node* RedBlackTree::root() const
{
    return NIL->left;
}

void RedBlackTree::LeftRotate(Node* node)
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

void RedBlackTree::RightRotate(Node* node)
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

void RedBlackTree::InsertFix(Node* node)
{
    while (node->parent->color == Node::Color::RED)
    {
        if (node->parent == node->parent->parent->left)
        {
            Node* rightUncle = node->parent->parent->right;
            if (rightUncle->color == Node::Color::RED)
            {
                node->parent->color = Node::Color::BLACK;
                rightUncle->color = Node::Color::BLACK;
                node->parent->parent->color = Node::Color::RED;
                node = node->parent->parent;
            }
            else 
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    LeftRotate(node);
                }
                node->parent->color = Node::Color::BLACK;
                node->parent->parent->color = Node::Color::RED;
                RightRotate(node->parent->parent);
            }
        }
        else
        {
            Node* leftUncle = node->parent->parent->left;
            if (leftUncle->color == Node::Color::RED)
            {
                node->parent->color = Node::Color::BLACK;
                leftUncle->color = Node::Color::BLACK;
                node->parent->parent->color = Node::Color::RED;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    RightRotate(node);
                }
                node->parent->color = Node::Color::BLACK;
                node->parent->parent->color = Node::Color::RED;
                LeftRotate(node->parent->parent);
            }
        }
    }
    root()->color = Node::Color::BLACK;
}

void RedBlackTree::MoveSubtree(Node* from, Node* to) const
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

void RedBlackTree::RemoveFix(Node* node)
{
    while (node != root() && node->color != Node::Color::BLACK)
    {
        if (node == node->parent->left)
        {
            Node* rightSibling = node->parent->right;
            if (rightSibling->color == Node::Color::RED)
            {
                rightSibling->color = Node::Color::BLACK;
                node->parent->color = Node::Color::RED;
                LeftRotate(node->parent);
                rightSibling = node->parent->right;
            }

            if (rightSibling->left->color == Node::Color::BLACK && rightSibling->right->color == Node::Color::BLACK)
            {
                rightSibling->color = Node::Color::RED;
                node = node->parent;
            }
            else
            {
                if (rightSibling->right->color == Node::Color::BLACK)
                {
                    rightSibling->left->color = Node::Color::BLACK;
                    rightSibling->color = Node::Color::RED;
                    RightRotate(rightSibling);
                    rightSibling = node->parent->right;
                }
                rightSibling->color = node->parent->color;
                node->parent->color = Node::Color::BLACK;
                rightSibling->right->color = Node::Color::BLACK;
                LeftRotate(node->parent);
                node = root();
            }
        }
        else
        {
            Node* leftSibling = node->parent->left;
            if (leftSibling->color == Node::Color::RED)
            {
                leftSibling->color = Node::Color::BLACK;
                node->parent->color = Node::Color::RED;
                RightRotate(node->parent);
                leftSibling = node->parent->left;
            }

            if (leftSibling->right->color == Node::Color::BLACK && leftSibling->left->color == Node::Color::BLACK)
            {
                leftSibling->color = Node::Color::RED;
                node = node->parent;
            }
            else
            {
                if (leftSibling->left->color == Node::Color::BLACK)
                {
                    leftSibling->right->color = Node::Color::BLACK;
                    leftSibling->color = Node::Color::RED;
                    LeftRotate(leftSibling);
                    leftSibling = node->parent->left;
                }
                leftSibling->color = node->parent->color;
                node->parent->color = Node::Color::BLACK;
                leftSibling->left->color = Node::Color::BLACK;
                RightRotate(node->parent);
                node = root();
            }
        }
    }
    node->color = Node::Color::BLACK;
}

void RedBlackTree::RemoveSubtree(Node* root)
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

RedBlackTree::Node* RedBlackTree::CopySubtree(const RedBlackTree& tree, Node* root)
{
    if (root == tree.NIL)
    {
        return NIL;
    }

    Node* newRoot = new Node(root->value);
    newRoot->color = root->color;
    newRoot->left = CopySubtree(tree, root->left);
    newRoot->left->parent = newRoot;
    
    newRoot->right = CopySubtree(tree, root->right);
    newRoot->right->parent = newRoot;
    return newRoot;
}

RedBlackTree::Node* RedBlackTree::Min(Node* node) const
{
    while (node->left != NIL)
    {
        node = node->left;
    }
    return node;
}

RedBlackTree::Node* RedBlackTree::Max(Node* node) const
{
    while (node->right != NIL)
    {
        node = node->right;
    }
    return node;
}

RedBlackTree::Node* RedBlackTree::Find(const DataType& value, Node* root) const
{
    while (root != NIL)
    {
        if (value == root->value)
        {
            return root;
        }
        if (value > root->value)
        {
            root = root->right;
        }
        else
        {
            root = root->left;
        }
    }
    return NIL;
}

RedBlackTreeConstIterator::RedBlackTreeConstIterator(const RedBlackTree* redBlackTree, RedBlackTree::Node* node) noexcept 
    : node(node)
    , redBlackTree(redBlackTree)
{ }

RedBlackTreeConstIterator::reference RedBlackTreeConstIterator::operator*() const noexcept
{
    return node->value;
}

RedBlackTreeConstIterator::pointer RedBlackTreeConstIterator::operator->() const noexcept
{
    return &(**this);
}

RedBlackTreeConstIterator& RedBlackTreeConstIterator::operator++() noexcept
{
    if (node->right == redBlackTree->NIL)
    {
        RedBlackTree::Node* parent;
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

RedBlackTreeConstIterator RedBlackTreeConstIterator::operator++(int) noexcept
{
    RedBlackTreeConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

RedBlackTreeConstIterator& RedBlackTreeConstIterator::operator--() noexcept
{
    if (node == redBlackTree->NIL)
    {
        node = redBlackTree->Max(redBlackTree->root());
    }
    else if (node->left == redBlackTree->NIL)
    {
        RedBlackTree::Node* parent;
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

RedBlackTreeConstIterator RedBlackTreeConstIterator::operator--(int) noexcept
{
    RedBlackTreeConstIterator tmp = *this;
    --(*this);
    return tmp;
}

bool RedBlackTreeConstIterator::operator==(const RedBlackTreeConstIterator& rhs) const noexcept
{
    return node == rhs.node;
}

bool RedBlackTreeConstIterator::operator!=(const RedBlackTreeConstIterator& rhs) const noexcept
{
    return !(*this == rhs);
}

RedBlackTreeIterator::reference RedBlackTreeIterator::operator*() const noexcept
{
    return const_cast<reference>(RedBlackTreeConstIterator::operator*());
}

RedBlackTreeIterator::pointer RedBlackTreeIterator::operator->() const noexcept
{
    return &(**this);
}

RedBlackTreeIterator& RedBlackTreeIterator::operator++() noexcept
{
    RedBlackTreeConstIterator::operator++();
    return *this;
}

RedBlackTreeIterator RedBlackTreeIterator::operator++(int) noexcept
{
    RedBlackTreeIterator tmp = *this;
    RedBlackTreeConstIterator::operator++();
    return tmp;
}

RedBlackTreeIterator& RedBlackTreeIterator::operator--() noexcept
{
    RedBlackTreeConstIterator::operator--();
    return *this;
}

RedBlackTreeIterator RedBlackTreeIterator::operator--(int) noexcept
{
    RedBlackTreeIterator tmp = *this;
    RedBlackTreeConstIterator::operator--();
    return tmp;
}

std::ostream& operator<<(std::ostream& os, const RedBlackTree& tree)
{
    tree.Print(os, "", tree.root(), false);
    return os;
}
