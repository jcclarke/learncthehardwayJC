#include <stdio.h>
#include <ctype.h>

// foward function declarations
int		can_print_it(char ch);
void	print_letters(char arg[]);

// print the program inputs
void	print_arguments(int argc, char *argv[])	
{

	int	i	= 0;

	printf("\n");
	for (i = 0; i < argc; i++)	{
		print_letters(argv[i]); 
	}	

}

// print the characters and their ascii code
void print_letters(char arg[])
{

	int i	= 0;

	for(i = 0; arg[i] != '\0'; i++) {

		char ch = arg[i];
		if (can_print_it(ch)) {
			printf("'%c' == %d", ch, ch);	
		printf("\n");
		}
	}

	printf("\n");

}

// print only characters or a space
int can_print_it(char ch)
{

	// is the character a letter or space
	return isalpha(ch) || isblank(ch);

}

// main
int		main (int argc, char *argv[])			
{

	print_arguments(argc, argv);
	
	return 0;

}

