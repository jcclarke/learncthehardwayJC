#include "minunit.h"
#include <list.h>
#include <assert.h>



static List *list	= NULL;
char *test1			= "test1 data";
char *test2			= "test2 data";
char *test3			= "test3 data";

//extra credit
static List *list1	= NULL;
char *test4			= "test4 data";
char *test5			= "test5 data";
char *test6			= "test6 data";



char *test_create()
{
	list			= List_create();
	mu_assert(list != NULL, "Failed to create list.");

	return NULL;
}



char *test_create1()
{
	list1			= List_create();
	mu_assert(list1 != NULL, "Failed to create list.");

	return NULL;
}



char *test_destroy()
{
	List_clear_destroy(list);

	return NULL;
}



char *test_destroy1()
{
	List_clear_destroy(list1);

	return NULL;
}



char *test_push()
{
	List_push(list, test1);
	mu_assert(List_last(list) == test1, "Wrong last value after push 1.");

	List_push(list, test2);
	mu_assert(List_last(list) == test2, "Wrong last value after push 2.");

	List_push(list, test3);
	mu_assert(List_last(list) == test3, "Wrong last value after push 3.");
	mu_assert(List_count(list) == 3, "Wrong count after push. \nShould be 3.");

	return NULL;
}



// Extra Credit function
char *test_copy()
{
	list1			= List_copy(list);
	mu_assert(List_count(list1) == 3, "Wrong count after copy. \nShould be 3.");
	mu_assert(List_first(list1) == test1, "Wrong first value after copy.");
	mu_assert(List_last(list1) == test3, "Wrong last value after copy.");

	return NULL;
}



char *test_unshift()
{

	List_unshift(list1, test4);
	mu_assert(List_first(list1) == test4, "Wrong first value after unshift 1.");

	List_unshift(list1, test5);
	mu_assert(List_first(list1) == test5, "Wrong first value after unshift 2.");

	List_unshift(list1, test6);
	mu_assert(List_first(list1) == test6, "Wrong first value after unshift 3.");
	mu_assert(List_count(list1) == 3, "Wrong count after unshift. \nShould be 3.");

	return NULL;
}




// Extra Credit function
char *test_join()
{
	List_join(list, list1);
	mu_assert(List_count(list) == 6, "Wrong count after copy. \nShould be 3.");
	mu_assert(List_first(list) == test1, "Wrong first value after copy.");
	mu_assert(List_last(list) == test4, "Wrong last value after copy.");

	return NULL;
}



char *test_remove_middle()
{
	// only the middle remove needs to be tested as other cases tested already
	
	char * val		= List_remove(list1, list1->first->next);		
	mu_assert(val == test5, "Wrong value after remove middle. \n should be test5.");
	mu_assert(List_count(list1) == 2, "Wrong count after remove middle. \nShould be 2.");
	mu_assert(List_first(list1) == test6, "Wrong first value after remove middle.");
	mu_assert(List_last(list1) == test4, "Wrong last value after remove middle.");

	return NULL;
}



// Extra Credit function
// List_split
char *test_split()
{
	List_split(list, list1, list->last->prev);
	mu_assert(List_count(list) == 4, "List has wrong count after split. \nShould be 4.");
	mu_assert(List_count(list1) == 2, "List1 has wrong count after split. \nShould be 2.");
	mu_assert(List_first(list) == test1, "List has wrong first value after split.");
	mu_assert(List_first(list1) == test5, "List1 has wrong first value after split.");
	mu_assert(List_last(list) == test6, "List has wrong last value after split.");
	mu_assert(List_last(list1) == test4, "List1 has wrong last value after split.");

	return NULL;
}



char *test_pop()
{
	char *val		= List_pop(list);
	mu_assert(val == test6, "Wrong value after pop. \n should be test6.");

	val				= List_pop(list);
	mu_assert(val == test3, "Wrong value after pop. \n should be test3.");

	val				= List_pop(list);
	mu_assert(val == test2, "Wrong value after pop. \n should be test2.");
	mu_assert(List_count(list) == 1, "Wrong count after pop. \nShould be 0.");

	return NULL;
}



char *test_shift()
{
	mu_assert(List_count(list1) != 0, "Wrong count before shift. \nShould be 2.");

	char *val		= List_shift(list1);
	mu_assert(val == test5, "Wrong value after shift. \n should be test5.");

	val				= List_shift(list1);
	mu_assert(val == test4, "Wrong value after shift. \n should be test4.");
	mu_assert(List_count(list1) == 0, "Wrong count after shift. \nShould be 0.");

	return NULL;
}



char *test_print()
{
	printf("\nlist: ");
	List_print(list);
	printf("\nlist1: ");
	List_print(list1);

	return NULL;
}



char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_create1);
	mu_run_test(test_push);
	mu_run_test(test_copy);
	mu_run_test(test_destroy1);
	mu_run_test(test_create1);
	mu_run_test(test_unshift);
	mu_run_test(test_print);
	mu_run_test(test_join);
	mu_run_test(test_print);
// insert the following tests in this order
// List_split
	mu_run_test(test_remove_middle);
	mu_run_test(test_destroy1);
	mu_run_test(test_create1);
	mu_run_test(test_split);
	mu_run_test(test_print);
	mu_run_test(test_pop);
	mu_run_test(test_shift);
	mu_run_test(test_destroy);

	return NULL;
}



RUN_TESTS(all_tests);
