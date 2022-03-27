#include <gtest/gtest.h>

#include "Container/List/List.h"
#include "Utils/Utils.h"

class ListTest : public testing::Test
{
protected:
    List list;
};

TEST_F(ListTest, PushBackTest)
{
    list.PushBack(1);
    ASSERT_EQ(list.Size(), 1);
    EXPECT_EQ(list[0], 1);

    list.PushBack(14564);
    ASSERT_EQ(list.Size(), 2);
    EXPECT_EQ(list[1], 14564);

    list.PushBack(-345);
    ASSERT_EQ(list.Size(), 3);
    EXPECT_EQ(list[2], -345);

    list.PushBack(-345);
    ASSERT_EQ(list.Size(), 4);
    EXPECT_EQ(list[3], -345);
}

TEST_F(ListTest, PushFrontTest)
{
    list.PushFront(1234);
    ASSERT_EQ(list.Size(), 1);
    EXPECT_EQ(list[0], 1234);

    list.PushFront(-453);
    ASSERT_EQ(list.Size(), 2);
    EXPECT_EQ(list[0], -453);

    list.PushFront(0);
    ASSERT_EQ(list.Size(), 3);
    EXPECT_EQ(list[0], 0);

    list.PushFront(0);
    ASSERT_EQ(list.Size(), 4);
    EXPECT_EQ(list[0], 0);
}

TEST_F(ListTest, InsertPositionTest)
{
    list.Insert(0, 1);
    ASSERT_EQ(list.Size(), 1);
    EXPECT_EQ(list[0], 1);

    list.Insert(1, 3);
    ASSERT_EQ(list.Size(), 2);
    EXPECT_EQ(list[1], 3);

    list.Insert(0, -4);
    ASSERT_EQ(list.Size(), 3);
    EXPECT_EQ(list[0], -4);

    list.Insert(1, 45);
    ASSERT_EQ(list.Size(), 4);
    EXPECT_EQ(list[1], 45);

    EXPECT_THROW(
        {
            try
            {
                list.Insert(5, 6);
            }
            catch (const std::out_of_range& e)
            {
                EXPECT_STREQ(e.what(), "Index is out of range");
                throw e;
            }
        }, std::out_of_range);
}

TEST_F(ListTest, InsertIteratorTest)
{
    list.Insert(list.cbegin(), 1);
    ASSERT_EQ(list.Size(), 1);
    EXPECT_EQ(list[0], 1);

    list.Insert(list.cend(), 3);
    ASSERT_EQ(list.Size(), 2);
    EXPECT_EQ(list[1], 3);

    list.Insert(list.begin(), -4);
    ASSERT_EQ(list.Size(), 3);
    EXPECT_EQ(list[0], -4);

    list.Insert(++list.cbegin(), 45);
    ASSERT_EQ(list.Size(), 4);
    EXPECT_EQ(list[1], 45);
}

TEST_F(ListTest, RemoveTest)
{
    list.PushBack(10);
    list.PushBack(35);
    list.PushBack(-234);

    ASSERT_EQ(list.Size(), 3);

    list.Remove(35);
    ASSERT_EQ(list.Size(), 2);

    list.Remove(20);
    ASSERT_EQ(list.Size(), 2);

    list.Remove(10);
    ASSERT_EQ(list.Size(), 1);

    list.Remove(-234);
    ASSERT_EQ(list.Size(), 0);

    list.Remove(-234);
    ASSERT_EQ(list.Size(), 0);
}

TEST_F(ListTest, RemoveBackTest)
{
    list.PushBack(2345);
    list.PushBack(-43);
    list.PushBack(89);

    ASSERT_EQ(list.Size(), 3);

    list.RemoveBack();
    ASSERT_EQ(list.Size(), 2);
    EXPECT_EQ(list[1], -43);

    list.RemoveBack();
    ASSERT_EQ(list.Size(), 1);
    EXPECT_EQ(list[0], 2345);

    list.RemoveBack();
    ASSERT_EQ(list.Size(), 0);

    list.RemoveBack();
    ASSERT_EQ(list.Size(), 0);
}

TEST_F(ListTest, RemoveFrontTest)
{
    list.PushBack(2345);
    list.PushBack(-43);
    list.PushBack(89);

    ASSERT_EQ(list.Size(), 3);

    list.RemoveFront();
    ASSERT_EQ(list.Size(), 2);
    EXPECT_EQ(list[1], 89);

    list.RemoveFront();
    ASSERT_EQ(list.Size(), 1);
    EXPECT_EQ(list[0], 89);

    list.RemoveFront();
    ASSERT_EQ(list.Size(), 0);

    list.RemoveFront();
    ASSERT_EQ(list.Size(), 0);
}

TEST_F(ListTest, RemoveAtPositionTest)
{
    list.PushBack(2345);
    list.PushBack(-43);
    list.PushBack(89);

    ASSERT_EQ(list.Size(), 3);

    list.RemoveAt(1);
    ASSERT_EQ(list.Size(), 2);
    EXPECT_EQ(list[0], 2345);
    EXPECT_EQ(list[1], 89);

    list.RemoveAt(0);
    ASSERT_EQ(list.Size(), 1);
    EXPECT_EQ(list[0], 89);

    list.RemoveAt(0);
    ASSERT_EQ(list.Size(), 0);

    list.RemoveAt(0);
    ASSERT_EQ(list.Size(), 0);
}

TEST_F(ListTest, RemoveAtIteratorTest)
{
    list.PushBack(2345);
    list.PushBack(-43);
    list.PushBack(89);

    ASSERT_EQ(list.Size(), 3);

    list.RemoveAt(++list.begin());
    ASSERT_EQ(list.Size(), 2);
    EXPECT_EQ(list[0], 2345);
    EXPECT_EQ(list[1], 89);

    list.RemoveAt(list.cbegin());
    ASSERT_EQ(list.Size(), 1);
    EXPECT_EQ(list[0], 89);

    list.RemoveAt(list.cbegin());
    ASSERT_EQ(list.Size(), 0);

    list.RemoveAt(list.begin());
    ASSERT_EQ(list.Size(), 0);

    list.RemoveAt(list.cend());
    ASSERT_EQ(list.Size(), 0);
}

TEST_F(ListTest, ClearTest)
{
    for (size_t i = 0; i < 34523; i++)
    {
        list.PushBack(Utils::GetRandomInt(INT32_MIN, INT32_MAX));
    }
    EXPECT_EQ(list.Size(), 34523);
    list.Clear();
    EXPECT_EQ(list.Size(), 0);
}

TEST_F(ListTest, FindTest)
{
    list.PushBack(1);
    list.PushBack(2345);
    list.PushBack(-13254);
    list.PushBack(234);
    list.PushBack(-712);

    auto it2 = list.begin();
    std::advance(it2, 2);
    EXPECT_EQ(list.Find(-13254), it2);
    EXPECT_EQ(list.Find(2321534), list.end());

    const List constList = { 1, 2345, -13254, 234, -712 };

    auto constIt2 = constList.cbegin();
    std::advance(constIt2, 2);
    EXPECT_EQ(constList.Find(-13254), constIt2);
    EXPECT_EQ(constList.Find(1234), constList.cend());
}