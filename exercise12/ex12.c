#include <stdio.h>

int main (int argc, char *argv[])		{
	

	//  variable definitions
	int		i				= 0;

	printf("\n");

	// the If statement
	
	// Not enough arguments?
	if (argc == 1)						{
			printf("You have only ONE argument!  YOU SUCK!!\n");	
	}

	// between 2 and 4 arguments?
	else if (argc > 1 && argc < 5)		{
		// go through each string in argv
		printf("These are your arguments:\n\n");	
		for(i = 0; i < argc; i++)		{
			printf("%s ", argv[i]);
		}
		printf("\n");
	}
	
	// more than 4 arguments?
	else								{
			printf("You have only too many arguments!  YOU SUCK!!\n");	
		
	}

	printf("\n");

	return 0;

}

