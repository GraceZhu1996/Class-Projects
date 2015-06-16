//ARRAYLIST_TESTS.CP

#include <gtest/gtest.h>
#include "ArrayList.hpp"


TEST(ArrayListTest, equalOperator)
{
    ArrayList<int> intList;
    intList.add(45);
    intList.add(90);

    ArrayList<int> secondList;
    secondList = intList;

    ASSERT_EQ(secondList.at(0), 45);
    ASSERT_EQ(secondList.at(1), 90);
}


TEST(ArrayListTest, objectAt)
{
    ArrayList<int> intList;
    intList.add(100);

    ASSERT_EQ(intList.at(0), 100);
}

TEST(ArrayListTest, outOfBoundsException)
{
    ArrayList<int> intList;
    intList.add(100);

	ASSERT_THROW(intList.at(1), OutOfBoundsException);
}


TEST(ArrayListTest, size)
{
    ArrayList<int> intList;
    intList.add(45);
    intList.add(90);
    intList.add(962);
    intList.add(900);

    ASSERT_EQ(intList.size(), 4);
}

TEST(ArrayListTest, capacityCheck)
{
    ArrayList<int> intList;

    ASSERT_EQ(intList.capacity(), 10);
}
