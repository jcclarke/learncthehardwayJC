#include <stdio.h>
#include <ctype.h>


// main
int		main (int argc, char *argv[])			
{

	//create two arrays that we care about
	int		ages[]		= {23, 43, 12, 89, 2};
	char*	names[]		= {"Alan", "Frank", "Mary", "John", "Lisa"};

	// safely get the size of ages
	int		count		= sizeof(ages) / sizeof(int);   
	int		i			= 0;
	//note: if we did sizeof(cur_age), we would get the size of the pointer, not the size of the array block
	
	printf("\n");

	// first way using indexing
	for (i = 0; i < count; i++)		{
		printf("%s has %d years alive.\n", names[i], ages[i]);
	}
	
	printf("\n");

	// setup the pointers to the start of the arrays
	int		*cur_age	= ages;
	char	**cur_name	= names;

	// Second way using pointers
	for (i = 0; i < count; i++)		{
		printf("%s has %d years old.\n", *(cur_name + i), *(cur_age + i));
	}

	printf("\n");

	// Third way, pointers are just arrays
	for (i = 0; i < count; i++)		{
		printf("%s has %d years old again.\n", cur_name[i], cur_age[i]);
	}

	printf("\n");

	// Fourth way with pointers in a stupid complex way
	for (cur_name = names, cur_age = ages; (cur_age - ages) < count; cur_name++, cur_age++)
	{
		printf("%s lived %d years so far.\n", *cur_name, *cur_age);
	}

	printf("\n");

	return 0;

}

