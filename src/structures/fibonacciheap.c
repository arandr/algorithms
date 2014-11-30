#include "fibonacciheap.h"

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
	linkedlist* last = object->prev;
	last->next = linkedlist_create();
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

/* private functions */
static fibonacci_heap_tree_node* fibonacci_heap_tree_node_create(void)
{
	fibonacci_heap_tree_node* node = (fibonacci_heap_tree_node*)malloc(sizeof(fibonacci_heap_tree_node));
	node->children = NULL;
	node->item = NULL;
	node->key = 0;
	node->n_children = 0;
	node->marked = BOOL_FALSE;
	return node;
}

static void fibonacci_heap_tree_node_destroy(fibonacci_heap_tree_node* object)
{
	linkedlist_foreach(object->children, &fibonacci_heap_tree_node_destroy);
	linkedlist_destroy(object->children);
	free(object);
}

/* API functions */
fibonacci_heap* fibonacci_heap_create(void)
{
	fibonacci_heap* heap = (fibonacci_heap*)malloc(sizeof(fibonacci_heap));
	if (heap == NULL) return heap;
	heap->min_root = NULL;
	heap->n_roots = 0;
	return heap;
}

boolean_t fibonacci_heap_get_min(fibonacci_heap* object, int* key, void** item)
{
	if (object == NULL || object->n_roots == 0) return BOOL_FALSE;
	*key = ((fibonacci_heap_tree_node*)(object->min_root->obj))->key;
	*item = ((fibonacci_heap_tree_node*)(object->min_root->obj))->item;
	return BOOL_TRUE;
}

fibonacci_heap_tree_node* fibonacci_heap_insert(fibonacci_heap* object, int key, void* item)
{
	fibonacci_heap_tree_node* new_root = fibonacci_heap_tree_node_create();
	linkedlist* new_list = NULL;
	new_root->item = item;
	new_root->key = key;
	if (object->n_roots == 0){
		new_list = object->min_root = linkedlist_create();
		object->min_root->obj = new_root;
	} else {
		new_list = linkedlist_append(object->min_root, new_root);
	}
	if (((fibonacci_heap_tree_node*)(object->min_root->obj))->key > key) object->min_root = new_list;
	++object->n_roots;
	return new_root;
}

void fibonacci_heap_insert_node(fibonacci_heap* object, fibonacci_heap_tree_node* node)
{
	linkedlist* new_list;
	if (object->n_roots == 0){
		new_list = object->min_root = linkedlist_create();
		object->min_root->obj = node;
	}
	else {
		new_list = linkedlist_append(object->min_root, node);
	}
	if (((fibonacci_heap_tree_node*)(object->min_root->obj))->key > node->key) object->min_root = new_list;
	++object->n_roots;
}

void fibonacci_heap_delete(fibonacci_heap* object, void* item)
{

}

void fibonacci_heap_delete_node(fibonacci_heap* object, fibonacci_heap_tree_node* node)
{

}

void fibonacci_heap_decrease_key(fibonacci_heap* object, void* item, int new_key)
{

}

void fibonacci_heap_decrease_key_node(fibonacci_heap* object, fibonacci_heap_tree_node* node, int new_key)
{

}

/* Reduces the number of tree roots in the heap by enforcing that there be at most one root of a given degree (number of children). 
   This is only done when deleting the minimum element, *not* at insert time. */
static void fibonacci_heap_consolidate(fibonacci_heap* object)
{
	linkedlist* current = object->min_root;
	linkedlist** degree_roots_map = (linkedlist**)calloc(object->n_roots,sizeof(linkedlist*)); //technically can be bound to log (n of elements), but we don't keep the total count of elements handy.
	linkedlist* to_destroy_list_node = NULL;
	while (current->next != object->min_root){
		size_t degree = ((fibonacci_heap_tree_node*)(current->obj))->n_children;
		if (degree_roots_map[degree] == NULL){
			degree_roots_map[degree] = current;
			current = current->next;
		} else { //found two trees where the roots have the same degree, must merge them
			if (((fibonacci_heap_tree_node*)(degree_roots_map[degree]->obj))->key < ((fibonacci_heap_tree_node*)(current->obj))->key){
				to_destroy_list_node = current;
				linkedlist_append(((fibonacci_heap_tree_node*)(degree_roots_map[degree]->obj))->children, current->obj);
				((fibonacci_heap_tree_node*)(degree_roots_map[degree]->obj))->n_children++;
				current = degree_roots_map[degree];
				degree_roots_map[degree] = NULL;
			} else {
				to_destroy_list_node = degree_roots_map[degree];
				linkedlist_append(((fibonacci_heap_tree_node*)(current->obj))->children, degree_roots_map[degree]->obj);
				((fibonacci_heap_tree_node*)(current->obj))->n_children++;
				degree_roots_map[degree] = NULL;
			}
			to_destroy_list_node->prev->next = to_destroy_list_node->next;
			to_destroy_list_node->next->prev = to_destroy_list_node->prev;
			to_destroy_list_node->prev = to_destroy_list_node->next = NULL;
			linkedlist_destroy(to_destroy_list_node);
			--object->n_roots;
		}
	}
}

void fibonacci_heap_delete_min(fibonacci_heap* object)
{
	if (object->n_roots == 0) return;
	linkedlist* next_min_root = object->min_root->next;
	fibonacci_heap_tree_node* deleted_node = object->min_root->obj;
	object->min_root->next->prev = object->min_root->prev;
	object->min_root->prev->next = object->min_root->next;
	object->min_root->prev = object->min_root->next = NULL;
	linkedlist_destroy(object->min_root);
	--object->n_roots;
	object->min_root = next_min_root;
	/*while (current->next != next_min_root){
		if (((fibonacci_heap_tree_node*)(current->obj))->key < ((fibonacci_heap_tree_node*)(object->min_root->obj))->key) object->min_root = current;
		current = current->next;
	}*/
	fibonacci_heap_tree_node** new_roots = (fibonacci_heap_tree_node**)malloc(deleted_node->n_children * sizeof(fibonacci_heap_tree_node*));
	linkedlist_collect(deleted_node->children, new_roots);
	for (size_t i = 0; i < deleted_node->n_children; i++) fibonacci_heap_insert_node(object, new_roots[i]);
	linkedlist_destroy(deleted_node->children);
	deleted_node->children = NULL;
	fibonacci_heap_tree_node_destroy(deleted_node);
	fibonacci_heap_consolidate(object);
}

void fibonacci_heap_destroy(fibonacci_heap* object)
{
	if (NULL == object) return;
	linkedlist_foreach(object->min_root, &fibonacci_heap_tree_node_destroy);
	linkedlist_destroy(object->min_root);
	free(object);
}