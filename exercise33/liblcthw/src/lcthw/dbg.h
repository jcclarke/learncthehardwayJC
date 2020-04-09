#ifndef		__dbg_h__
#define		__dbg_h__

#include	<stdio.h>
#include	<errno.h>
#include	<string.h>

#ifdef		NDEBUG								//-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-		// if you compile with NDEBUG defined then "no debug" messages print
#define		debug(M, ...)
#else											//-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-		// else print "debug" messages to stderr 
#define		debug(M, ...)			fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)	
#endif

#define		clean_errno()			(errno == 0 ? "None" : strerror(errno))			//	-	-	-	-	-	-	-	-	-	-	-	-	-		//	get a safe readable version of errno

#define		log_err(M, ...)			fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)		// show user the errors 

#define		log_warn(M, ...)		fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)		// show user the warnings

#define		log_info(M, ...)		fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)								// show user the logs

#define		check(A, M, ...)		if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error;}													// check if 'A' is true, else log error message 'M' with variable argument in log_err

#define		sentinel(M, ...)		{ log_err(M, ##__VA_ARGS__); errno=0; goto error;}															// placed in any function that shouldn't run to catch and display error as above

#define		check_mem(A)			check((A), "Out of memory.")																				// print error if memory not defined 

#define		check_debug(A,M,...)	if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error;}													// check alternative for less critical/common error to be printed if NDEBUG set

#endif
