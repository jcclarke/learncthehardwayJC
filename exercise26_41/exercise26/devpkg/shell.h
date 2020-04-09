#ifndef _shell_h
#define _shell_h

/*------------------------------------------------------------------------ 
 * define constants                                                      *
-------------------------------------------------------------------------*/
#define MAX_COMMAND_ARGS 100

/*------------------------------------------------------------------------
 * Include libraries                                                     *
-------------------------------------------------------------------------*/
#include <apr_thread_proc.h>
//#include "/usr/local/apr/include/apr-1/apr_thread_proc.h"

/*------------------------------------------------------------------------ 
 * declare structures                                                    *
-------------------------------------------------------------------------*/
typedef struct Shell {
	const char		*	dir;
	const char		*	exe;

	apr_procattr_t	*	attr;
	apr_proc_t			proc;
	apr_exit_why_e		exit_why;
	int					exit_code;
	int					num_arg;							// number of arguments that need to be replaced for the shell cmd template

	const char		*	args[MAX_COMMAND_ARGS];
} Shell;

/*-------------------------------------------------------------------------
 * declare functions                                                      *
--------------------------------------------------------------------------*/
int Shell_run(apr_pool_t *p, Shell *cmd);
int Shell_exec(Shell cmd, ...);								//not sure if this missing * infront of cmd is a mistake or not

/*------------------------------------------------------------------------ 
 * declare variables                                                      *
-------------------------------------------------------------------------*/
extern Shell CLEANUP_SH;
extern Shell GIT_SH;
extern Shell TAR_SH;
extern Shell CURL_SH;
extern Shell CONFIGURE_SH;
extern Shell MAKE_SH;
extern Shell INSTALL_SH;

#endif
