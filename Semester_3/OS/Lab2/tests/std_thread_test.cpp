#include <gtest/gtest.h>
#include "std_thread.h"

using namespace std;

class ThreadTest : public::testing::Test {
protected:
    Array* th_a = nullptr;

    void SetUp() override
    {
        th_a = new Array();
        th_a->size = 0;
        th_a->array = nullptr;
    }

    void TearDown() override 
    {
        if (th_a) {
            delete[]th_a->array;
            delete th_a;
        }
    }
};

TEST_F(ThreadTest, FiveMinMax) 
{
    th_a->size = 5;
    th_a->array = new int[th_a->size];
    
    int a[] = { 10,23,2,27,87 };

    for (int i = 0; i < th_a->size; i++) {
        th_a->array[i] = a[i];
    }

    thread t_minmax(min_max, th_a);
    t_minmax.join();

    EXPECT_EQ(th_a->min, 2);
    EXPECT_EQ(th_a->max, 87);
}

TEST_F(ThreadTest, EqualMinMax)
{
    th_a->size = 3;
    th_a->array = new int[th_a->size];

    int a[] = { 3,3,3 };

    for (int i = 0; i < th_a->size; i++) {
        th_a->array[i] = a[i];
    }

    thread t_minmax(min_max, th_a);
    t_minmax.join();

    EXPECT_EQ(th_a->min, 3);
    EXPECT_EQ(th_a->max, th_a->min);
}

TEST_F(ThreadTest, SingleMinMax)
{
    th_a->size = 1;
    th_a->array = new int[th_a->size];

    int a[] = { 6 };

    for (int i = 0; i < th_a->size; i++) {
        th_a->array[i] = a[i];
    }

    thread t_minmax(min_max, th_a);
    t_minmax.join();

    EXPECT_EQ(th_a->min, 6);
    EXPECT_EQ(th_a->max, th_a->min);
}

TEST_F(ThreadTest, EmptyMinMax)
{
    stringstream buffer;
    streambuf* sbuf = cout.rdbuf();
    cout.rdbuf(buffer.rdbuf());

    thread t_minmax(min_max, th_a);
    t_minmax.join();

    cout.rdbuf(sbuf);
    string output = buffer.str();

    EXPECT_EQ(output, "Array is empty\n");
}

TEST_F(ThreadTest, SevenAverage)
{
    th_a->size = 7;
    th_a->array = new int[th_a->size];

    int a[] = { 1,2,3,4,5,6,7 };

    for (int i = 0; i < th_a->size; i++) {
        th_a->array[i] = a[i];
    }

    thread t_average(average, th_a);
    t_average.join();

    EXPECT_EQ(th_a->average, 4);
}

TEST_F(ThreadTest, EqualAverage)
{
    th_a->size = 4;
    th_a->array = new int[th_a->size];

    int a[] = { 2,2,2,2 };

    for (int i = 0; i < th_a->size; i++) {
        th_a->array[i] = a[i];
    }

    thread t_average(average, th_a);
    t_average.join();

    EXPECT_EQ(th_a->average, 2);
}

TEST_F(ThreadTest, SingleAverage)
{
    th_a->size = 1;
    th_a->array = new int[th_a->size];

    int a[] = { 8 };

    for (int i = 0; i < th_a->size; i++) {
        th_a->array[i] = a[i];
    }

    thread t_average(average, th_a);
    t_average.join();

    EXPECT_EQ(th_a->average, 8);
}

TEST_F(ThreadTest, EmptyAverage) 
{
    stringstream buffer;
    streambuf* sbuf = cout.rdbuf();
    cout.rdbuf(buffer.rdbuf());

    thread t_average(average, th_a);
    t_average.join();

    cout.rdbuf(sbuf);
    string output = buffer.str();

    EXPECT_EQ(output, "Array is empty\n");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}