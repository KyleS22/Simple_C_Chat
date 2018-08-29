/*
* list_movers.c
* Authors:
*     Kyle Seidenthal
* Date: 12-09-16
* Description: Functions used to indicate and change
* positions in the list are found here, as well as search-related
* functions.
*/

#include "list.h"
#include <stdio.h>

int ListCount(LIST *list){
	/* If list is null, print an error message and return -1 */
	if(list == NULL){
		printf("Error in procdure ListCount(): Invalid parameter list\n");
		return -1;
	}
	
	return list->size; /* Return the number of items in the list */
}

void *ListFirst(LIST *list){
	/* If list is null, print an error message */
	if(list == NULL){
		printf("Error in procdure ListFirst(): Invalid parameter list\n");
	}

	list->cur = list->head;	/* Set the current item to the list head */
	if(list->head != NULL){
		return list->head->item;	/* Return the list head */
	}else{
		return NULL;
	}
}

void *ListLast(LIST *list){
	/* If list is null, print an error message */
	if(list == NULL){
		printf("Error in procdure ListLast(): Invalid parameter list\n");
	}
	
	list->cur = list->tail;	/* Set the current item to the list tail */
	if(list->tail != NULL){
		return list->tail->item; /* Return the list tail */
	}else{
		return NULL;
	}
}

void *ListNext(LIST *list){
	/* If list is null, print an error message */
	if(list == NULL){
		printf("Error in procdure ListNext(): Invalid parameter list\n");
	}
	
	/* Make sure we don't advance past the end of the list */
	if(list->cur->next != NULL){
		list->cur = list->cur->next;	/* Update cur to the next item */
		return list->cur->item;		/* Return the item */
	}else{
		return NULL;			/* We tried to advance past the end of the list */
	}
}

void *ListPrev(LIST *list){
	/* If list is null, print an error message */
	if(list == NULL){
		printf("Error in procdure ListPrev(): Invalid parameter list\n");
	}

	/* Make sure we don't back up beyond the beginning of the list */
	if(list->cur->prev != NULL){
		list->cur = list->cur->prev;	/* Update cur to the previous item */
		return list->cur->item;		/* Return the item */
	}else{
		return NULL;			/* We tried to back up past the beginning of the list */
	}
}

void *ListCurr(LIST *list){
	/* If list is null, print an error message */
	if(list == NULL){
		printf("Error in procdure ListCurr(): Invalid parameter list\n");
	}	

	return list->cur->item;	/* Return the current list item */
}

void *ListSearch(LIST *list, int (*comparator)(void *item, void *comparisonArg), void *comparisonArg){
	int compare;
	/* If list is null, print and error message */
    if(list == NULL){
		printf("Error in procedure ListSearch(): Invalid parameter list\n");
    }
	
	/* Make sure the current pointer is not NULL */
	if(list->cur == NULL){
		printf("Cannot search empty list\n");
		return NULL;
	}	

	/* Check that the comparator function is callable */
	compare = (*comparator)(list->cur->item, list->cur->item);

	if(compare != 1){
		printf("Error in procedure ListSearch(): Invalid parameter (*comparator)(void *item)\n");
	}
	
	/* If the comparisonArg is null, print an error message*/
	if(comparisonArg == NULL){
		printf("Error in procedure ListSearch(): Invalid parameter comparisonArg\n");
	}

	
	/* While we can still go forward in the list and a match is not found */
	do {
		compare = (*comparator)(list->cur->item, comparisonArg);	/* Compare the items */
		if(compare == 1){
			return list->cur->item;		/* Return the item */
		}else{
			list->cur = list->cur->next;	/* Advance one item */
		}

	} while(list->cur->next != NULL && compare == 0);

	return NULL;
}



