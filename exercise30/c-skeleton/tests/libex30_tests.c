#include "minunit.h"
#include <dlfcn.h>


/*------------------------------------------------------------------------- 
 * declare structures                                                    *
-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------
 * define functions                                                      *
-------------------------------------------------------------------------*/

typedef int (*lib_function)(const char *data);
char *lib_file	= "build/libex30.so";
void *lib		= NULL;


int check_function(const char *func_to_run, const char *data, int expected)
{
	// create a funtion pointer to the function found in the library
	lib_function func = dlsym(lib, func_to_run);
	check(func != NULL, "Did not find %s function in the library %s: %s", func_to_run, lib_file, dlerror());

	// now run the function if it was found
	int rc = func(data);
	check(rc == expected, "Function %s return %d for data: %s", func_to_run, rc, data);

	return 1;
error:
	return 0;

}

char *test_dlopen()
{
	// open the library archive
	lib = dlopen(lib_file, RTLD_NOW);
	mu_assert(lib != NULL, "Failed to open the library to test");

	return NULL;
}

char *test_functions()
{
	mu_assert(check_function("print_a_message", "Hello", 0), "print_a_message failed.");
	mu_assert(check_function("uppercase", "Hello", 0), "uppercase failed.");
	mu_assert(check_function("lowercase", "Hello", 0), "lowercase failed.");

	return NULL;
}

char *test_failures()
{
	mu_assert(check_function("fail_on_purpose", "Hello", 1), "fail_on_purpose should fail.");

	return NULL;
}

char *test_dlclose()
{
	// close the library archive
	int rc = dlclose(lib);
	mu_assert(rc == 0, "Failed to close lib.");

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_dlopen);
	mu_run_test(test_functions);
	mu_run_test(test_failures);
	mu_run_test(test_dlclose);

	return NULL;
}

RUN_TESTS(all_tests);
