#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

int THE_SIZE		= 1000;

// ONLY accessible directly in this file
static int THE_AGE	= 37;

// function to get access to the THE_AGE from another file
int get_age ()
{

	return THE_AGE;

}

// function to change THE_AGE value from another file
void set_age(int age)
{

	THE_AGE = age;

}

// 'ratio' can only be accessed in this function
double update_ratio(double new_ratio){

	static double ratio = 1.0;

	double old_ratio	= ratio;
	ratio				= new_ratio;
	
	return old_ratio;

}

void print_size()
{

	log_info("I think size is: %d", THE_SIZE);

}
