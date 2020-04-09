#ifndef lcthw_darray_algos_h
#define lcthw_darray_algos_h

#include <darray.h>

typedef int (*DArray_compare)(const void *a, const void *b);

// sorting algorithms using bsd/stdlib.h
int DArray_quicksort(DArray *array, DArray_compare cmp);
int DArray_heapsort(DArray *array, DArray_compare cmp);
int DArray_mergesort(DArray *array, DArray_compare cmp);


// extra credit
// element swap
void DArray_swap(DArray *array, int a, int b);
// error check array before sorting
int DArray_check_b4_sort(DArray *array);

// my implementation of quick sort
int DArray_my_quicksort(DArray *array, DArray_compare cmp);
void DArray_my_qsort(DArray *array, int lo, int hi, DArray_compare cmp);
int DArray_partition(DArray *array, int lo, int hi, DArray_compare cmp);

// my implementation of heap sort
int DArray_my_heapsort(DArray *array, DArray_compare cmp);
void heapify(DArray *array, int i, int N, DArray_compare cmp);

// my implementation of mergesort sort
int DArray_my_mergesort(DArray *array, DArray_compare cmp);
void split_n_merge(DArray *array_copy, int begin, int end, DArray *array, DArray_compare cmp);
void merge(DArray *array, int begin, int middle, int end, DArray *array_copy, DArray_compare cmp);

#endif
