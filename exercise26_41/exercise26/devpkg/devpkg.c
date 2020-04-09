/*------------------------------------------------------------------------- 
 * Include libraries                                                    *
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <apr_general.h>
#include <apr_getopt.h>
#include <apr_strings.h>
#include <apr_lib.h>

//#include "/usr/local/apr/include/apr-1/apr_general.h"
//#include "/usr/local/apr/include/apr-1/apr_getopt.h"
//#include "/usr/local/apr/include/apr-1/apr_strings.h"
//#include "/usr/local/apr/include/apr-1/apr_lib.h"
#include "dbg.h"
#include "db.h"
#include "commands.h"



/*------------------------------------------------------------------------- 
 * define constants                                                    *
-------------------------------------------------------------------------*/


/*------------------------------------------------------------------------- 
 * declare structures                                                    *
-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
 * define functions                                                      *
-------------------------------------------------------------------------*/


/*------------------------------------------------------------------------- 
 * MAIN                                                    *
-------------------------------------------------------------------------*/

int main (int argc, const char * const * argv)      // char ** argv[] is string pointer. to the left makes the pointer and the char constant (unchangeable)
{
	apr_pool_t *p				= NULL;
	apr_pool_initialize();
	apr_pool_create(&p, NULL);

	apr_getopt_t * opt;
	apr_status_t rv;

	char ch						= '\0';
	const char * optarg			= NULL;
	const char * config_opts	= NULL;
	const char * install_opts	= NULL;
	const char * make_opts		= NULL;
	const char * url			= NULL;
	enum  CommandType request	= COMMAND_NONE;


	rv = apr_getopt_init(&opt, p, argc, argv);

	while (apr_getopt(opt, "I:Lc:m:i:d:SF:B:", &ch, &optarg) == APR_SUCCESS) {
		switch (ch) {
			case 'I':
				request			= COMMAND_INSTALL;
				url				= optarg;
				break;
		
			case 'L':
				request			= COMMAND_LIST;
				break;
		
			case 'c':
				config_opts		= optarg;
				break;
		
			case 'm':
				make_opts		= optarg;
				break;
		
			case 'i':
				install_opts	= optarg;
				break;
		
			case 'S':
				request			= COMMAND_INIT;
				break;
		
			case 'F':
				request			= COMMAND_FETCH;
				url				= optarg;
				break;
		
			case 'B':
				request			= COMMAND_BUILD;
				url				= optarg;
				break;
		}
	}

	switch (request) {
	
		case COMMAND_INSTALL:
			check(url, "You must at least give a URL.");
			Command_install(p, url, config_opts, make_opts, install_opts);
			break;

		case COMMAND_LIST:
			DB_list();
			break;

		case COMMAND_FETCH:
			check(url != NULL, "You must give a URL.");
			Command_fetch(p, url, 1);
			log_info("Downloaded to %s and in /tmp/", BUILD_DIR);
			break;

		case COMMAND_BUILD:
			check(url, "You must at least give a URL.");
			Command_build(p, url, config_opts, make_opts, install_opts);
			break;

		case COMMAND_INIT:
			rv = DB_init();
			check(rv == 0, "Failed to make the database.");
			break;

		default:
			sentinel("Invalid command given.\n"
					 "\nUSAGE: devpkg <command> [<options>]"
					 "\n"
					 "\n\tCommands:"
					 "\n\t-I <url> \tInstall package from <url>"
					 "\n\t-L\t\tList installed packages"
					 "\n\t-S\t\tInitialize package database"
					 "\n\t-F <url>\tFetch package from <url>"
					 "\n\t-B <url>\tBuild package from <url>"
					 "\n\n\tinstall options:"
					 "\n\t-c <config-opts>"
					 "\n\t-m <make-opts>"
					 "\n\t-i <install-opts>"
					 "\n"
					);
	}
	apr_pool_terminate();
	return 0;

error:
	apr_pool_terminate();
	return 1;
}
