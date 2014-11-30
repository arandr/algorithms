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
	EXPECT_EQ(values[1], *(char*)item_ptr);
	EXPECT_EQ(2, ((fibonacci_heap_tree_node*)(heap->min_root->obj))->key);
}

TEST(FibonacciHeapTest, InsertSeveralElements)
{
	fibonacci_heap* heap = fibonacci_heap_create();
	char values[3] = { 'a', 'b', 'c' };
	void* item_ptr = NULL;
	int key = -1;
	EXPECT_TRUE(NULL != heap);
	fibonacci_heap_tree_node* new_element = fibonacci_heap_insert(heap, 2, &values[1]);
	new_element = fibonacci_heap_insert(heap, 1, &values[0]);
	new_element = fibonacci_heap_insert(heap, 5, &values[2]);
	EXPECT_EQ(true, fibonacci_heap_get_min(heap, &key, &item_ptr));
	EXPECT_TRUE(NULL != item_ptr);
	EXPECT_EQ(1, key);
	EXPECT_EQ(values[0], *(char*)item_ptr);
	EXPECT_EQ(1, ((fibonacci_heap_tree_node*)(heap->min_root->obj))->key);
}

TEST(FibonacciHeapTest, InsertThenDeleteMin)
{
	fibonacci_heap* heap = fibonacci_heap_create();
	char values[3] = { 'a', 'b', 'c' };
	void* item_ptr = NULL;
	int key = -1;
	EXPECT_TRUE(NULL != heap);
	fibonacci_heap_tree_node* new_element = fibonacci_heap_insert(heap, 2, &values[1]);
	new_element = fibonacci_heap_insert(heap, 1, &values[0]);
	new_element = fibonacci_heap_insert(heap, 5, &values[2]);
	fibonacci_heap_delete_min(heap);
	EXPECT_EQ(true, fibonacci_heap_get_min(heap, &key, &item_ptr));
	EXPECT_TRUE(NULL != item_ptr);
	EXPECT_EQ(2, key);
	EXPECT_EQ(values[1], *(char*)item_ptr);
	EXPECT_EQ(2, ((fibonacci_heap_tree_node*)(heap->min_root->obj))->key);
}

TEST(FibonacciHeapTest, SuccessiveDeleteMin)
{
	fibonacci_heap* heap = fibonacci_heap_create();
	char values[5] = { 'a', 'b', 'c', 'd', 'e' };
	void* item_ptr = NULL;
	int key = -1;
	EXPECT_TRUE(NULL != heap);
	fibonacci_heap_tree_node* new_element = fibonacci_heap_insert(heap, 2, &values[1]);
	new_element = fibonacci_heap_insert(heap, 1, &values[0]);
	new_element = fibonacci_heap_insert(heap, 5, &values[2]);
	new_element = fibonacci_heap_insert(heap, 6, &values[3]);
	fibonacci_heap_delete_min(heap);
	fibonacci_heap_delete_min(heap);
	EXPECT_EQ(true, fibonacci_heap_get_min(heap, &key, &item_ptr));
	EXPECT_TRUE(NULL != item_ptr);
	EXPECT_EQ(5, key);
	EXPECT_EQ(values[2], *(char*)item_ptr);
	EXPECT_EQ(5, ((fibonacci_heap_tree_node*)(heap->min_root->obj))->key);
}

TEST(FibonacciHeapTest, InsertThenDecreaseKey)
{
	fibonacci_heap* heap = fibonacci_heap_create();
	char values[3] = { 'a', 'b', 'c' };
	void* item_ptr = NULL;
	int key = -1;
	EXPECT_TRUE(NULL != heap);
	fibonacci_heap_tree_node* new_element = fibonacci_heap_insert(heap, 2, &values[1]);
	new_element = fibonacci_heap_insert(heap, 1, &values[0]);
	fibonacci_heap_tree_node*  last_element = fibonacci_heap_insert(heap, 5, &values[2]);
	fibonacci_heap_decrease_key_node(heap,last_element,0);
	EXPECT_EQ(true, fibonacci_heap_get_min(heap, &key, &item_ptr));
	EXPECT_TRUE(NULL != item_ptr);
	EXPECT_EQ(0, key);
	EXPECT_EQ(values[2], *(char*)item_ptr);
	EXPECT_EQ(0, ((fibonacci_heap_tree_node*)(heap->min_root->obj))->key);
}