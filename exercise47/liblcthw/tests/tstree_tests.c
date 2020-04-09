#include "minunit.h"
#include <assert.h>
#include <bstrlib.h>
#include <string.h>
#include <tstree.h>



TSTree *node				= NULL;
char *ValueA				= "VALUEA";
char *ValueB				= "VALUEB";
char *Value2				= "VALUE2";
char *Value4				= "VALUE4";
char *Reverse				= "VALUER";
int traverse_count			= 0;

struct tagbstring test1		= bsStatic("TEST");
struct tagbstring test2		= bsStatic("TEST2");
struct tagbstring test3		= bsStatic("TSET");
struct tagbstring test4		= bsStatic("T");


char *test_insert()
{
	node					= TSTree_insert(node, bdata(&test1), blength(&test1), ValueA);
	mu_assert(node != NULL, "Failed to insert into tstree.");
	debug("\nchar 1: %c, char 2: %c, char 3: %c, char 4: %c, value node 4: %s\n", 
			node->splitchar,
			node->equal->splitchar,
			node->equal->equal->splitchar,
			node->equal->equal->equal->splitchar,
			(char *)node->equal->equal->equal->value); 

	node					= TSTree_insert(node, bdata(&test2), blength(&test2), Value2);
	mu_assert(node != NULL, "Failed to insert into tstree with second name.");
	debug("\nchar 1: %c, char 2: %c, char 3: %c, char 4: %c, value node 4: %s, char 5: %c, value node 5: %s\n", 
			node->splitchar,
			node->equal->splitchar,
			node->equal->equal->splitchar,
			node->equal->equal->equal->splitchar,
			(char *)node->equal->equal->equal->value, 
			node->equal->equal->equal->equal->splitchar,
			(char *)node->equal->equal->equal->equal->value); 

	node					= TSTree_insert(node, bdata(&test3), blength(&test3), Reverse);
	mu_assert(node != NULL, "Failed to insert into tstree with reverse name.");
	debug("\nchar 1: %c, char 2: %c, char 3: %c, char 4: %c, value node 4: %s\n", 
			node->splitchar,
			node->equal->splitchar,
			node->equal->high->splitchar,
			node->equal->high->equal->splitchar,
			(char *)node->equal->high->equal->equal->value); 

	node					= TSTree_insert(node, bdata(&test4), blength(&test4), Value4);
	mu_assert(node != NULL, "Failed to insert into tstree with another name.");
	debug("\nchar 1: %c, value node 1: %s, char 2: %c, char 3: %c, char 4: %c, value node 4: %s, char 5: %c, value node 5: %s\n", 
			node->splitchar,
			(char *)node->value, 
			node->equal->splitchar,
			node->equal->equal->splitchar,
			node->equal->equal->equal->splitchar,
			(char *)node->equal->equal->equal->value, 
			node->equal->equal->equal->equal->splitchar,
			(char *)node->equal->equal->equal->equal->value); 

	return NULL;
}


char *test_search_exact()
{
	// tstree returns the last one inserted
	void *res				= TSTree_search(node, bdata(&test1), blength(&test1));
	mu_assert(res == ValueA, "Got the wrong value back. should get ValueA");

	// tstree does not find if not exact
	res						= TSTree_search(node, "TESTNO", strlen("TESTNO"));
	mu_assert(res == NULL, "Should not find anything.");

	return NULL;
}


char *test_search_prefix()
{
	void *res				= TSTree_search_prefix(node, bdata(&test1), blength(&test1));
	debug("result: %p, expected: %p", res, ValueA);
	mu_assert(res == ValueA, "Got the wrong value back from ValueA prefix search size ValueA. should get ValueA");

	res						= TSTree_search_prefix(node, bdata(&test1), 1);
	debug("result: %p, expected: %p", res, Value4);
	mu_assert(res == Value4, "Got the wrong value back from ValueA prefix search size 1. should get Value4");

	res						= TSTree_search_prefix(node, "TE", strlen("TE"));
	debug("result: %p", res);
	mu_assert(res != NULL, "Should find for short prefix.");

	res						= TSTree_search_prefix(node, "TE--", strlen("TE--"));
	debug("result: %p", res);
	mu_assert(res != NULL, "Should find for partial prefix.");

	return NULL;
}
	

void TSTree_traverse_test_cb(void *value, void *data)
{
	assert(value != NULL && "Should not get a NULL value.");
	assert(data == ValueA && "Expecting ValueA as the data");
	traverse_count++;
}


char *test_traverse()
{
	traverse_count			= 0;
	TSTree_traverse(node, TSTree_traverse_test_cb, ValueA);
	debug("traverse count is: %d", traverse_count);
	mu_assert(traverse_count == 4, "Didn't find 4 keys.");

	return NULL;
}


char *test_destroy()
{
	TSTree_destroy(node);

	return NULL;
}


char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_insert);
	mu_run_test(test_search_exact);
	mu_run_test(test_search_prefix);
	mu_run_test(test_traverse);
	mu_run_test(test_destroy);

	return NULL;
}



RUN_TESTS(all_tests);
