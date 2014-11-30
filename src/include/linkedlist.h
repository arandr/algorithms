#include <stdlib.h>

typedef struct linkedlist{
	struct linkedlist* prev;
	struct linkedlist* next;
	void* obj;
} linkedlist;

typedef void(*list_iterator_func)(void* obj);

linkedlist* linkedlist_create(void);

void linkedlist_foreach(linkedlist* object, list_iterator_func function);

void linkedlist_collect(linkedlist* object, void** objs);

linkedlist* linkedlist_append(linkedlist* object, void* obj);

void linkedlist_destroy(linkedlist* object);