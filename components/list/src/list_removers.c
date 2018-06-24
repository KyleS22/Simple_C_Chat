/*
* list_removers.c
* Authors:
*     Kyle Seidenthal
* Date: 12-09-16
* Description:  Functions used in removing items snd lists
* 		are implemented here.
*/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void *ListRemove(LIST *list){
	void *item;
	NODE *next;

	/* if list is NULL, print error message*/
	if(list == NULL){
		printf("Error in procedure ListRemove(): Invalid parameter list\n");
	}

	/* If there is no current node, we cannot remove it */
	if(list->cur == NULL){
		printf("Cannot remove nodes from an empty list\n");
		return NULL;
	}

	item = list->cur->item;	/* Save the item */


	/* If we are deleting the tail */
	if(list->cur->next == NULL){
		list->tail = list->tail->prev;
		/* Handle the case where we delete the last node in the list */
		if(list->tail != NULL){
			list->tail->next = NULL;
		}
		next = list->cur->prev;	/* If we delete the tail, leave the cursor on the new tail */
	}else{
		/* Otherwise link the current node's next node to its prev node */
		list->cur->next->prev = list->cur->prev;
		next = list->cur->next;	/* Save the next item */
	}
	
	/* If we are deleting the head */
	if(list->cur->prev == NULL){
		list->head = list->head->next;

		/* Handle the case where we delete the last node in the list */
		if(list->head != NULL){
			list->head->prev = NULL;
		}
	}else{	
		/* Otherwise link the current node's prev node to its next node */
		list->cur->prev->next = list->cur->next;
	}

	list->cur->item = NULL;	/* Reset the current item */
	list->cur->prev = NULL;	/* Reset the previous reference */
	
	list->cur->next = next_avail_node;	/* Link the node into the free node array */
	next_avail_node = list->cur;		/* Update next available node */
	list->cur = next;			/* Leave the cursor in the next node in the list */
	list->size = list->size - 1;

	return item; 	/* Return the item */

}

void ListFree(LIST *list, void (*itemFree)(void *itemToBeFreed)){
	int i;
	NODE *current;
	/* If list is empty, print error message */
	if(list == NULL){
		printf("Error in procedure ListFree(): Invalid parameter list\n");
	}

 	ListFirst(list);	/* Go to the beginning of the list */
	/* Call itemfree on every item in the list */
	for(i =0; i < list->size; i++){
		current = list->cur;
		if(current->next != NULL){
			ListNext(list);
		}
		(*itemFree)(current);
	}
	
	/* Reset list parameters */
	list->head = NULL;
	list->tail = NULL;
	list->cur = NULL;
	list->next_list = next_avail_list;
	next_avail_list = list;	/* Update next_avail_list */
	free(list);	
}

void *ListTrim(LIST *list){
	void *item;
	/* If list is empty, print error message */
	if(list == NULL){
		printf("Error in procedure ListTrim(): Invalidparameter list\n");
	}
	ListLast(list);
	item = ListRemove(list);
	return item;
}

