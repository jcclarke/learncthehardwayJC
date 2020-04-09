#ifndef	_object_h
#define _object_h

typedef enum {
	NORTH,SOUTH, EAST, WEST
} Direction;

typedef struct {
	char	*description;
	int		(*init)(void *self);
	void	(*describe)(void *self);
	void	(*destroy)(void *self);
	void	*(*move)(void *self, Direction direction);
	int		(*attack)(void *self, int damage);
} Object;

int		Object_init(void *self);
void	Object_destroy(void *self);
void	Object_describe(void *self);
void	*Object_move(void *self, Direction direction);
int		Object_attack(void *self, int damage);
void	*Object_new(size_t size, Object proto, char *description);


/* define macros */

// when a NEW function with this format is called, 
// use it to create a function with Object_new format,
// and replace NEW with Object_new. 
#define NEW(T,N) Object_new(sizeof(T), T##Proto, N)

// same as above, this time 
// use _(N) to get proto.N
#define _(N) proto.N

#endif
