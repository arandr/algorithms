#include "gtest/gtest.h"

extern "C"{
#include "radixsort.h"
}

TEST(RadixSortTest, SortsPositiveIntegers)
{
	int positiveValuedArray[3] = { 2, 4, 3 };
	array_type positive = { positiveValuedArray, 3 };
	int resultArray[3] = { 0, 0, 0 };
	array_type result = { resultArray, 3 };
	sort_radix(&result, &positive);
	EXPECT_EQ(2, resultArray[0]);
	EXPECT_EQ(3, resultArray[1]);
	EXPECT_EQ(4, resultArray[2]);
	EXPECT_EQ(2, positiveValuedArray[0]);
	EXPECT_EQ(4, positiveValuedArray[1]);
	EXPECT_EQ(3, positiveValuedArray[2]);
}

TEST(RadixSortTest, SortsNegativeIntegers)
{
	int negativeValuedArray[4] = { -50, -10, -20, -100 };
	int resultArray[4] = { 0, 0, 0, 0 };
	array_type negative = { negativeValuedArray, 4 };
	array_type result = { resultArray, 4 };
	sort_radix(&result, &negative);
	EXPECT_EQ(-100, resultArray[0]);
	EXPECT_EQ(-50, resultArray[1]);
	EXPECT_EQ(-20, resultArray[2]);
	EXPECT_EQ(-10, resultArray[3]);
	EXPECT_EQ(-50, negativeValuedArray[0]);
	EXPECT_EQ(-10, negativeValuedArray[1]);
	EXPECT_EQ(-20, negativeValuedArray[2]);
	EXPECT_EQ(-100, negativeValuedArray[3]);
}

TEST(RadixSortTest, SortsMixedValues)
{
	int mixedValuedArray[3] = { 2, -5, 13 };
	int resultArray[3] = { 0, 0, 0 };
	array_type mixed = { mixedValuedArray, 3 };
	array_type result = { resultArray, 3 };
	sort_radix(&result, &mixed);
	EXPECT_EQ(-5, resultArray[0]);
	EXPECT_EQ(2, resultArray[1]);
	EXPECT_EQ(13, resultArray[2]);
	EXPECT_EQ(2, mixedValuedArray[0]);
	EXPECT_EQ(-5, mixedValuedArray[1]);
	EXPECT_EQ(13, mixedValuedArray[2]);
}

TEST(RadixSortTest, SortsDuplicates)
{
	int duplicateValuedArray[4] = { 10, -10, -10, 40 };
	int resultArray[4] = { 0, 0, 0, 0 };
	array_type duplicate = { duplicateValuedArray, 4 };
	array_type result = { resultArray, 4 };
	sort_radix(&result, &duplicate);
	EXPECT_EQ(-10, resultArray[0]);
	EXPECT_EQ(-10, resultArray[1]);
	EXPECT_EQ(10, resultArray[2]);
	EXPECT_EQ(40, resultArray[3]);
	EXPECT_EQ(10, duplicateValuedArray[0]);
	EXPECT_EQ(-10, duplicateValuedArray[1]);
	EXPECT_EQ(-10, duplicateValuedArray[2]);
	EXPECT_EQ(40, duplicateValuedArray[3]);
}

TEST(RadixSortTest, SortsLargeArray)
{
	int* largeArray = new int[1000000];
	int* resultArray = new int[1000000];
	for (size_t i = 0; i < 1000000; i++){
		largeArray[i] = rand();
	}
	array_type large = { largeArray, 1000000 };
	array_type result = { resultArray, 1000000 };
	sort_radix(&result, &large);
	for (size_t i = 0; i < 1000000-1; i++){
		EXPECT_LE(resultArray[i], resultArray[i + 1]);
	}
}