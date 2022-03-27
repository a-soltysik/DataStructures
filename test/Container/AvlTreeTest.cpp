#include <gtest/gtest.h>

#include "Container/AvlTree/AvlTree.h"
#include "Utils/Utils.h"

#include <algorithm>

class AvlTreeTest : public testing::Test
{
protected:
    AvlTree tree;
};

TEST_F(AvlTreeTest, InsertTest)
{
    tree.Insert(9);
    ASSERT_EQ(tree.Size(), 1);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    ASSERT_TRUE(tree.Find(9) != tree.end());

    tree.Insert(4);
    ASSERT_EQ(tree.Size(), 2);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    ASSERT_TRUE(tree.Find(4) != tree.end());

    tree.Insert(11);
    ASSERT_EQ(tree.Size(), 3);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    ASSERT_TRUE(tree.Find(11) != tree.end());

    tree.Insert(7);
    ASSERT_EQ(tree.Size(), 4);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    ASSERT_TRUE(tree.Find(7) != tree.end());

    tree.Insert(8);
    ASSERT_EQ(tree.Size(), 5);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    ASSERT_TRUE(tree.Find(8) != tree.end());

    tree.Insert(1);
    ASSERT_EQ(tree.Size(), 6);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    ASSERT_TRUE(tree.Find(1) != tree.end());

    tree.Insert(5);
    ASSERT_EQ(tree.Size(), 7);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    ASSERT_TRUE(tree.Find(5) != tree.end());

    tree.Insert(2);
    ASSERT_EQ(tree.Size(), 8);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    ASSERT_TRUE(tree.Find(2) != tree.end());
}

TEST_F(AvlTreeTest, RemoveTest)
{
    tree.Insert(9);
    tree.Insert(4);
    tree.Insert(11);
    tree.Insert(15);
    tree.Insert(23);
    tree.Insert(13);
    tree.Insert(5);
    tree.Insert(1);
    ASSERT_EQ(tree.Size(), 8);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));

    tree.Remove(754);
    ASSERT_EQ(tree.Size(), 8);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));

    tree.Remove(23);
    ASSERT_EQ(tree.Size(), 7);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    EXPECT_EQ(tree.Find(23), tree.cend());

    tree.Remove(23);
    ASSERT_EQ(tree.Size(), 7);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    EXPECT_EQ(tree.Find(23), tree.cend());

    tree.Remove(1);
    ASSERT_EQ(tree.Size(), 6);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    EXPECT_EQ(tree.Find(1), tree.cend());

    tree.Remove(15);
    ASSERT_EQ(tree.Size(), 5);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    EXPECT_EQ(tree.Find(15), tree.cend());

    tree.Remove(9);
    ASSERT_EQ(tree.Size(), 4);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    EXPECT_EQ(tree.Find(9), tree.cend());

    tree.Remove(4);
    ASSERT_EQ(tree.Size(), 3);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    EXPECT_EQ(tree.Find(4), tree.cend());

    tree.Remove(11);
    ASSERT_EQ(tree.Size(), 2);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    EXPECT_EQ(tree.Find(11), tree.cend());

    tree.Remove(5);
    ASSERT_EQ(tree.Size(), 1);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    EXPECT_EQ(tree.Find(5), tree.cend());

    tree.Remove(13);
    ASSERT_EQ(tree.Size(), 0);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    EXPECT_EQ(tree.Find(13), tree.cend());

    tree.Remove(754);
    ASSERT_EQ(tree.Size(), 0);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
}

TEST_F(AvlTreeTest, FindTest)
{
    tree.Insert(9);
    tree.Insert(4);
    tree.Insert(11);
    tree.Insert(15);
    tree.Insert(23);
    tree.Insert(13);
    tree.Insert(5);
    tree.Insert(1);

    ASSERT_EQ(tree.Size(), 8);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));

    ASSERT_EQ(tree.Find(754), tree.cend());
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));

    ASSERT_NE(tree.Find(23), tree.cend());
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));


    ASSERT_NE(tree.Find(1), tree.cend());
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));

    ASSERT_NE(tree.Find(15), tree.cend());
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));

    ASSERT_NE(tree.Find(9), tree.cend());
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));

    ASSERT_NE(tree.Find(4), tree.cend());
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));

    ASSERT_NE(tree.Find(11), tree.cend());
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));

    ASSERT_NE(tree.Find(5), tree.cend());
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));

    ASSERT_NE(tree.Find(13), tree.cend());
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
}

TEST_F(AvlTreeTest, ClearTest)
{
    for (int32_t i = 0; i < 12345; i++)
    {
        tree.Insert(Utils::GetRandomInt(INT32_MIN, INT32_MAX));
        ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));
    }

    ASSERT_EQ(tree.Size(), 12345);
    ASSERT_TRUE(std::is_sorted(tree.cbegin(), tree.cend()));

    tree.Clear();
    ASSERT_EQ(tree.Size(), 0);

    tree.Insert(5);
    tree.Insert(2);
    tree.Remove(5);
    tree.Clear();
}