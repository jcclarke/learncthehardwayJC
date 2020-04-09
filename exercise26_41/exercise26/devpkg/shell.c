/*------------------------------------------------------------------------- 
 * Include libraries                                                    *
-------------------------------------------------------------------------*/
#include <stdarg.h>

#include "shell.h"
#include "dbg.h"


/*------------------------------------------------------------------------- 
 * define constants                                                    *
-------------------------------------------------------------------------*/


/*------------------------------------------------------------------------- 
 * declare structures                                                    *
-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
 * define functions                                                      *
-------------------------------------------------------------------------*/
int Shell_exec(Shell template, ...)
{
	apr_pool_t *p	= NULL;									// create a pointer to a NULL memory pool			
	int rc			= -1;			
	apr_status_t rv	= APR_SUCCESS;							// an error checker
	va_list argp;											// complete argoments list
	const char *key	= NULL;
	const char *arg	= NULL;
	int i			= 0;
	//int total_arg	= 0;																		// number of arguments counter //

	rv	= apr_pool_create(&p, NULL);						// create a memory pool 
	check(rv == APR_SUCCESS, "Failed to create pool.");		// make sure we were successful

	va_start(argp, template);

	// compare the arguments in va_args to the function templates
	// starting from the first va_arg argument, for each argument until the NULL argument
	for (key = va_arg(argp, const char *);
		 key != NULL;
		 key = va_arg(argp, const char *)) {
			
	//	total_arg++;																			// count the total number of arguments //
		arg		= va_arg(argp, const char *);

		for (i = 0; template.args[i] != NULL; i++) {
			if (strcmp(template.args[i], key) == 0) {
				template.args[i] = arg;
				break;			// found it
			
			}
		}
	}
	
	// check(template.num_arg == total_arg, "Failed to provide correct number of arguments."); // make sure correct number of arguments provided //
	rc = Shell_run(p, &template);
	apr_pool_destroy(p);
	va_end(argp);
	return rc;

error:
	if (p) {
		apr_pool_destroy(p);
	}
	return rc;
}	


int Shell_run(apr_pool_t *p, Shell *cmd)
{
	apr_procattr_t * attr;
	apr_status_t rv;
	apr_proc_t newproc;

	rv = apr_procattr_create(&attr, p);
	check(rv == APR_SUCCESS, "Failed to create proc_attr.");

	rv = apr_procattr_io_set(attr, APR_NO_PIPE, APR_NO_PIPE,
		   	APR_NO_PIPE);
	check(rv == APR_SUCCESS, "Failed to set IO of command.");

	rv = apr_procattr_dir_set(attr, cmd->dir);
	check(rv == APR_SUCCESS, "Failed to set root to %s.", cmd->dir);

	rv = apr_procattr_cmdtype_set(attr, APR_PROGRAM_PATH);
	check(rv == APR_SUCCESS, "Failed to set cmd type.");

	rv = apr_proc_create(&newproc, cmd->exe, cmd->args, NULL, attr, p);
	check(rv == APR_SUCCESS, "Failed to run command.");

	rv = apr_proc_wait(&newproc, &cmd->exit_code, &cmd->exit_why, APR_WAIT);
	check(rv == APR_CHILD_DONE, "Failed to wait.");

	check(cmd->exit_code == 0, "%s exited badly.", cmd->exe);
	check(cmd->exit_why == APR_PROC_EXIT, "%s was killed or crashed.", cmd->exe);

	return 0;

error:
	return -1;
}

/*------------------------------------------------------------------------ 
 * define variables                                                      *
-------------------------------------------------------------------------*/

Shell CLEANUP_SH = {
	.exe	= "rm",
	.dir	= "/tmp",
	.num_arg = 6,
	.args	= {"rm", "-rf", "/tmp/pkg-build", "/tmp/pkg-scr.tar.gz",
	   	"/tmp/pkg-scr.tar.bz2", "/tmp/DEPENDS", NULL}
};

Shell GIT_SH = {
	.dir	= "/tmp",
	.exe	= "git",
	.num_arg = 4,
	.args	= {"git", "clone", "URL", "pkg-build", NULL}
};

Shell TAR_SH = {
	.dir	= "/tmp/pkg-build",
	.exe	= "tar",
	.num_arg = 5,
	.args	= {"tar", "-xzf", "FILE", "--strip-components", "1", NULL}
};

Shell CURL_SH = {
	.dir	= "/tmp",
	.exe	= "curl",
	.num_arg = 5,
	.args	= {"curl", "-L", "-o", "TARGET", "URL", NULL}
};

Shell CONFIGURE_SH = {
	.exe	= "./configure",
	.dir	= "/tmp/pkg-build",
	.num_arg = 2,
	.args	= {"configure", "OPTS", NULL}
};

Shell MAKE_SH = { 
	.exe	= "make",
	.dir	= "/tmp/pkg-build",
	.num_arg = 2,
	.args	= {"make", "OPTS", NULL}
};

Shell INSTALL_SH = {
	.exe	= "sudo",
	.dir	= "/tmp/pkg-build",
	.num_arg = 3,
	.args	= {"sudo", "make", "TARGET", NULL}
};

