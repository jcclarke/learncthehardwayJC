#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <list.h>

typedef int (*List_compare)(const void *a, const void *b);

void List_swap_node(List *list, ListNode *left, ListNode *right);

void List_swap_value(ListNode *left, ListNode *right);

int List_bubble_sort(List *list, List_compare cmp);

List *List_merge_sort(List *list, List_compare cmp);

List *List_merge(List *left, List *right, List_compare cmp);

#endif
