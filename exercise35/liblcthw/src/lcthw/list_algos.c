#include <list_algos.h> 
#include <assert.h>
#include <dbg.h>


//swap then nodes
void List_swap_node(List *list, ListNode *left, ListNode *right)
{
	ListNode *before		= left->prev;
	ListNode *after			= right->next;
	
	// make sure cur->prev exits
	if (before){
		before->next		= right;
		right->prev			= before;
	}else{
		right->prev			= NULL;
		list->first			= right;
	}
	
	right->next				= left;
	left->prev				= right;

	//make sure cur->next->next exists
	if (after){
		left->next			= after;
		after->prev			= left;
	// else next is end of list
	}else{
		left->next			= NULL;
	}
}


//swap the node values
void List_swap_value(ListNode *left, ListNode *right)
{
	void *temp				= left->value;
	left->value				= right->value;
	right->value			= temp;
}


// bubble sort with outer for loop instead of do loop.
int List_bubble_sort(List *list, List_compare cmp)
{
	int length				= List_count(list);
	int i					= 0;

	for(i = 0; i < length; i++){
		LIST_FOREACH(list, first, next, cur){

			// swap nodes if next value smaller
			if (cur->next && cmp(cur->value, cur->next->value) > 0 ){

				//List_swap_node(list, cur, cur->next);

				List_swap_value(cur, cur->next);
				//make sure cur points to the correct list index
				//cur = right;
			}
		}
	}
	return 0;
}


// merge sort
List *List_merge_sort(List *list, List_compare cmp)
{
	// Base case. A list of 0 elements is sorted
	if (List_count(list) <= 1){
		return list;
	}

	// Recursive case.
	// Divide list into equal size sublists having the first and second
	// halves respectively. Assume list starts at 0
	List *left				= List_create();
	List *right				= List_create();
	int length				= List_count(list);
	int i					= 0 ;
	LIST_FOREACH(list, first, next, cur){
		if(i < length/2){
			List_push(left, cur->value);
		}else{
			List_push(right, cur->value);
		}
		i++;
	}

	// recusively merge sort both sublists
	List *left_sorted		= List_merge_sort(left, cmp);
	List *right_sorted		= List_merge_sort(right, cmp);

	// safety feature to ensure  you don't accidentally delete data that
	// has bth pointer pointed at the same location
	if(left_sorted != left) List_clear_destroy(left);	
	if(right_sorted != left) List_clear_destroy(right);

	return List_merge(left_sorted, right_sorted, cmp);
		
}

List *List_merge(List *left, List *right, List_compare cmp)
{
	List *sorted_list		= List_create();

	//merge node or node value
	char merge_n_or_v		= 'n';
	void *value_temp		= NULL;
	ListNode *node_temp		= NULL;	
	
	// This shifts the value and not the whole element
	while(List_count(left) > 0 || List_count(right) > 0){
	
		// merge by value
		if(merge_n_or_v == 'v'){
			if(List_count(left) > 0 && List_count(right) > 0){
				if(cmp(List_first(left), List_first(right)) <= 0){
					value_temp	= List_shift(left);
				} else {
					value_temp	= List_shift(right);
				}
				List_push(sorted_list, value_temp);
			
			} else if (List_count(left) > 0){
				value_temp		= List_shift(left);
				List_push(sorted_list, value_temp);
			
			} else if (List_count(right) > 0){
				value_temp		= List_shift(right);
				List_push(sorted_list, value_temp);
			}

		//merge by node
		} else if (merge_n_or_v == 'n'){
			if(List_count(left) > 0 && List_count(right) > 0){
				if(cmp(List_first(left), List_first(right)) <= 0){
					node_temp	= List_shift_node(left);
				} else {
					node_temp	= List_shift_node(right);
				}
				List_push_node(sorted_list, node_temp);
			
			} else if (List_count(left) > 0){
				node_temp		= List_shift_node(left);
				List_push_node(sorted_list, node_temp);
			
			} else if (List_count(right) > 0){
				node_temp			= List_shift_node(right);
				List_push_node(sorted_list, node_temp);
			}
		}
	}
	return sorted_list;
}
