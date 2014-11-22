#include "radixsort.h"

void sort_radix(array_type* sorted_array, array_type* to_sort_array)
{
	size_t counts[8][16] = { 0 }; //assumes 4-byte int
	size_t filled_buckets[8] = { 0 };
	for (size_t i = 0; i < to_sort_array->size; i++){
		for (unsigned char j = 0; j < 8; j++){
			unsigned char bucket = (unsigned char)((((unsigned int)(to_sort_array->data[i] ^ (1<<31))) << (7 - j) * 4) >> 28);
			++counts[j][bucket];
			++filled_buckets[j];
		}
	}
	int * buckets = (int*)malloc((filled_buckets[0] + filled_buckets[1] + filled_buckets[2] + filled_buckets[3] + filled_buckets[4] + filled_buckets[5] + filled_buckets[6] + filled_buckets[7])*sizeof(int));
	size_t offsets[8][16] = { 0 };
	for (unsigned char j = 0; j < 8; ++j){
		for (size_t i = 0; i < to_sort_array->size; ++i){
			unsigned char b_index = 0;
			for (unsigned char k = 0; k < j - 1; ++k) b_index += filled_buckets[k];
			int element = j == 0 ? to_sort_array->data[i] : buckets[b_index + i];
			unsigned char bucket = (unsigned char)((((unsigned int)(element ^ (1 << 31))) << (7 - j) * 4) >> 28);
			unsigned char k_index = 0;
			for (unsigned char k = 0; k < bucket; ++k) k_index += counts[j][k];
			b_index = 0;
			for (unsigned char k = 0; k < j; ++k) b_index += filled_buckets[k];
			k_index += offsets[j][bucket];
			++offsets[j][bucket];
			buckets[b_index + k_index] = element;
		}
	}
	size_t most_sig_bucket = (filled_buckets[0] + filled_buckets[1] + filled_buckets[2] + filled_buckets[3] + filled_buckets[4] + filled_buckets[5] + filled_buckets[6]);
	memcpy(sorted_array->data, buckets + most_sig_bucket, sorted_array->size*sizeof(int));
}