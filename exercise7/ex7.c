#include <stdio.h>

int main (int argc, char *argv[])	{
	
	int		bugs				= 100	;
	double	bug_rate			= 1.2	;

	// print the bugs and bug_rate values
	printf("\nYou have %d bugs at the imaginary rate of %f.\n", bugs, bug_rate);

	long universe_of_defects	= 1L * 1024L * 1024L * 1024L;
	//print bugs in universe
	printf("The entire universe has %ld bugs.\n", universe_of_defects);
	
	double expected_bugs		= bugs * bug_rate;
	//print expected bugs
	printf("You are expected to have %f bugs.\n",  expected_bugs);

	double part_of_universe		= expected_bugs / universe_of_defects;
	//print ratio of bugs to bugs in universe
	printf("That is only %e portion of the universe.\n", part_of_universe);

	// this makes no sence, just a demo of something weird
	char nul_byte				= '\0';
	int care_percentage			= bugs * nul_byte ;
	printf("Which means you should care %d%%.\n test nul_byte %s.\n\n", care_percentage, nul_byte);					// %% means print out a percentage sign not a variable


	return 0;

}

