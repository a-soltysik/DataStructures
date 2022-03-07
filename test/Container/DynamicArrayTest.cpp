#include <gtest/gtest.h>

#include "Container/DynamicArray/DynamicArray.h"

class DynamicArrayTest : public testing::Test
{
protected:
    DynamicArray array;
};

TEST_F(DynamicArrayTest, PushBackTest)
{
    array.PushBack(1);
    ASSERT_EQ(array.Size(), 1);
    EXPECT_EQ(array[0], 1);

    array.PushBack(14564);
    ASSERT_EQ(array.Size(), 2);
    EXPECT_EQ(array[1], 14564);

    array.PushBack(-345);
    ASSERT_EQ(array.Size(), 3);
    EXPECT_EQ(array[2], -345);

    array.PushBack(-345);
    ASSERT_EQ(array.Size(), 4);
    EXPECT_EQ(array[3], -345);
}

TEST_F(DynamicArrayTest, PushFrontTest)
{
    array.PushFront(1234);
    ASSERT_EQ(array.Size(), 1);
    EXPECT_EQ(array[0], 1234);

    array.PushFront(-453);
    ASSERT_EQ(array.Size(), 2);
    EXPECT_EQ(array[0], -453);

    array.PushFront(0);
    ASSERT_EQ(array.Size(), 3);
    EXPECT_EQ(array[0], 0);

    array.PushFront(0);
    ASSERT_EQ(array.Size(), 4);
    EXPECT_EQ(array[0], 0);
}

TEST_F(DynamicArrayTest, InsertPositionTest)
{
    array.Insert(0, 1);
    ASSERT_EQ(array.Size(), 1);
    EXPECT_EQ(array[0], 1);

    array.Insert(1, 3);
    ASSERT_EQ(array.Size(), 2);
    EXPECT_EQ(array[1], 3);

    array.Insert(0, -4);
    ASSERT_EQ(array.Size(), 3);
    EXPECT_EQ(array[0], -4);

    array.Insert(1, 45);
    ASSERT_EQ(array.Size(), 4);
    EXPECT_EQ(array[1], 45);

    EXPECT_THROW(
    {
        try
        {
            array.Insert(5, 6);
        }
        catch(const std::out_of_range& e)
        {
            EXPECT_STREQ(e.what(), "Index is out of range");
            throw e;
        }
    }, std::out_of_range);
}

TEST_F(DynamicArrayTest, InsertIteratorTest)
{
    array.Insert(array.cbegin(), 1);
    ASSERT_EQ(array.Size(), 1);
    EXPECT_EQ(array[0], 1);

    array.Insert(array.cend(), 3);
    ASSERT_EQ(array.Size(), 2);
    EXPECT_EQ(array[1], 3);

    array.Insert(array.begin(), -4);
    ASSERT_EQ(array.Size(), 3);
    EXPECT_EQ(array[0], -4);

    array.Insert(array.cbegin() + 1, 45);
    ASSERT_EQ(array.Size(), 4);
    EXPECT_EQ(array[1], 45);
}

TEST_F(DynamicArrayTest, RemoveTest)
{
    array.PushBack(10);
    array.PushBack(35);
    array.PushBack(-234);

    ASSERT_EQ(array.Size(), 3);

    array.Remove(35);
    ASSERT_EQ(array.Size(), 2);

    array.Remove(20);
    ASSERT_EQ(array.Size(), 2);

    array.Remove(10);
    ASSERT_EQ(array.Size(), 1);

    array.Remove(-234);
    ASSERT_EQ(array.Size(), 0);

    array.Remove(-234);
    ASSERT_EQ(array.Size(), 0);
}

TEST_F(DynamicArrayTest, RemoveBackTest)
{
    array.PushBack(2345);
    array.PushBack(-43);
    array.PushBack(89);

    ASSERT_EQ(array.Size(), 3);

    array.RemoveBack();
    ASSERT_EQ(array.Size(), 2);
    EXPECT_EQ(array[1], -43);

    array.RemoveBack();
    ASSERT_EQ(array.Size(), 1);
    EXPECT_EQ(array[0], 2345);

    array.RemoveBack();
    ASSERT_EQ(array.Size(), 0);

    array.RemoveBack();
    ASSERT_EQ(array.Size(), 0);
}

TEST_F(DynamicArrayTest, RemoveFrontTest)
{
    array.PushBack(2345);
    array.PushBack(-43);
    array.PushBack(89);

    ASSERT_EQ(array.Size(), 3);

    array.RemoveFront();
    ASSERT_EQ(array.Size(), 2);
    EXPECT_EQ(array[1], 89);

    array.RemoveFront();
    ASSERT_EQ(array.Size(), 1);
    EXPECT_EQ(array[0], 89);

    array.RemoveFront();
    ASSERT_EQ(array.Size(), 0);

    array.RemoveFront();
    ASSERT_EQ(array.Size(), 0);
}

TEST_F(DynamicArrayTest, RemoveAtPositionTest)
{
    array.PushBack(2345);
    array.PushBack(-43);
    array.PushBack(89);

    ASSERT_EQ(array.Size(), 3);

    array.RemoveAt(1);
    ASSERT_EQ(array.Size(), 2);
    EXPECT_EQ(array[0], 2345);
    EXPECT_EQ(array[1], 89);

    array.RemoveAt(0);
    ASSERT_EQ(array.Size(), 1);
    EXPECT_EQ(array[0], 89);

    array.RemoveAt(0);
    ASSERT_EQ(array.Size(), 0);

    array.RemoveAt(0);
    ASSERT_EQ(array.Size(), 0);
}

TEST_F(DynamicArrayTest, RemoveAtIteratorTest)
{
    array.PushBack(2345);
    array.PushBack(-43);
    array.PushBack(89);

    ASSERT_EQ(array.Size(), 3);

    array.RemoveAt(array.begin() + 1);
    ASSERT_EQ(array.Size(), 2);
    EXPECT_EQ(array[0], 2345);
    EXPECT_EQ(array[1], 89);

    array.RemoveAt(array.cbegin());
    ASSERT_EQ(array.Size(), 1);
    EXPECT_EQ(array[0], 89);

    array.RemoveAt(array.cbegin());
    ASSERT_EQ(array.Size(), 0);

    array.RemoveAt(array.begin());
    ASSERT_EQ(array.Size(), 0);

    array.RemoveAt(array.cend());
    ASSERT_EQ(array.Size(), 0);
}

TEST_F(DynamicArrayTest, ClearTest)
{
    for (size_t i = 0; i < 34523; i++)
    {
        array.PushBack(i);
    }
    EXPECT_EQ(array.Size(), 34523);
    array.Clear();
    EXPECT_EQ(array.Size(), 0);
}

TEST_F(DynamicArrayTest, FindTest)
{
    array.PushBack(1);
    array.PushBack(2345);
    array.PushBack(-13254);
    array.PushBack(234);
    array.PushBack(-712);

    EXPECT_EQ(array.Find(-13254), array.begin() + 2);
    EXPECT_EQ(array.Find(2321534), array.end());

    const DynamicArray constArray = { 1, 2345, -13254, 234, -712 };

    EXPECT_EQ(constArray.Find(-13254), constArray.cbegin() + 2);
    EXPECT_EQ(constArray.Find(1234), constArray.cend());
}