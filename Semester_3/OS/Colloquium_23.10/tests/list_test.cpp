#include <gtest/gtest.h>
#include "list.h"
#include <vector>

using namespace std;

class ListTests : public::testing::Test {
protected:
    LinkedList list;

	void SetUp() override 
    {
        list.clear();
    }

	void TearDown() override {}
};

TEST_F(ListTests, List_Size_Three)
{
    vector<int>input = { 1,2,3 };
    list.create(input);

    EXPECT_EQ(list.size(), 3);
}

TEST_F(ListTests, Empty_List_Size)
{
    EXPECT_EQ(list.size(), 0);
}

TEST_F(ListTests, List_Empty_Five)
{
    vector<int>input = { 7,8,9,10,11 };
    list.create(input);

    EXPECT_FALSE(list.empty());
}

TEST_F(ListTests, Empty_List_Empty)
{
    EXPECT_TRUE(list.empty());
}

TEST_F(ListTests, List_To_Vector_Two)
{
    vector<int>input = { 1,2 };
    list.create(input);

    EXPECT_EQ(list.to_vector(), input);
}

TEST_F(ListTests, Empty_List_To_Vector)
{
    EXPECT_EQ(list.to_vector(), vector<int>({}));
}

TEST_F(ListTests, List_Create_Empty) {
    vector<int> empty;
    list.create(empty);

    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST_F(ListTests, List_Create_Seven) {
    vector<int> input = { 1,2,3,4,5,6,7 };
    list.create(input);

    EXPECT_EQ(list.size(), 7);
    EXPECT_EQ(list.to_vector() , input);
}

TEST_F(ListTests, List_Reverse)
{
    vector<int> input = { 6,7,8,9,10 };
    list.create(input);
    list.reverse();

    EXPECT_EQ(list.to_vector(), vector<int>({ 10,9,8,7,6 }));
}

TEST_F(ListTests, List_Reverse_Single)
{
    vector<int> input = { 8 };
    list.create(input);
    list.reverse();

    EXPECT_EQ(list.to_vector(), vector<int>({ 8 }));
}

TEST_F(ListTests, List_Reverse_Empty)
{
    list.reverse();
    EXPECT_TRUE(list.empty());
}

TEST_F(ListTests, List_Clear)
{
    vector<int> input = { 0,1,2,3,4 };
    list.create(input);
    list.clear();

    EXPECT_TRUE(list.empty());
}

TEST_F(ListTests, Empty_List_Clear)
{
    list.clear();

    EXPECT_TRUE(list.empty());
}