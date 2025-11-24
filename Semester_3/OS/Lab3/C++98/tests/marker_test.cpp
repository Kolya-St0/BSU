#include <gtest/gtest.h>
#include "marker.h"

using namespace std;

class MarkerThreadTests : public::testing::Test {
protected:
	void SetUp() override {}
	void TearDown() override {}

	bool all_zeros(vector<int>& array)
	{
		for (int i = 0; i < array.size(); i++) {
			if (array[i]) {
				return false;
			}
		}
		return true;
	}

	bool correct_array_mark(vector<int>& array, int thread_id)
	{
		for (int i = 0; i < array.size(); i++) {
			if (array[i] != 0 && array[i] != thread_id) {
				return false;
			}
		}
		return true;
	}

	int marked_count(vector<int>& array)
	{
		int count = 0;
		for (int i = 0; i < array.size(); i++) {
			if (array[i]) {
				count++;
			}
		}
		return count;
	}

	bool correct_thread_end(vector<int>& array, int thread_id)
	{
		for (int i = 0; i < array.size(); i++) {
			if (array[i] == thread_id) {
				return false;
			}
		}
		return true;
	}
};

TEST_F(MarkerThreadTests, ArrayCorrectMarkingBySingleThread)
{
	MarkerManager m(10, 1);
	m.start_threads();
	m.wait_for_blocking_threads();

	EXPECT_TRUE(correct_array_mark(m.get_array(), 1));

	m.end_thread(1);
}

TEST_F(MarkerThreadTests, ArrayAllZerosAfterSingleThread)
{
	MarkerManager m(10, 1);
	m.start_threads();
	m.wait_for_blocking_threads();
	m.end_thread(1);

	EXPECT_TRUE(all_zeros(m.get_array()));
}

TEST_F(MarkerThreadTests, ArrayCorrectMarkingByManyThreads)
{
	MarkerManager m(20, 8);
	m.start_threads();
	m.wait_for_blocking_threads();

	vector<int>array = m.get_array();

	EXPECT_GT(marked_count(array), 0);
	
	for (int i = 0; i < 20; i++) {
		EXPECT_GE(array[i], 0);
		EXPECT_LE(array[i], 8);
	}

	for (int i = 0; i < 8; i++) {
		m.end_thread(i + 1);
	}

	EXPECT_TRUE(all_zeros(m.get_array()));
}

TEST_F(MarkerThreadTests, CorrectSequentialEnding)
{
	MarkerManager m(10, 5);
	m.start_threads();
	
	for (int i = 0; i < 5; i++) {
		m.wait_for_blocking_threads();
		m.end_thread(i + 1);

		EXPECT_TRUE(correct_thread_end(m.get_array(), i + 1));

		m.resume_threads();
		Sleep(100);
	}

	EXPECT_TRUE(all_zeros(m.get_array()));
}