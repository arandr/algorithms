#include "gtest/gtest.h"

extern "C"{
#include "fibonacciheap.h"
}

TEST(FibonacciHeapTest, InsertOneElement)
{
	fibonacci_heap* heap = fibonacci_heap_create();
	char values[3] = { 'a', 'b', 'c' };
	void* item_ptr = NULL;
	int key = -1;
	EXPECT_TRUE(NULL != heap);
	fibonacci_heap_tree_node* new_element = fibonacci_heap_insert(heap, 2, &values[1]);
	EXPECT_EQ(true, fibonacci_heap_get_min(heap, &key, &item_ptr));
	EXPECT_TRUE(NULL != item_ptr);
	EXPECT_EQ(2, key);
	EXPECT_EQ(*(char*)item_ptr, values[1]);
	EXPECT_EQ(2, ((fibonacci_heap_tree_node*)(heap->min_root->obj))->key);
}