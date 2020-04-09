#include <stdio.h>

int main (int argc, char *argv[])		{
	

	//  variable definitions
	int		i				= 0;

	// go through each string in argv
	// why am I skipping argv[0]?
	printf("\n");
	for (i=1; i < argc; i++)			{
		printf("arg %d:\t\t%s\n",i, argv[i]);
	}


	// Let's crete our own array of strings
	char	*provinces[]	=			{
		"Alberta", "Manitoba",
		"Ontario","Quebec"
	};
	int		num_provinces	= 5;

	printf("\n");
	for (i=0; i < num_provinces; i++)	{
		printf("province %d:\t%s\n", i, provinces[i]);	
	}
	printf("\n");


	return 0;

}

