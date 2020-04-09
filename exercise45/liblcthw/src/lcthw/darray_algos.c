#include <darray_algos.h> 
#include <assert.h>
#include <dbg.h>
#include <stdlib.h>




int DArray_quicksort(DArray *array, DArray_compare cmp)
{
	qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
	return 0;
}

int DArray_heapsort(DArray *array, DArray_compare cmp)
{
	return heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
	return mergesort(array->contents, DArray_count(array), sizeof(void *), cmp);
}




//extra credit
// swap elements
void DArray_swap(DArray *array, int a, int b){
	void *temp				= DArray_get(array, a);
	DArray_set(array, a, DArray_get(array, b));
	DArray_set(array, b, temp);
}


// error check before sorting
int DArray_check_b4_sort(DArray *array)
{
	check(array, "DArray is NULL, doesn't exists.");
	check(DArray_max(array) > 0, "The size must be > 0.");
	check(DArray_end(array) > 0, "The size must be > 0.");

	return 0;
error:
	return -1;
}



// my quick sort
/*	----------------------------------------------------------------------------------
	Simple implementation of quicksort
	----------------------------------------------------------------------------------
*/
int DArray_my_quicksort(DArray *array, DArray_compare cmp)
{
	int rc					= DArray_check_b4_sort(array);
	check(rc == 0, "DArray failed checks before quick sorting.");

	int lo					= 0;
	int hi					= DArray_count(array) - 1;

	DArray_my_qsort(array, lo, hi, cmp);

	return 0;

error:
	return -1;
}

void DArray_my_qsort(DArray *array, int lo, int hi, DArray_compare cmp)
{
	if (lo < hi){
		
		// partition index
		int part			= DArray_partition(array, lo, hi, cmp);

		// sort elements to the left and right of "part" recursively
		DArray_my_qsort(array, lo, part - 1, cmp);
		DArray_my_qsort(array, part + 1, hi, cmp);

	}
}

int DArray_partition(DArray *array, int lo, int hi, DArray_compare cmp)
{
	int i					= lo;
	int j					= 0;
	void *pivot				= DArray_get(array, hi);

	for (j = lo; j < hi; j++){
		
		if (cmp(DArray_get(array, j), pivot) < 0){
		//printf("\n\npivot is  %s\n\n", (char *)pivot);
			DArray_swap(array, i, j);
			i++;
		}
	}

	DArray_swap(array, i, hi);

	return i;
}



// my heap sort
/*	----------------------------------------------------------------------------------
	Simple implementation of heapsort
	----------------------------------------------------------------------------------
*/
int DArray_my_heapsort(DArray *array, DArray_compare cmp)
{
	int rc					= DArray_check_b4_sort(array);
	check(rc == 0, "DArray failed checks before heap sorting.");
	
	int i					= 0;
	int N					= DArray_count(array);

	// initial max heap (largest element on top)
	for (i = N/2 - 1; i >= 0; i--){
		heapify(array, i, N, cmp);
	}

	// heap sort
	for (i = (N-1); i >= 0; i--){
		
		// swap initial and final values
		DArray_swap(array, 0, i);

		// heapify to get max heap again
		heapify(array, 0, i, cmp);
	}

	return 0; 
error:
	return -1;
}

void heapify(DArray *array, int i, int N, DArray_compare cmp)
{
	// root and left child
	int new_root			= i;
	int left				= 2*i + 1;

	// determine the new root
	if (left < N && cmp(DArray_get(array, new_root), DArray_get(array, left)) < 0){
		new_root			= left;
	}

	if ((left + 1) < N && cmp(DArray_get(array, new_root), DArray_get(array, left + 1)) < 0){
		new_root			= left + 1;
	}

	if (new_root != i){

		DArray_swap(array, new_root, i);

		// recursive heapify 
		heapify(array, new_root, N, cmp);
	}
}



//my merge sort
/*	----------------------------------------------------------------------------------
	Two copies of DArray struct or DA_copy array are needed for this wikipedia version
	of the algorithm to work. This is because for each recursive split_n_merge call
	the array parameters must be swapped in the function call. 
	----------------------------------------------------------------------------------
*/
int DArray_my_mergesort(DArray *array, DArray_compare cmp)
{
	int rc					= DArray_check_b4_sort(array);
	check(rc == 0, "DArray failed checks before quick sorting.");

	int i					= 0;
	int N					= DArray_count(array);
	
/*	
//	one time copy of DArray into an DA-copy won't work  
//	ie. DA_copy is array and array is DA_copy
//	can be modified to copy to a DArray struct. Explore benefits before implementing.

	void **DA_copy	= malloc(N * sizeof(void *));
	void **DA_copy2	= malloc(N * sizeof(void *));
	check_mem(DA_copy);
	for (i = 0; i < N; i++){
		DA_copy[i]	= DArray_get(array, i);
		DA_copy2[i]	= DArray_get(array, i);
	}
*/
	
	// One time copy of DArray array into DArray array_copy
	DArray *array_copy		= DArray_create(sizeof(void *), N);
	check_mem(array_copy);
	for (i = 0; i < N; i++){
		// may have to do some error checking here
//		printf("\n---\ni = %d; array_copy[%d] = %s", i, i, (char *)DArray_get(array, i));
		DArray_set(array_copy, i, DArray_get(array, i));
	}
	

	// split and merge
	split_n_merge(array_copy, 0, N, array, cmp);													//B,...,A

	// free array_copy
	DArray_destroy(array_copy);
/*
	// clear DA_copy memory
	free(DA_copy);
*/

	return 0;

error:
	return 1;
}

// Sort the given run of array using array_cpy as its source
void split_n_merge(DArray *array_copy, int begin, int end, DArray *array, DArray_compare cmp)		//B,...,A
{
	// don't try to split arrays size 1. already sorted.
	if (end - begin < 2){
		return;
	}
	
	// Find mid point and recursively sort (split and merge) from "array" into "array_copy"
	int middle		= (end + begin)/2;
	split_n_merge(array, begin, middle, array_copy, cmp);											//A,...,B
	split_n_merge(array, middle, end, array_copy, cmp);												//A,...,B

	// now merge the resulting runs from "array_copy" into "array"
	merge(array_copy, begin, middle, end, array, cmp);												//B,...,A
}

void merge(DArray *array, int begin, int middle, int end, DArray *array_copy, DArray_compare cmp)	//A,...,B
{
	// left and right array indices
	int i			= begin;
	int j			= middle;

	int k			= 0;
//	printf("\n---\ncase begin = %d; middle = %d; end = %d\n---\n", begin, middle, end);
	
	for (k = begin; k < end; k++){
		
		// if there are left array elements && ( no more right array elements || left[i] < right[j] )
		if (i < middle && ((j >= end ) || (cmp(DArray_get(array, i), DArray_get(array, j)) < 0))){
//			printf("left --- \nk = %d; array[%d] = %s;\n", k, i, (char *)DArray_get(array, i));
			DArray_set(array_copy, k, DArray_get(array, i));
			i++;
		}else{
//			printf("right--- \nk = %d; array[%d] = %s;\n", k, j, (char *)DArray_get(array, j));
			DArray_set(array_copy, k, DArray_get(array, j));
			j++;
		}
	}
}

