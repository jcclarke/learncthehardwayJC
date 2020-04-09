#include "minunit.h"
#include <bstrlib.h>


static char *string1				= "This is the complete string,";
static char *string2				= " and this is added.";
static char *string3				= "complete";
static char *string4				= "first";
//static char *string5				= "and the second";
static int len1						= 28;
static int len2						= 19;
static int len3						= 8;
static int len4						= 5;

static bstring bstr1				= NULL;
static bstring bstr2				= NULL;
static bstring bstr3				= NULL;
static bstring bstr4				= NULL;
static struct bstrList *bspllist	= NULL;
//extra credit



char *test_create()
{
	bstr1						= bfromcstr(string1);
	mu_assert(bstr1 != NULL, "Failed to create bstr1 from string1.");
	mu_assert(blength(bstr1) == len1, "Wrong bstr1 length value.");
	
	bstr2						= blk2bstr(string2, len2);
	mu_assert(bstr2 != NULL, "Failed to create bstr2 from string2.");
	mu_assert(blength(bstr2) == len2, "Wrong bstr2 length value.");
	
	bstr3						= bfromcstr(string1);
	int rc						= bassigncstr(bstr3, string3);
	mu_assert(rc != BSTR_ERR, "Failed to set bstr3 from string3.");
	mu_assert(blength(bstr3) == len3, "Wrong bstr3 length value.");
	
	bstr4						= bfromcstr(string1);
	rc							= bassignblk(bstr4, string4, len4);
	mu_assert(rc != BSTR_ERR, "Failed to set bstr4 from string4.");
	mu_assert(blength(bstr4) == len4, "Wrong bstr4 length value.");

	bspllist					= bstrListCreate();		
	mu_assert(bspllist != NULL, "Failed to create bspllist.");

	return NULL;
}



char *test_destroy()
{
	bdestroy(bstr1);
	bdestroy(bstr2);
	bdestroy(bstr3);
	bdestroy(bstr4);
	bstrListDestroy(bspllist);

	return NULL;
}



char *test_contents()
{
	bstring tst1				= NULL;
	tst1						= bstrcpy(bstr3);

	mu_assert(bstr1 != NULL, "Failed to make tst1 a duplicate of bstr3.");
	mu_assert(bstricmp(bstr3, tst1) == 0, "Error. bstr3 and tst1 != after copy.");
	mu_assert(biseq(bstr3, tst1) == 1, "Error. tst1 and bstr3 not equal.");
	mu_assert(binstr(bstr1, 5, bstr3) == 12, "Failed to find bstr3 in bstr1.");
	mu_assert(bassign(tst1, bstr1) != BSTR_ERR, "Failed to copy bstr1 to tst1.");
	mu_assert(bfindreplace(tst1, bstr3, bstr4, 0) != BSTR_ERR, "Failed to find and replace.");
	mu_assert(bconcat(tst1, bstr2) == BSTR_OK, "Failed to concatenate bstr2 to the end of tst1.");
	mu_assert(blength(tst1) == 44, "Failed to take the bstring length.");
	
	bspllist					= bsplit(tst1, ',');
	int i						= 0;


	// How to print a bstrList
	for (i  = 0; i < bspllist->qty; i++){
		// how to print a bstring as a string
		printf("%d: %s\n", i, bdatae(bspllist->entry[i], "NULL"));
	}
	printf("0: %s\n", bdatae(bstr2, "NULL"));
	
	mu_assert(bstrcmp(bspllist->entry[1], bstr2) == 0, "Failed to split bsplit tst1.");

	bdestroy(tst1);
	return NULL;
}


char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_contents);
/*	mu_run_test(test_set);
	mu_run_test(test_get);
	mu_run_test(test_remove);
	mu_run_test(test_expand_contract);
	mu_run_test(test_push_pop); */
	mu_run_test(test_destroy);

	return NULL;
}



RUN_TESTS(all_tests);
