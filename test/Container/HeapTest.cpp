#include <gtest/gtest.h>

#include "Container/Heap/Heap.h"

#include <algorithm>

class HeapTest : public testing::Test
{
protected:
    Heap heap;
};

TEST_F(HeapTest, InsertTest)
{
    heap.Insert(1);
    heap.Insert(2);
    heap.Insert(3);
    heap.Insert(4);
    heap.Insert(5);

    ASSERT_EQ(heap.Size(), 5);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Insert(10);
    heap.Insert(8);
    heap.Insert(6);
    heap.Insert(-1);
    heap.Insert(-5);

    ASSERT_EQ(heap.Size(), 10);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));
}

TEST_F(HeapTest, FindTest)
{
    heap.Insert(1);
    heap.Insert(23);
    heap.Insert(15);
    heap.Insert(-34);
    heap.Insert(12);
    heap.Insert(10);
    heap.Insert(0);

    ASSERT_EQ(heap.Size(), 7);
    ASSERT_NE(heap.Find(1), nullptr);
    ASSERT_NE(heap.Find(23), nullptr);
    ASSERT_NE(heap.Find(15), nullptr);
    ASSERT_NE(heap.Find(-34), nullptr);
    ASSERT_NE(heap.Find(12), nullptr);
    ASSERT_NE(heap.Find(10), nullptr);
    ASSERT_NE(heap.Find(0), nullptr);

    ASSERT_EQ(heap.Find(345), nullptr);
    ASSERT_EQ(heap.Find(-21345), nullptr);
}

TEST_F(HeapTest, RemoveTest)
{
    heap.Insert(1);
    heap.Insert(23);
    heap.Insert(15);
    heap.Insert(-34);
    heap.Insert(12);
    heap.Insert(10);
    heap.Insert(0);

    ASSERT_EQ(heap.Size(), 7);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Remove(1);
    ASSERT_EQ(heap.Size(), 6);
    ASSERT_EQ(heap.Find(1), nullptr);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Remove(23);
    ASSERT_EQ(heap.Size(), 5);
    ASSERT_EQ(heap.Find(23), nullptr);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Remove(15);
    ASSERT_EQ(heap.Size(), 4);
    ASSERT_EQ(heap.Find(15), nullptr);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Remove(-34);
    ASSERT_EQ(heap.Size(), 3);
    ASSERT_EQ(heap.Find(-34), nullptr);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Remove(12);
    ASSERT_EQ(heap.Size(), 2);
    ASSERT_EQ(heap.Find(12), nullptr);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Remove(10);
    ASSERT_EQ(heap.Size(), 1);
    ASSERT_EQ(heap.Find(10), nullptr);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Remove(0);
    ASSERT_EQ(heap.Size(), 0);
    ASSERT_EQ(heap.Find(0), nullptr);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Remove(453);
    ASSERT_EQ(heap.Size(), 0);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));
}

TEST_F(HeapTest, PopTest)
{
    heap.Insert(1);
    heap.Insert(23);
    heap.Insert(15);
    heap.Insert(-34);
    heap.Insert(12);
    heap.Insert(10);
    heap.Insert(0);

    ASSERT_EQ(heap.Size(), 7);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Pop();
    ASSERT_EQ(heap.Size(), 6);
    ASSERT_EQ(heap.Max(), 15);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Pop();
    ASSERT_EQ(heap.Size(), 5);
    ASSERT_EQ(heap.Max(), 12);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Pop();
    ASSERT_EQ(heap.Size(), 4);
    ASSERT_EQ(heap.Max(), 10);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Pop();
    ASSERT_EQ(heap.Size(), 3);
    ASSERT_EQ(heap.Max(), 1);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Pop();
    ASSERT_EQ(heap.Size(), 2);
    ASSERT_EQ(heap.Max(), 0);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Pop();
    ASSERT_EQ(heap.Size(), 1);
    ASSERT_EQ(heap.Max(), -34);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Pop();
    ASSERT_EQ(heap.Size(), 0);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    EXPECT_THROW(
    {
        try
        {
            auto tmp = heap.Max();
        }
        catch (const std::out_of_range& e)
        {
            EXPECT_STREQ(e.what(), "Index is out of range");
            throw e;
        }
    }, std::out_of_range);
}

TEST_F(HeapTest, ClearTest)
{
    for (size_t i = 0; i < 23455; i++)
    {
        heap.Insert(i);
    }
    ASSERT_EQ(heap.Size(), 23455);
    ASSERT_TRUE(std::is_heap(heap.Array().cbegin(), heap.Array().cend()));

    heap.Clear();
    ASSERT_EQ(heap.Size(), 0);
}