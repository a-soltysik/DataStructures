#pragma once

#include <istream>

struct AvlTreeIterator;
struct AvlTreeConstIterator;

class AvlTree
{
public:
    friend struct AvlTreeIterator;
    friend struct AvlTreeConstIterator;

    using DataType = int32_t;
    using Iterator = AvlTreeIterator;
    using ConstIterator = AvlTreeConstIterator;

    [[nodiscard]] static constexpr const char* ClassName() { return "AvlTree"; }

    AvlTree() = default;
    AvlTree(std::initializer_list<DataType> initList);
    AvlTree(const AvlTree& rhs);
    AvlTree(AvlTree&& rhs) noexcept;
    AvlTree& operator=(const AvlTree& rhs);
    AvlTree& operator=(AvlTree&& rhs) noexcept;
    ~AvlTree();

    Iterator Insert(DataType value);
    bool Remove(DataType value);
    void Clear();

    [[nodiscard]] ConstIterator Find(DataType value) const;
    [[nodiscard]] Iterator Find(DataType value);

    [[nodiscard]] DataType Min() const;
    [[nodiscard]] DataType Max() const;

    [[nodiscard]] size_t Size() const noexcept;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;
    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;
    [[nodiscard]] ConstIterator cbegin() const noexcept;
    [[nodiscard]] ConstIterator cend() const noexcept;

    [[nodiscard]] std::string ToString() const;
    friend std::ostream& operator<<(std::ostream& os, const AvlTree& tree);
    friend std::istream& operator>>(std::istream& is, AvlTree& tree);

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
    [[nodiscard]] Node* MakeNode(DataType value) const;

    void SetRoot(Node* node) const noexcept;
    [[nodiscard]] Node* Root() const noexcept;

    [[nodiscard]] Node* Min(Node* node) const noexcept;
    [[nodiscard]] Node* Max(Node* node) const noexcept;
    [[nodiscard]] Node* Find(const DataType& value, Node* root) const noexcept;

    void InsertFix(Node* node) const noexcept;
    void RemoveFix(Node* node) const noexcept;

    void RemoveSubtree(Node* root);
    [[nodiscard]] Node* CopySubtree(const AvlTree& tree, Node* root);

    Node* RemoveNodeWithoutChildren(Node* node) const;
    Node* RemoveNodeWithOneChild(Node* node) const;
    Node* RemoveNodeWithTwoChildren(Node* node) const;

    void ToString(std::string& result, const std::string& prefix, const Node* node, bool isRight) const;
    void Serialize(std::ostream& os, Node* node) const;
    [[nodiscard]] Node* Deserialize(std::istream& is, Node* node, size_t& size);

    Node* NIL = MakeNil();
    size_t size = 0;
};

struct AvlTreeConstIterator
{
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = AvlTree::DataType;
    using pointer = const value_type*;
    using reference = const value_type&;

    AvlTreeConstIterator() = default;
    AvlTreeConstIterator(const AvlTree* avlTree, AvlTree::Node* node) noexcept;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    AvlTreeConstIterator& operator++() noexcept;
    AvlTreeConstIterator operator++(int) noexcept;
    AvlTreeConstIterator& operator--() noexcept;
    AvlTreeConstIterator operator--(int) noexcept;

    [[nodiscard]] bool operator==(const AvlTreeConstIterator& rhs) const noexcept;
    [[nodiscard]] bool operator!=(const AvlTreeConstIterator& rhs) const noexcept;

protected:
    const AvlTree* avlTree;
    AvlTree::Node* node;
};

struct AvlTreeIterator : public AvlTreeConstIterator
{
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = AvlTree::DataType;
    using pointer = value_type*;
    using reference = value_type&;

    using AvlTreeConstIterator::AvlTreeConstIterator;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    AvlTreeIterator& operator++() noexcept;
    AvlTreeIterator operator++(int) noexcept;
    AvlTreeIterator& operator--() noexcept;
    AvlTreeIterator operator--(int) noexcept;
};