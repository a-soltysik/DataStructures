#pragma once

#include <istream>
#include <optional>
#include <iterator>

struct RedBlackTreeIterator;
struct RedBlackTreeConstIterator;

class RedBlackTree
{
public:
    friend struct RedBlackTreeIterator;
    friend struct RedBlackTreeConstIterator;

    using DataType = int32_t;
    using Iterator = RedBlackTreeIterator;
    using ConstIterator = RedBlackTreeConstIterator;

    RedBlackTree() = default;
    RedBlackTree(std::initializer_list<DataType> initList);
    RedBlackTree(const RedBlackTree& rhs);
    RedBlackTree(RedBlackTree&& rhs) noexcept;
    RedBlackTree& operator=(const RedBlackTree& rhs);
    RedBlackTree& operator=(RedBlackTree&& rhs) noexcept;
    ~RedBlackTree();

    Iterator Insert(const DataType& value);
    bool Remove(const DataType& value);
    [[nodiscard]] ConstIterator Find(const DataType& value) const;
    [[nodiscard]] Iterator Find(const DataType& value);
    void Clear();

    [[nodiscard]] DataType Min() const;
    [[nodiscard]] DataType Max() const;

    [[nodiscard]] size_t Size() const;

    [[nodiscard]] Iterator begin() noexcept;
    [[nodiscard]] Iterator end() noexcept;
    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;
    [[nodiscard]] ConstIterator cbegin() const noexcept;
    [[nodiscard]] ConstIterator cend() const noexcept;

    [[nodiscard]] static std::string ClassName();
    [[nodiscard]] std::string ToString() const;
    friend std::ostream& operator<<(std::ostream& os, const RedBlackTree& tree);
    friend std::istream& operator>>(std::istream& is, RedBlackTree& tree);

private:
    struct Node
    {
        enum class Color : uint8_t
        {
            RED,
            BLACK
        };
        Color color;
        DataType value;

        Node* parent;
        Node* right;
        Node* left;
    };

    inline static constexpr int64_t NIL_VALUE = -1;

    [[nodiscard]] static Node* MakeNil();

    void SetRoot(Node* node) const;
    [[nodiscard]] Node* root() const;
    [[nodiscard]] Node* Min(Node* node) const;
    [[nodiscard]] Node* Max(Node* node) const;
    [[nodiscard]] Node* Find(const DataType& value, Node* root) const;

    void LeftRotate(Node* node) const;
    void RightRotate(Node* node) const;

    void InsertFix(Node* node) const;
    void RemoveFix(Node* node) const;

    void MoveSubtree(Node* from, Node* to) const;
    void RemoveSubtree(Node* root);
    [[nodiscard]] Node* CopySubtree(const RedBlackTree& tree, Node* root);
    [[nodiscard]] Node* MakeNode(const DataType& value) const;

    void ToString(std::string& result, const std::string& prefix, const Node* node, bool isLeft) const;
    void Serialize(std::ostream& os, Node* node) const;
    [[nodiscard]] Node* Deserialize(std::istream& is, Node* node);

    Node* NIL = MakeNil();
    size_t size = 0u;
};

struct RedBlackTreeConstIterator
{
    friend class RedBlackTree;

    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = RedBlackTree::DataType;
    using pointer = const value_type*;
    using reference = const value_type&;

    RedBlackTreeConstIterator() = default;
    RedBlackTreeConstIterator(const RedBlackTree* redBlackTree, RedBlackTree::Node* node) noexcept;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    RedBlackTreeConstIterator& operator++() noexcept;
    RedBlackTreeConstIterator operator++(int) noexcept;
    RedBlackTreeConstIterator& operator--() noexcept;
    RedBlackTreeConstIterator operator--(int) noexcept;

    [[nodiscard]] bool operator==(const RedBlackTreeConstIterator& rhs) const noexcept;
    [[nodiscard]] bool operator!=(const RedBlackTreeConstIterator& rhs) const noexcept;

protected:
    const RedBlackTree* redBlackTree;
    RedBlackTree::Node* node;
};

struct RedBlackTreeIterator : public RedBlackTreeConstIterator
{
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = RedBlackTree::DataType;
    using pointer = value_type*;
    using reference = value_type&;

    using RedBlackTreeConstIterator::RedBlackTreeConstIterator;

    [[nodiscard]] reference operator*() const noexcept;

    [[nodiscard]] pointer operator->() const noexcept;

    RedBlackTreeIterator& operator++() noexcept;
    RedBlackTreeIterator operator++(int) noexcept;
    RedBlackTreeIterator& operator--() noexcept;
    RedBlackTreeIterator operator--(int) noexcept;
};