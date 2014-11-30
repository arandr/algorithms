#include "linkedlist.h"

linkedlist* linkedlist_create(void)
{
	linkedlist* list = (linkedlist*)malloc(sizeof(linkedlist));
	list->next = list;
	list->prev = list;
	list->obj = NULL;
	return list;
}

void linkedlist_foreach(linkedlist* object, list_iterator_func function)
{
	linkedlist* current = object;
	if (current == NULL) return;
	do{
		function(current->obj);
		current = current->next;
	} while (current != object);
}

void linkedlist_collect(linkedlist* object, void** objs)
{
	linkedlist* current = object;
	if (current == NULL) return;
	size_t n = 0;
	do{
		objs[n++] = current->obj;
	} while (current != object);
}

linkedlist* linkedlist_append(linkedlist* object, void* obj)
{
	linkedlist* last = object != NULL ? object->prev : linkedlist_create();
	if(object != NULL) last->next = linkedlist_create();
	else last->next = object = last;
	last->next->obj = obj;
	last->next->prev = last;
	last->next->next = object;
	object->prev = last->next;
	return object->prev;
}

void linkedlist_destroy(linkedlist* object)
{
	linkedlist* current = object;
	if (current == NULL) return;
	if (current->next == object){
		free(object);
		return;
	}
	do{
		current = current->next;
		free(current->prev);
	} while (current->next != object);
}