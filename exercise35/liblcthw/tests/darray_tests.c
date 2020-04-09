#include "minunit.h"
#include <darray.h>


static DArray *array	= NULL;
static int *val1		= NULL;
static int *val2		= NULL;

//extra credit



char *test_create()
{
	array				= DArray_create(sizeof(int), 100);
	mu_assert(array != NULL, "Failed to create darray.");
	mu_assert(array->contents != NULL, "Contents are wrong in darray after DArray_create.");
	mu_assert(array->end == 0, "end isn't at the right spot. Should be 0 after DArray_create.");
	mu_assert(array->element_size ==sizeof(int), "Element size is wrong after DArray_create.");
	mu_assert(array->max == 100, "Wrong max darray length on intial size after DArray_create.");


	return NULL;
}



char *test_destroy()
{
	DArray_destroy(array);

	return NULL;
}



char *test_new()
{
	val1				= DArray_new(array);
	mu_assert(val1 != NULL, "Failed to make a new element after DArray_new for val1.");

	val2				= DArray_new(array);
	mu_assert(val1 != NULL, "Failed to make a new element after DArray_new for val2.");

	return NULL;
}



char *test_set()
{
	DArray_set(array, 0, val1);
	DArray_set(array, 1, val2);

	return NULL;
}



char *test_get()
{
	mu_assert(DArray_get(array, 0) == val1, "Wrong first value.");
	mu_assert(DArray_get(array, 1) == val2, "Wrong second value.");

	return NULL;
}



char *test_remove()
{
	int *val_check		= DArray_remove(array, 0);
	mu_assert(val_check != NULL, "DArray_remove should not return NULL.");
	mu_assert(*val_check == *val1, "DArray_remove should return the frist value.");
	mu_assert(DArray_get(array, 0) == NULL, "Element 0 should be gone.");
	DArray_free(val_check);

	val_check		= DArray_remove(array, 1);
	mu_assert(val_check != NULL, "DArray_remove should not return NULL.");
	mu_assert(*val_check == *val2, "DArray_remove should return the frist value.");
	mu_assert(DArray_get(array, 1) == NULL, "Element 1 should be gone.");
	DArray_free(val_check);

	return NULL;
}



char *test_expand_contract()
{
	int old_max			= array->max;
	DArray_expand(array);
	mu_assert((unsigned int)array->max == old_max + array->expand_rate, "Wrong size after DArray_expand call.");

	DArray_contract(array);
	mu_assert((unsigned int)array->max == array->expand_rate + 1, "Should stay at the expand rate at least after the DArray_expand call.");

	DArray_contract(array);
	mu_assert((unsigned int)array->max == array->expand_rate + 1, "Should stay at the expand rate at least after the DArray_expand call.");

	return NULL;
}



char *test_push_pop()
{
	int i				= 0;
	for (i = 0; i < 1000; i++){
		int *val	= DArray_new(array);
		*val		= i * 333;
		DArray_push(array, val);
	}

	mu_assert(array->max == 1201, "Incorrect max size after DArray_push.");

	for (i = 999; i >= 0; i--){
		int *val	= DArray_pop(array);
		mu_assert(val != NULL, "DArray_pop should not return NULL.");
		mu_assert(*val == i * 333, "DArray_pop returned the wrong value.");
		DArray_free(val);
	}
	
	return NULL;
}



char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_new);
	mu_run_test(test_set);
	mu_run_test(test_get);
	mu_run_test(test_remove);
	mu_run_test(test_expand_contract);
	mu_run_test(test_push_pop);
	mu_run_test(test_destroy);

	return NULL;
}



RUN_TESTS(all_tests);
