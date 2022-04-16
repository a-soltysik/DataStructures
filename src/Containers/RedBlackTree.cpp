#include "Containers/RedBlackTree.h"
#include "Utils/Utils.h"

RedBlackTree::RedBlackTree(std::initializer_list<DataType> initList)
{
    for (const auto& item: initList)
    {
        Insert(item);
    }
}

RedBlackTree::RedBlackTree(const RedBlackTree& rhs)
{
    SetRoot(CopySubtree(rhs, rhs.Root()));
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
    if (this == &rhs)
    {
        return *this;
    }
    Clear();
    SetRoot(CopySubtree(rhs, rhs.Root()));
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

RedBlackTree::Iterator RedBlackTree::Insert(DataType value)
{
    Node* newNode = MakeNode(value);
    Node* parent = NIL;
    Node* iterator = Root();

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

    return {this, newNode};
}

bool RedBlackTree::Remove(DataType value)
{
    Node* nodeToRemove = Find(value, Root());
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

void RedBlackTree::Clear()
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

RedBlackTree::ConstIterator RedBlackTree::Find(DataType value) const
{
    return {this, Find(value, Root())};
}

RedBlackTree::Iterator RedBlackTree::Find(DataType value)
{
    return {this, Find(value, Root())};
}

RedBlackTree::DataType RedBlackTree::Min() const
{
    return Min(Root())->value;
}

RedBlackTree::DataType RedBlackTree::Max() const
{
    return Max(Root())->value;
}

size_t RedBlackTree::Size() const
{
    return size;
}

RedBlackTree::Iterator RedBlackTree::begin() noexcept
{
    return {this, Min(Root())};
}

RedBlackTree::Iterator RedBlackTree::end() noexcept
{
    return {this, NIL};
}

RedBlackTree::ConstIterator RedBlackTree::begin() const noexcept
{
    return {this, Min(Root())};
}

RedBlackTree::ConstIterator RedBlackTree::end() const noexcept
{
    return {this, NIL};
}

RedBlackTree::ConstIterator RedBlackTree::cbegin() const noexcept
{
    return {this, Min(Root())};
}

RedBlackTree::ConstIterator RedBlackTree::cend() const noexcept
{
    return {this, NIL};
}

std::string RedBlackTree::ToString() const
{
    std::string result;
    ToString(result, "", Root(), false);
    return result;
}

std::ostream& operator<<(std::ostream& os, const RedBlackTree& tree)
{
    if (os.fail())
    {
        return os;
    }
    os << tree.Size() << "\n";
    tree.Serialize(os, tree.Root());
    return os;
}

std::istream& operator>>(std::istream& is, RedBlackTree& tree)
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

RedBlackTree::Node* RedBlackTree::MakeNil()
{
    Node* nil = new Node {};

    nil->color = Node::Color::BLACK;
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;

    return nil;
}


RedBlackTree::Node* RedBlackTree::MakeNode(const DataType& value) const
{
    Node* newNode = new Node {};

    newNode->color = Node::Color::BLACK;
    newNode->value = value;
    newNode->left = NIL;
    newNode->right = NIL;

    return newNode;
}

void RedBlackTree::LeftRotate(Node* node) const noexcept
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

void RedBlackTree::RightRotate(Node* node) const noexcept
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

void RedBlackTree::SetRoot(Node* node) const noexcept
{
    NIL->left = node;
    node->parent = NIL;
}

RedBlackTree::Node* RedBlackTree::Root() const noexcept
{
    return NIL->left;
}

RedBlackTree::Node* RedBlackTree::Min(Node* node) const noexcept
{
    while (node->left != NIL)
    {
        node = node->left;
    }
    return node;
}

RedBlackTree::Node* RedBlackTree::Max(Node* node) const noexcept
{
    while (node->right != NIL)
    {
        node = node->right;
    }
    return node;
}

RedBlackTree::Node* RedBlackTree::Find(const DataType& value, Node* root) const noexcept
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

void RedBlackTree::InsertFix(Node* node) const noexcept
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

void RedBlackTree::RemoveFix(Node* node) const noexcept
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

    Node* newRoot = new Node;
    newRoot->value = root->value;
    newRoot->color = root->color;
    newRoot->left = CopySubtree(tree, root->left);
    newRoot->left->parent = newRoot;

    newRoot->right = CopySubtree(tree, root->right);
    newRoot->right->parent = newRoot;
    return newRoot;
}

void RedBlackTree::ToString(std::string& result, const std::string& prefix, const Node* node, bool isRight) const
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

void RedBlackTree::Serialize(std::ostream& os, Node* node) const
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

RedBlackTree::Node* RedBlackTree::Deserialize(std::istream& is, Node* node, size_t& sizeOfTree)
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

RedBlackTreeConstIterator::RedBlackTreeConstIterator(const RedBlackTree* redBlackTree,
                                                     RedBlackTree::Node* node) noexcept
    : redBlackTree(redBlackTree)
    , node(node) { }

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
        node = redBlackTree->Max(redBlackTree->Root());
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