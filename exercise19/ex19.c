#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex19.h"


// define constants


/*------------------------------------------------------------------------- 
 * declare structures                                                    *
-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------
 * define functions                                                      *
-------------------------------------------------------------------------*/
/* weapon attack function */
/* Initialize the weapon / weapon constructor*/ 
int Weapon_init(void *self)
{

	Weapon *weapon	= self;
	weapon->damage	= 1;
	return 1;

}


/* Monster object prototype */
Object WeaponProto = {
	.init	= Weapon_init,
};

int Monster_attack(void *self, int damage)
{
	Monster *monster = self;

	printf ("You attack %s!\n", monster->_(description));

	monster->hit_points -= damage;

	if (monster->hit_points > 0) {
		printf("You do %d damage.\nIt is still alive. HP = %d\n", damage, monster->hit_points);
		return 0;
	} else {
		printf("It is dead!\n");
		return 1;
	}
}
		

/* Initialize the monster / monster constructor*/ 
int Monster_init(void *self)
{

	Monster *monster	= self;
	monster->hit_points	= 10;
	return 1;

}


/* Monster object prototype */
Object MonsterProto = {
	.init	= Monster_init,
	.attack	= Monster_attack
};

/* room move function */
void *Room_move(void *self, Direction direction)
{
	Room *room	= self;
	Room *next	= NULL;

	if(direction == NORTH && room->north){
		printf("You go north, into:\n");
		next	= room->north;	
	} else if (direction == SOUTH && room->south){
		printf("You go south, into:\n");
		next	= room->south;	
	} else if (direction == EAST && room->east){
		printf("You go east, into:\n");
		next	= room->east;	
	} else if (direction == WEST && room->west){
		printf("You go west, into:\n");
		next	= room->west;	
	} else  {
		printf("You can't go that direction.\n");
		next	= NULL;	
	}
	
	if (next) {
		next->_(describe)(next);
	}

	return next;
}

/* room attack function */
int Room_attack(void *self, int damage)
{
	Room	*room		= self;
	Monster *monster	= room->bad_guy;

	if(monster) {
		monster->_(attack)(monster, damage);
		return 1;
	} else {
		printf("You flail in the air at nothing. Idiot!\n");
		return 0;
	}

}


/* i don't know yet */
Object RoomProto = {
	.move	= Room_move,
	.attack	= Room_attack
};



void *Map_move(void *self, Direction direction)
{
	Map *map		= self;
	Room *location	= map->location;
	Room *next		= NULL;

	next = location->_(move)(location, direction);

	if (next) {
		map->location = next;
	}

	return next;
}

int Map_attack(void *self, int damage)
{
	Map* map		= self;
	Room *location	= map->location;
	
	return location->_(attack)(location, damage);
}

int Map_init(void *self)
{
	Map* map		= self;

	// Make some rooms for a small map
	Room *hall			= NEW(Room, "The Great Hall");
	Room *throne		= NEW(Room, "The Throne Room");
	Room *arena			= NEW(Room, "The arena, with the Minitaur");
	Room *kitchen		= NEW(Room, "Kitchen. You have a knife now");

	// put bad guy in the arena
	arena->bad_guy		= NEW(Monster, "The evil minotaur");

	// put a weapon in the kitchen
	kitchen->weaponry	= NEW(Weapon, "A knife");

	// setup the map rooms
	hall->north			= throne;

	throne->west		= arena;
	throne->east		= kitchen;
	throne->south		= hall;

	arena->east			= throne;
	kitchen->west		= throne;

	// start the map and the character off in the hall
	map->start			= hall;
	map->location		= hall;

	return 1;
}

/* Map object constructor */
Object MapProto = {
	.init	= Map_init,
	.move	= Map_move,
	.attack	= Map_attack
};


int process_input(Map *game, int *game_weapon)
{
	printf("\n> ");
	
	char ch = getchar();
	getchar();  //eat ENTER
	
	// find weapon, increase damage
	int damage = (rand() % 4) + game_weapon[0];

	switch(ch) {
		case -1:
			printf("Giving up? You Suck!\n");
			return 0;
			break;

		case 'n':
			game->_(move)(game, NORTH);
			break;

		case 's':
			game->_(move)(game, SOUTH);
			break;

		case 'e':
			game->_(move)(game, EAST);
			break;

		case 'w':
			game->_(move)(game, WEST);
			break;
		
		case 'a':
			game->_(attack)(game, damage);
			break;
	
		case 'l':
			printf("You can go\n");
			if(game->location->north) printf("NORTH\n");
			if(game->location->south) printf("SOUTH\n");
			if(game->location->east) printf("EAST\n");
			if(game->location->west) printf("WEST\n");
			break;
		// game play instructions
		case 'h':
			printf("Here are the commands used to play this game\n");
			printf("'n'\t\tmove you character NORTH\n");
			printf("'s'\t\tmove you character SOUTH\n");
			printf("'e'\t\tmove you character EAST\n");
			printf("'w'\t\tmove you character WEST\n");
			printf("'a'\t\tattack\n");
			printf("'l'\t\twhere you can move\n");
			printf("'h'\t\tthis help menu\n");
			printf("'ctrl+d'\tquit game\n");
			break;
		
		default:
			printf("What?: %d\n", ch);
	}
	// the first time you enter the arena
	// increase damage, you got a knife	 
	if(game->location->weaponry && game_weapon[0] == 0){
		game_weapon[0]	= 1;
	} 

	return 1;
}



/*-----------------------------------------------------------------------
 * main                                                                *
-----------------------------------------------------------------------*/

int	main (int argc, char *argv[])			
{
	// simple way to setup the randomness
	srand(time(NULL));

	// make our map work with
	Map *game	= NEW(Map, "The Hall of the Minitaur.");

	printf("you enter the ");
	game->location->_(describe)(game->location);

	printf("Type 'h' then 'enter' for game instructions.\n");
	
	// if you find a weapon, increase damage
	// weapons[0] -- knife				-- +1 damage
	// weapons[1] -- sword and shield	-- +2 damage
	// weapons[2] -- bow and arrow		-- +1 damage
	int weapons[]	= {0,0,0};
	int *weapon		= weapons;

	while(process_input(game, weapon)) {
	}

	return 0;

}
