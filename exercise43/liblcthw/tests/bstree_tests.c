#include "minunit.h"
#include <bstree.h>
#include <assert.h>
#include <bstrlib.h>
#include <stdlib.h>
#include <time.h>



BSTree *map						= NULL;
static int traverse_called		= 0;
// create static bstrings
struct tagbstring test1			= bsStatic("test data 1");
struct tagbstring test2			= bsStatic("test data 2");
struct tagbstring test3			= bsStatic("test data 3");
struct tagbstring expect1		= bsStatic("THE VALUE 1");
struct tagbstring expect2		= bsStatic("THE VALUE 2");
struct tagbstring expect3		= bsStatic("THE VALUE 3");


static int traverse_good_cb(BSTreeNode *node)
{
	debug("KEY: %s", bdata((bstring)node->key));
	traverse_called++;
	return 0;
}


static int traverse_fail_cb(BSTreeNode *node)
{
	debug("KEY: %s", bdata((bstring)node->key));
	traverse_called++;
	
	if (traverse_called == 2) {
		return 1;
	} else {
		return 0;
	}
}


char *test_create()
{
	map							= BSTree_create(NULL);
	mu_assert(map != NULL, "Failed to create bstree map.");

	return NULL;
}



char *test_destroy()
{
	BSTree_destroy(map);

	return NULL;
}


char *test_get_set()
{
	int rc						= BSTree_set(map, &test1, &expect1);
	mu_assert(rc == 0, "Failed to set &test1.");
	bstring result				= BSTree_get(map, &test1);
	mu_assert(result == &expect1, "Wrong value for test1.");

	rc							= BSTree_set(map, &test2, &expect2);
	mu_assert(rc == 0, "Failed to set &test2.");
	result						= BSTree_get(map, &test2);
	mu_assert(result == &expect2, "Wrong value for test2.");

	rc							= BSTree_set(map, &test3, &expect3);
	mu_assert(rc == 0, "Failed to set &test3.");
	result						= BSTree_get(map, &test3);
	mu_assert(result == &expect3, "Wrong value for test3.");

	return NULL;
}


char *test_traverse()
{
	int rc						= BSTree_traverse(map, traverse_good_cb);
	mu_assert(rc == 0, "Failed to traverse.");
	mu_assert(traverse_called == 3, "Wrong count traverse.");

	traverse_called				= 0;
	rc							= BSTree_traverse(map, traverse_fail_cb);
	mu_assert(rc == 1, "Failed to traverse.");
	mu_assert(traverse_called == 2, "Wrong count traverse for fail.");

	return NULL;
}


char *test_delete()
{
	bstring deleted				= (bstring)BSTree_delete(map, &test1);
	mu_assert(deleted != NULL, "Got NULL on delete.");
	mu_assert(deleted == &expect1, "Should get test1.");
	bstring result				= BSTree_get(map, &test1);
	mu_assert(result == NULL, "Should be deleted.");

	deleted				= (bstring)BSTree_delete(map, &test1);
	mu_assert(deleted == NULL, "Should get NULL on delete.");
	
	deleted						= (bstring)BSTree_delete(map, &test2);
	mu_assert(deleted != NULL, "Got NULL on delete.");
	mu_assert(deleted == &expect2, "Should get test2.");
	result						= BSTree_get(map, &test2);
	mu_assert(result == NULL, "Should be deleted.");

	deleted						= (bstring)BSTree_delete(map, &test3);
	mu_assert(deleted != NULL, "Got NULL on delete.");
	mu_assert(deleted == &expect3, "Should get test3.");
	result						= BSTree_get(map, &test3);
	mu_assert(result == NULL, "Should be deleted.");

	// test deleting non-existing stuff
	deleted				= (bstring)BSTree_delete(map, &test3);
	mu_assert(deleted == NULL, "Should get NULL on delete.");
	
	return NULL;
}


char *test_fuzzing()
{
	BSTree *store				= BSTree_create(NULL);
	int i						= 0;
	int j						= 0;
	bstring numbers[100]		= {NULL};
	bstring data[100]			= {NULL};
	srand((unsigned int)time(NULL));

	// put 100 data in
	for (i = 0; i < 100; i++) {
		int num					= rand();
		numbers[i]				= bformat("%d", num);
		data[i]					= bformat("data: %d", num);
		BSTree_set(store, numbers[i], data[i]);
	}

	// now destroy all the data 1 by 1.
	for (i = 0; i < 100; i++) {
		bstring value			= BSTree_delete(store, numbers[i]);
		mu_assert(value == data[i], "Failed to delete the right number.");

		mu_assert(BSTree_delete(store, numbers[i]) == NULL, "Should get NULL.");

		// check ahead to make sure all remaining values are still in the bstree.
		//for (j = i+1; j < 99 -i; j++)  // 99 - i make no difference in whether the code runs error free.
		for (j = i+1; j < 100; j++) {
			bstring value_in	= BSTree_get(store, numbers[j]);
			mu_assert(value_in == data[j], "failed to get the correct number.");
		}

		bdestroy(value);
		bdestroy(numbers[i]);
	}

	BSTree_destroy(store);

	return NULL;
}


char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_get_set);
	mu_run_test(test_traverse);
	mu_run_test(test_delete);
	mu_run_test(test_destroy);
	mu_run_test(test_fuzzing);

	return NULL;
}



RUN_TESTS(all_tests);
