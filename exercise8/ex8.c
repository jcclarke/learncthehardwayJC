#include <stdio.h>

int main (int argc, char *argv[])	{
	
	// variable instatiations
	int		areas[]			= {10, 12, 13, 14, 20};
	char	name[]			= "Jean-Claude";
	char	full_name[]		= {
		'J','e','a','n','-','C','l','a','u','d','e',
		' ','L','.',' ',
		'C','l','a','r','k','e','\0'
	};

	// WARNING: On some systems you may have to change the
	// %ld in this code to a %u since it will use unsigned ints
	printf("\nThe size of an int: \t\t\t%ld\n", sizeof(int));
	printf("The size of areas (int[]): \t\t%ld\n", sizeof(areas));
	printf("The number of ints in areas: \t\t%ld\n", sizeof(areas) / sizeof(int));
	printf("The first area is \t\t\t%d\nThe second area is \t\t\t%d\n\n", areas[0], areas[1]);
	
	printf("The size of a char: \t\t\t%ld\n", sizeof(char));
	printf("The size of name (char[]): \t\t%ld\n", sizeof(name));
	printf("The number of chars in name: \t\t%ld\n\n", sizeof(name) / sizeof(char));

	printf("The size of full_name (char[]): \t%ld\n", sizeof(full_name));
	printf("The number of chars in full_name: \t%ld\n\n", sizeof(full_name) / sizeof(char));

	printf("name \t\t\t=\"%s\"\nfull_name \t\t=\"%s\"\n\n", name, full_name);

	//printf("The 50th name char is \t\t\t%d\nThe 50th full_name char is \t\t\t%d\n\n", name[50], full_name[50]);

	return 0;

}

