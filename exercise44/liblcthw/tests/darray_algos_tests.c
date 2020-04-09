#include "minunit.h"
#include <darray_algos.h>



int testcmp(char **a, char **b)
{
	return strcmp(*a, *b);
}



DArray *create_words()
{
	DArray *result			= DArray_create(0, 10);
	char *words[]			= {"asdfasfd", "werwar", "13234", "asdfasfd", "OiOj", "w_123", "_H1mg", "WERWAR", "924813", "oioj"};
	int	i					= 0;

	for (i = 0; i < 10;  i++){
		DArray_push(result, words[i]);	
	}

	return result;
}



int is_sorted(DArray *array)
{
	int i					= 0;

	for (i = 0; i < DArray_count(array) - 1; i++){
		if(strcmp(DArray_get(array, i), DArray_get(array, i+1)) > 0){
			return 0;
		}
	}
	return 1; 
}



char *run_sort_test(int (*func)(DArray *, DArray_compare), const char *name)
{
	DArray *words			= create_words();
	mu_assert(!is_sorted(words), "Words should start unsorted");

	debug("--- Testing %s sorting algorithm", name);
	
	// added to select which compare to use
	char my[3]			= "hi";
	strncpy(my, name, 2);
	int rc					= 0;
	// use strcmp for my sorting libraries
	if(strcmp(my, "my") == 0){
		rc					= func(words, (DArray_compare)strcmp);
	// use testcmp for libbsd sorting libraries
	}else{
		rc					= func(words, (DArray_compare)testcmp);
	}

//	int i = 0;
//	if((strcmp(name, "my_mergesort") == 0) || (strcmp(name, "my_heapsort") == 0)){
//		for (i = 0; i < DArray_count(words); i++){
//			printf("\n\nvalue %d is %s\n",i ,(char *)DArray_get(words ,i));
//		}
//	}
	mu_assert(rc == 0, "Sort Failed");
	mu_assert(is_sorted(words), "Words were not sorted.");

	DArray_destroy(words);

	return NULL;
}



char *test_quicksort()
{
	return run_sort_test(DArray_quicksort, "quicksort");
}



char *test_heapsort()
{
	return run_sort_test(DArray_heapsort, "heapsort");
}



char *test_mergesort()
{
	return run_sort_test(DArray_mergesort, "mergesort");
}



//extra credit
char *test_my_quicksort()
{
	return run_sort_test(DArray_my_quicksort, "my_quicksort");
}



char *test_my_heapsort()
{
	return run_sort_test(DArray_my_heapsort, "my_heapsort");
}



char *test_my_mergesort()
{
	return run_sort_test(DArray_my_mergesort, "my_mergesort");
}



char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_quicksort);
	mu_run_test(test_heapsort);
	mu_run_test(test_mergesort);

	// extra credit
	mu_run_test(test_my_quicksort);
	mu_run_test(test_my_heapsort);
	mu_run_test(test_my_mergesort);

	return NULL;
}



RUN_TESTS(all_tests);
