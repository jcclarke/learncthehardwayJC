#ifndef _ex19_h
#define _ex19_h
#include "object.h"

/* weapon class definition of type object */
struct Weapon {
	Object proto;
	int damage;
};

/* weapon declaration */
typedef struct Weapon Weapon;

// weapon constructor
int Weapon_init(void *self);

/* monster class definition of type object */
struct Monster {
	Object proto;
	int hit_points;
};

/* monster declaration */
typedef struct Monster Monster;

/* monster function definitions */
int Monster_attack(void *self, int damage);
// monster constructor
int Monster_init(void *self);

/* room class definition of type object */
struct Room {
	Object proto;
	Monster *bad_guy;
	Weapon *weaponry;
	struct Room *north;
	struct Room *south;
	struct Room *east;
	struct Room *west;
};

/* room declaration */
typedef struct Room Room;

/* room function definitions */
void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);
// room constructor
int Room_init(void *self);

/* map class definition of type object */
struct Map {
	Object proto;
	Room *start;
	Room *location;
};

/* map declaration */
typedef struct Map Map;

/* map function definitions */
void *Map_move(void *self, Direction direction);
int Map_attack(void *self, int damage);
// map constructor
int Map_init(void *self);

#endif
