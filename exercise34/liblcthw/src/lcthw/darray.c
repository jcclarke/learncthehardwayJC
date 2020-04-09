#include <darray.h> 
#include <assert.h>


// create new dynamic array
DArray *DArray_create(size_t element_size, size_t initial_max)
{
	DArray *array				= malloc(sizeof(DArray));
	check_mem(array);	
	array->max					= initial_max;
	check(array->max > 0,"You must enter an initial_max > 0.");
	
	array->contents				= calloc(initial_max, sizeof(void *));
	check_mem(array->contents);

	array->end					= 0;
	array->element_size			= element_size;
	array->expand_rate			= DEFAULT_EXPAND_RATE;

	return array;

error:
	if (array) free (array);
	return NULL;
}



// clear all array contents
void DArray_clear(DArray *array)
{
	int i						= 0;
	if (array->element_size > 0){
		for (i = 0; i < array->max; i ++){
			if (array->contents[i] != NULL){
				free (array->contents[i]);
			}
		}
	}
}


// destroy current dynamic array
void DArray_destroy(DArray *array)
{
	if (array){
		if (array->contents){
			free(array->contents);
		}
		free(array);
	}
}


// clear array list contents and destroy current dynamic array
void DArray_clear_destroy(DArray *array)
{
	DArray_clear(array);
	DArray_destroy(array);
}


//resize the dynamic array
static inline int DArray_resize(DArray *array, size_t new_size)
{
	array->max					= new_size;
	check(array->max > 0, "The new size must be > 0.");

	void *contents				= realloc(array->contents, array->max * sizeof(void *));

	// check contents and assume realloc doesn't harm the original on error
	check_mem(contents);

	array->contents				= contents;

	return 0;
error:
	return -1;
}


// expand the size of the dynamic array
int DArray_expand(DArray *array)
{
	size_t old_max				= array->max;
	check(DArray_resize(array, array->max + array->expand_rate) == 0, "Failed to expand array from %d, to new size: %d", old_max, array->max + (int)array->expand_rate);


	memset(array->contents + old_max, 0, array->expand_rate + 1);

	return 0;

error:
	return -1;
}


// expand the size of the dynamic array
int DArray_contract(DArray *array)
{
	int new_size				= array->end < (int)array->expand_rate ? (int)array->expand_rate : array->end;
		
	return DArray_resize(array, new_size + 1);
}


// add(push) new value to end of dynamic array. 
int DArray_push(DArray *array,void *el)
{
	array->contents[array->end]	= el;
	array->end++;

	if(DArray_end(array) >= DArray_max(array)){
		return DArray_expand(array);
	}else{
		return 0;
	}
}


// remove(shift) value from the end of the dynamic array
void *DArray_pop(DArray *array){
	check(array->end - 1 >= 0, "ERROR. Tried to pop from empty array.");

	void *el					= DArray_remove(array, array->end - 1);
	array->end--;

	if(DArray_end(array) > (int)array->expand_rate && DArray_end(array) % array->expand_rate){
		DArray_contract(array);
	}
	
	return el;
error:
	return NULL;	
}
