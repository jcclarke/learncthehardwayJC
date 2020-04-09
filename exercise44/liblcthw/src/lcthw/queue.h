#ifndef lcthw_Queue_h
#define lcthw_Queue_h

#include <list.h>

typedef List Queue;

#define Queue_create		List_create
#define Queue_destroy		List_destroy
#define Queue_clear			List_clear
#define Queue_clear_destroy List_clear_destroy

#define Queue_send			List_push
#define Queue_recv			List_shift

#define Queue_count			List_count
#define Queue_peek			List_first

#define QUEUE_FOREACH(L, V) ListNode *V = NULL;\
	for(V = L->last; V != NULL; V = V->prev) // L = list and V = cur
#endif
