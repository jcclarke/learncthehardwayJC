#include <stdio.h>

int main (int argc, char *argv[])		{

	// Input error checking
	if (argc != 2){
		printf("\nERROR: You need one and only one argument\n\n");
		// This is how you abort a program
		return 1;
	}	

	//  variable definitions
	int		i			= 0;

	printf("\n");
	for (i = 0; argv[1][i] != '\0'; i++){
		char letter		= argv[1][i];

		switch (letter)					{
			case 'a':								// This is an example of a fall through
			case 'A':
				printf("%d: 'A'\n", i);
				break;

			case 'e':
			case 'E':
				printf("%d: 'E'\n", i);
				break;

			case 'i':
			case 'I':
				printf("%d: 'I'\n", i);
				break;

			case 'o':
			case 'O':
				printf("%d: 'O'\n", i);
				break;

			case 'u':
			case 'U':
				printf("%d: 'U'\n", i);
				break;

			case 'y':
			case 'Y':
				if (i > 2)				{
					// It's only sometimes Y
					printf("%d: 'Y'\n", i);
				break;
				}

			default:
				printf("%d: %c is not a vowel\n", i, letter);

		}	
	}
	
	printf("\n");

	return 0;

}

