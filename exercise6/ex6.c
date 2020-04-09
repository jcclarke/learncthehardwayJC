#include <stdio.h>

int main (int argc, char *argv[])	{

	// initialise variables
	int		distance		= 100			;
	float	power			= 2.345f		;
	double	super_power		= 56789.4532	;
	char	intial			= 'L'			;
	char	first_name[]	= "Jean-Claude"	;
	char	last_name[]		= "Clarke"		;

	// Print statements
	printf("\nYou are %d miles away.\n", distance );
	printf("You have %f levels of power.\n", power);
	printf("You have %f awesome super powers.\n", super_power);
	printf("I have an initial %c.\n", intial);
	printf("I have a first name %s.\n", first_name);
	printf("I have a last name %s.\n", last_name);
	printf("My whole name is %s %c %s.\n\n" ,first_name, intial, last_name);
	
	return 0;

}

