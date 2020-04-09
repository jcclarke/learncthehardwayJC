#include <stdio.h>

int main (int argc, char *argv[])	{
	
	//  variable definitions
	int		numbers[12]		= {'a'};
    char	name[12]		= {'a', 0, 97};

	// print out the current raw information 
	printf("\nnumbers:      %d %d %d %d %d %d %d %d %d %d %d %d\n", 
			numbers[0], numbers[1], numbers[2], numbers[3],
			numbers[4], numbers[5], numbers[6], numbers[7],
			numbers[8], numbers[9], numbers[10], numbers[11]);
	printf("name each:    %c %c %c %c %c %c %c %c %c %c %c %c\n", 
			name[0], name[1], name[2], name[3],
			name[4], name[5], name[6], name[7],
			name[8], name[9], name[10], name[11]);
	// print the name like a string
	printf("name:         %s\n", name);
	
	// update/setup the numbers 
	numbers[0]				= 1;
	numbers[1]				= 2;
	numbers[2]				= 3;
	numbers[3]				= 4;
	numbers[4]				= 5;
	numbers[5]				= 6;
	numbers[6]				= 7;
	numbers[7]				= 8;
	numbers[8]				= 9;
	numbers[9]				= 10;
	numbers[10]				= 11;
	numbers[11]				= 12;
	
	// update/setup the name
	name[0]					= 'J';	
	name[1]					= 'e';	
	name[2]					= 'a';	
	name[3]					= 'n';	
	name[4]					= '-';	
	name[5]					= 'C';	
	name[6]					= 'l';	
	name[7]					= 'a';	
	name[8]					= 'r';	
	name[9]					= 'k';	
	name[10]				= 'e';	
	name[11]				= '\0';	
	
	// print out the updated/ initialized
	printf("\nnumbers:      %d %d %d %d %d %d %d %d %d %d %d %d\n", 
			numbers[0], numbers[1], numbers[2], numbers[3],
			numbers[4], numbers[5], numbers[6], numbers[7],
			numbers[8], numbers[9], numbers[10], numbers[11]);
	printf("name each:    %c %c %c %c %c %c %c %c %c %c %c %c\n", 
			name[0], name[1], name[2], name[3],
			name[4], name[5], name[6], name[7],
			name[8], name[9], name[10], name[11]);
	// print the name like a string
	printf("name:         %s\n", name);

	// another way to use name
	char *another			="Jean-Claude";
	// print the name like a string
	printf("\nanother:      %s\n\n", another);
	printf("another each: %c %c %c %c %c %c %c %c %c %c %c %c\n\n", 
			another[0], another[1], another[2], another[3],
			another[4], another[5], another[6], another[7],
			another[8], another[9], another[10], another[11]);

	return 0;

}

