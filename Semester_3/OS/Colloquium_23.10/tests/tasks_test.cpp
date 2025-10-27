#include <gtest/gtest.h>
#include "tasks.h"
#include <vector>

using namespace std;

class TasksTests : public::testing::Test {
protected:
	void SetUp() override {}
	void TearDown() override {}
};

TEST_F(TasksTests, Factorials_Zero)
{
	auto result = Tasks::calc_factorials(0);
	EXPECT_EQ(result.size(), 1);
	EXPECT_EQ(result[0], 1);
}

TEST_F(TasksTests, Factorials_Negative) 
{
	EXPECT_THROW(Tasks::calc_factorials(-1), string);
}

TEST_F(TasksTests, Factorials_Overflow) 
{
	EXPECT_THROW(Tasks::calc_factorials(21), string);
}

TEST_F(TasksTests, Factorials_Six) 
{
	auto result = Tasks::calc_factorials(6);
	EXPECT_EQ(result.size(), 7);
	EXPECT_EQ(result, vector<unsigned long long> ({ 1,1,2,6,24,120,720 }));
}

TEST_F(TasksTests, Delete_Duplicates_Four) 
{
	vector<int>input = { 1,2,1,3,2,2,4,5,4 };
	Tasks::delete_duplicates(input);
	EXPECT_EQ(input, vector<int>({ 1,2,3,4,5 }));
}

TEST_F(TasksTests, Delete_Duplicates_All_Unique) 
{
	vector<int>input = { 0,17,4,23,9 };
	Tasks::delete_duplicates(input);
	EXPECT_EQ(input, vector<int>({ 0,17,4,23,9 }));
}