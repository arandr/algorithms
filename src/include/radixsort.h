#include <stdlib.h>
#include <string.h>

typedef struct array_type{
	int* data;
	size_t size;
} array_type;

void sort_radix(array_type* sorted_array, array_type* to_sort_array);