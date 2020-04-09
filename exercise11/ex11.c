#include <stdio.h>

int main (int argc, char *argv[])		{
	

	//  variable definitions
	int		i				= 0;

	// go through each string in argv
	printf("\n");
	while (i < argc)				{
		printf("arg %d:\t\t%s\n",i, argv[i]);
		i++;
	}


	// Let's create our own array of strings
	char	*provinces[]	=			{
		"Alberta", "Manitoba",
		"Ontario","Quebec"
	};
	int		num_provinces	= 5;

	i = 0;			// watch for this (must always reinitialize before a while loop)
	printf("\n");
	while ( i < num_provinces)	{
		printf("province %d:\t%s\n", i, provinces[i]);	
		i++;
	}
	printf("\n");


	return 0;

}

