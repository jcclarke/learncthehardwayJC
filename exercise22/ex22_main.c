#include "ex22.h"
#include "dbg.h"

// define constants

const char	*MY_NAME	= "Jean-Claude Clarke";

/*------------------------------------------------------------------------- 
 * declare structures                                                    *
-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------
 * define functions                                                      *
-------------------------------------------------------------------------*/

void scope_demo(int count)
{

	log_info("count is: %d", count);
	
	// will it print the count in the if statement or the input count?
	if(count > 10){
		int count = 100;		// BAD! BUGS!

		log_info("count in this scope is %d", count);
	}

	log_info("count is at exit: %d", count);

	count = 3000;

	log_info("count after assign: %d", count);

}


/*-----------------------------------------------------------------------
 * main                                                                *
-----------------------------------------------------------------------*/

int	main (int argc, char *argv[])			
{

	// test out THE_AGES accessors
	log_info("My name: %s, age: %d", MY_NAME, get_age());

	set_age(75);

	log_info("My age is now: %d", get_age());

	// test out THE_SIZE extern
	log_info("THE_SIZE is: %d", THE_SIZE);
	print_size();

	// test the ratio function static
	log_info("Ratio at first: %f", update_ratio(2.0));
	log_info("Ratio again: %f", update_ratio(10.0));
	log_info("Ratio once more: %f", update_ratio(300.0));

	// test the scope demo
	int count = 4;
	scope_demo(count);
	scope_demo(count * 20);

	log_info("count after calling scope_demo: %d", count);
		
	return 0;

}
