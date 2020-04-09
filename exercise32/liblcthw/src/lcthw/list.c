#include <list.h> 
#include <assert.h>
#include <dbg.h>


// create new list
List *List_create()
{
	return calloc(1, sizeof(List));
}


// destroy current list
void List_destroy(List *list)
{
	LIST_FOREACH(list, first, next, cur) {
		if (cur->prev) {
			free(cur->prev);
		}
	}

	free(list->last);
	free(list);
}


// clear all list values
void List_clear(List *list)
{
	LIST_FOREACH(list, first, next, cur) {
		free(cur->value);
	}

}


// clear all list values and destroy current list
void List_clear_destroy(List *list)
{
	// extra credit begins
	LIST_FOREACH(list, first, next, cur) {
		free(cur->value);
		if (cur->prev) {
			free(cur->prev);
		}
	}

	//free(list->last->value);  You can't free() NULL values
	free(list->last);
	free(list);
	// extra credit ends
	
	// changed the code for one loop
	//List_clear(list);
	//List_destroy(list);
}


// add(push) new value to end of list. 
void List_push(List *list, void *value)
{
	ListNode *node			= calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value				= value;

	if(list->last == NULL){
		// if nothing in the list, put as first element
		list->first			= node;
		list->last			= node;
	}else{
		// otherwise, add to end of list
		list->last->next	= node;
		node->prev			= list->last;
		list->last			= node;
	}

	list->count++;

error:
	return;
}


// remove(pop) value from the end of the list
void *List_pop(List *list)
{
	ListNode *node			= list->last;
	return node != NULL ? List_remove(list, node) : NULL;
}


// add(unshift) new value to the beginning of list
void List_unshift(List *list, void *value)
{
	ListNode *node			= calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value				= value;

	if(list->last == NULL){
		// if nothing in the list, put as first element
		list->first			= node;
		list->last			= node;
	}else{
		// otherwise, add to beginning of list
		node->next			= list->first;
		list->first->prev	= node;
		list->first			= node;
	}

	list->count++;

error:
	return;
}


// remove(shift) value from the beginning of the list
void *List_shift(List *list)
{
	ListNode *node			= list->first;
	return node != NULL ? List_remove(list, node) : NULL;
}


// remove node from list
void *List_remove(List *list, ListNode *node)
{
	void *result			= NULL;

	check(list->first && list->last, "List is Empty.");
	check(node, "Node can't be NULL");
	
	if(node == list->first && node == list->last){
		// remove the only element in the list
		list->first			= NULL;
		list->last			= NULL;
	}else if(node == list->first){
		// remove first element
		list->first			= node->next;
		check(list->first != NULL, "Invalid list, \nsomehow the new first element is NULL! \n(list->first->next == NULL)");
		list->first->prev		= NULL;
	}else if(node == list->last){
		// remove last element
		list->last			= node->prev;
		check(list->last != NULL, "Invalid list, \nsomehow the new last element that is NULL! \n(list->last->prev == NULL)");
		list->last->next	= NULL;
	}else{
		// remove any other element
		ListNode *after		= node->next;
		ListNode *before	= node->prev;
		after->prev			= before;
		before->next		= after;
	}


	list->count--;
	result					= node->value;
	free(node);

error:
	return result;
}


// Extra Credit begins
// print list
void List_print(List *list)
{
	check(list, "List is NULL, doesn't exist.");
	check(list->first && list->last, "List is Empty.");

	printf("\n[FIRST] <=> ");

	LIST_FOREACH(list, first, next, cur) {
		printf("%s <=> ",(char*)cur->value);
	}

	printf("[LAST]\ncount: %d\n", list->count);

error:
	return;
}



//print list backwards
void list1ackwards_print(List *list){
	

}



// copy a list
List *List_copy(List *list)
{
	check(list, "List is NULL, doesn't exist.");
	check(list->first && list->last, "List is Empty.");

	List *list1				= List_create();
	check(list1 != NULL, "Failed to create list.");

	LIST_FOREACH(list, first, next, cur) {
		List_push(list1, cur->value);
	}
	return list1;

error:
	return list1;
}



// join list1 to list 
// delete list1 if del_list1 set to >= 1
void List_join(List *list, List *list1)  
{
	check(list, "First list is NULL, doesn't exist.");
	check(list1, "Second list is NULL, doesn't exist.");
	check(list->first && list->last, "First list is Empty.");
	check(list1->first && list1->last, "Second list 2 is Empty.");

	// join list to list1 v1
	// list1 still points to the concat part of list join
//	list1->first->prev		= list->last;
//	list->last->next		= list1->first;
//	list->last				= list1->last;
//	list->count				= list->count + list1->count;
//
//	if (del_list_b == 0){

//		List *temp			= List_create();
//		mu_assert(temp != NULL, "Failed to create list.");
//		temp				= List_copy(list_b);
//		list_b				= temp;
//		temp				= NULL;	
//
//	} else {
//		list_b				= List_create();
//		List_destroy(list_b);
//	}

	// join list to list1 v2
	// slower implementation than v1
	LIST_FOREACH(list1, first, next, cur) {
		List_push(list, cur->value);
	}

	return ;

error:
	return;
}




// Split list1 to list 
// delete list1 if del_list1 set to >= 1
void List_split(List *list, List *list1, ListNode *node)  
{
	check(list, "FirstlList is NULL, doesn't exist.");
	check(list1, "Second list is NULL, doesn't exist.");
	check(list->first && list->last, "First list is Empty.");
	check(list->first != node, "Can't split list at first node.");

	int count_check = 0;
	LIST_FOREACH(list, first, next, cur) {
		if(cur == node){
			break;
		}
		count_check++;
	}

	// split list to list1 v2
	list1->last			= list->last;
	list->last			= node->prev;
	list1->first		= node;
	list->last->next	= NULL;
	list1->first->prev	= NULL;
	list1->count		= list->count - count_check;
	list->count			= count_check;

	return ;

error:
	return;
}
// end of Extra Credit
