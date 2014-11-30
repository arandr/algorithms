#include <stdlib.h>

typedef struct linkedlist{
	struct linkedlist* prev;
	struct linkedlist* next;
	void* obj;
} linkedlist;

typedef void(*list_iterator_func)(void* obj);

linkedlist* linkedlist_create(void);

void linkedlist_foreach(linkedlist* object, list_iterator_func function);

void linkedlist_destroy(linkedlist* object);

typedef enum{
	BOOL_FALSE = 0,
	BOOL_TRUE
} boolean_t;

typedef struct fibonacci_heap_tree_node{
	linkedlist* children;
	short n_children; //degree of heap nodes is supposed to be low, we can save space here
	boolean_t marked;
	int key;
	void* item;
} fibonacci_heap_tree_node;

typedef struct fibonacci_heap{
	linkedlist* min_root;
	size_t n_roots;
} fibonacci_heap;

fibonacci_heap* fibonacci_heap_create(void);

boolean_t fibonacci_heap_get_min(fibonacci_heap* object, int* key, void** item);

fibonacci_heap_tree_node* fibonacci_heap_insert(fibonacci_heap* object, int key, void* item);

void fibonacci_heap_delete(fibonacci_heap* object, void* item);

void fibonacci_heap_delete_node(fibonacci_heap* object, fibonacci_heap_tree_node* node);

void fibonacci_heap_decrease_key(fibonacci_heap* object, void* item, int new_key);

void fibonacci_heap_decrease_key_node(fibonacci_heap* object, fibonacci_heap_tree_node* node, int new_key);

void fibonacci_heap_delete_min(fibonacci_heap* object);

/* This call frees the object memory, i.e. the pointer is no longer valid after being destructed. */
void fibonacci_heap_destroy(fibonacci_heap* object);