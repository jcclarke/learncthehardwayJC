#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>


/*------------------------------------------------------------------------- 
 * declare structures                                                    *
-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------
 * define functions                                                      *
-------------------------------------------------------------------------*/

typedef int (*lib_function)(const char *data);


int main(int argc, char *argv[])
{

	int rc = 0;
	check(argc == 4, "USAGE: ex29 libex29.so function data");

	char *lib_file = argv[1];
	char *func_to_run = argv[2];
	char *data = argv[3];
	
	// open the library archive
	void *lib = dlopen(lib_file, RTLD_NOW);
	check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());
	
	// create a funtion pointer to the function found in the library
	lib_function func = dlsym(lib, func_to_run);
	check(func != NULL, "Did not find %s function in the library %s: %s", func_to_run, lib_file, dlerror());

	// now run the function if it was found
	rc = func(data);
	check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);

	// close the library archive
	rc = dlclose(lib);
	check(rc == 0, "Failed to close %s", lib_file);

	return 0;

error:
	return 1;

}

