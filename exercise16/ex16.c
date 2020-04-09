#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


// declare a person struct
struct Person {

	char	*name;
	int		age;
	int		height;
	int		weight;

};


// create a new person info
struct Person *Person_create(char *name, int age, int height, int weight)
{
	
	// allocate memory for the *who struct. malloc calculates the amount and then assigns it
	struct Person *who	= malloc(sizeof(struct Person));

	// a sanity check to make sure we get a valid memory block 
	assert(who != NULL);

	// initialize the new person's info
	who	-> name				= strdup(name);				// strdup -- STRing 'DUPlicate
	who	-> age				= age;
	who	-> height			= height;
	who	-> weight			= weight;

	return who;

}

// remove person info and free memory  (ALWAYS HAVE THIS else memory leak)
void Person_destroy(struct Person *who)
{

	// see line 25
	assert(who != NULL);
	
	// free string and struct memory
	free(who->name);
	free(who);

}

// print person info
void Person_print(struct Person *who)
{

	printf("\nName:\t%s\n", who->name);
	printf("\tAge:\t%d\n", who->age);
	printf("\theight:\t%d\n", who->height);
	printf("\tweight:\t%d\n", who->weight);

}

// main
int	main (int argc, char *argv[])			
{

	// make two people structures
	struct Person *joe		= Person_create("Joe Alex", 32, 64, 140);
	struct Person *frank	= Person_create("Frank Blank", 20, 72, 180);

	// print them out and where they are located in memory
	printf("\nJoe is in memory location %p:\n", joe);
	Person_print(joe);
	
	printf("\nFrank is in memory location %p:\n", frank);
	Person_print(frank);

	// make everyone 20 years older and print again
	joe		-> age			+= 20;
	joe		-> height		-= 2;
	joe		-> weight		+= 40;
	Person_print(joe);

	frank	-> age			+= 20;
	frank	-> weight		+= 20;
	Person_print(frank);

	printf("\n");

	// destroy them both so we clean up memory
	Person_destroy(joe);
	Person_destroy(frank);


	// create a new person struct without pointers and point to it
	struct Person mike		= {"Mike Drop", 26, 69, 175}; 
	struct Person *mike_ptr	= &mike ;

	Person_print(mike_ptr);

	// make mike 26 years older
	mike . age				+= 26;
	mike.weight				+= 14;
	mike.height				-= 1;

	Person_print(mike_ptr);

	printf("\n");

	return 0;

}
