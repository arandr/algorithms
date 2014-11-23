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
	EXPECT_EQ(resultArray[0], 2);
	EXPECT_EQ(resultArray[1], 3);
	EXPECT_EQ(resultArray[2], 4);
	EXPECT_EQ(positiveValuedArray[0], 2);
	EXPECT_EQ(positiveValuedArray[1], 4);
	EXPECT_EQ(positiveValuedArray[2], 3);
}

TEST(RadixSortTest, SortsNegativeIntegers)
{
	int negativeValuedArray[4] = { -50, -10, -20, -100 };
	int resultArray[4] = { 0, 0, 0, 0 };
	array_type negative = { negativeValuedArray, 4 };
	array_type result = { resultArray, 4 };
	sort_radix(&result, &negative);
	EXPECT_EQ(resultArray[0], -100);
	EXPECT_EQ(resultArray[1], -50);
	EXPECT_EQ(resultArray[2], -20);
	EXPECT_EQ(resultArray[3], -10);
	EXPECT_EQ(negativeValuedArray[0], -50);
	EXPECT_EQ(negativeValuedArray[1], -10);
	EXPECT_EQ(negativeValuedArray[2], -20);
	EXPECT_EQ(negativeValuedArray[3], -100);
}

TEST(RadixSortTest, SortsMixedValues)
{
	int mixedValuedArray[3] = { 2, -5, 13 };
	int resultArray[3] = { 0, 0, 0 };
	array_type mixed = { mixedValuedArray, 3 };
	array_type result = { resultArray, 3 };
	sort_radix(&result, &mixed);
	EXPECT_EQ(resultArray[0], -5);
	EXPECT_EQ(resultArray[1], 2);
	EXPECT_EQ(resultArray[2], 13);
	EXPECT_EQ(mixedValuedArray[0], 2);
	EXPECT_EQ(mixedValuedArray[1], -5);
	EXPECT_EQ(mixedValuedArray[2], 13);
}

TEST(RadixSortTest, SortsDuplicates)
{
	int duplicateValuedArray[4] = { 10, -10, -10, 40 };
	int resultArray[4] = { 0, 0, 0, 0 };
	array_type duplicate = { duplicateValuedArray, 4 };
	array_type result = { resultArray, 4 };
	sort_radix(&result, &duplicate);
	EXPECT_EQ(resultArray[0], -10);
	EXPECT_EQ(resultArray[1], -10);
	EXPECT_EQ(resultArray[2], 10);
	EXPECT_EQ(resultArray[3], 40);
	EXPECT_EQ(duplicateValuedArray[0], 10);
	EXPECT_EQ(duplicateValuedArray[1], -10);
	EXPECT_EQ(duplicateValuedArray[2], -10);
	EXPECT_EQ(duplicateValuedArray[3], 40);
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