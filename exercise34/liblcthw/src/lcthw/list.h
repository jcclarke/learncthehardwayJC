#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

struct ListNode;

typedef struct ListNode {
	struct ListNode *next;
	struct ListNode *prev;
	void *value;
} ListNode;

typedef struct List {
	int count;
	ListNode *first;
	ListNode *last;
} List;

List *List_create();
void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destroy(List *list);

#define List_count(A) ((A)->count) 
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL) 
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)  

void List_push_node(List *list, ListNode *node);
void List_push(List *list, void *value);
ListNode *List_pop_node(List *list);
void *List_pop(List *list);

void List_unshift_node(List *list, ListNode *node);
void List_unshift(List *list, void *value);
ListNode *List_shift_node(List *list);
void *List_shift(List *list);

void List_remove_node(List *list, ListNode *node);
void *List_remove(List *list, ListNode *node);

// Extra Credit begin
void List_print(List *list);
void List_backwards_print(List *list);

List *List_copy(List *list);

void List_join(List *list, List *list1);
void List_split(List *list, List *list1, ListNode *node);
// end of Extra Credit 

#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
	ListNode *V = NULL;\
	for(V = _node = L->S; _node != NULL; V = _node = _node->M)
	//for (cur = node = list->first; node != NULL; cur = node = node->next)

#endif