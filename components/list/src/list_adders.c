/*
* list_adders.c
* Authors:
*     Kyle Seidenthal
*
* Date: 12-09-16
* Description: Functions used to add items to 
* a list as well as create a new list.
*/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>


NODE *nodes;
LIST *lists;
NODE *next_avail_node = NULL;
LIST *next_avail_list;

LIST *ListCreate(){
	LIST *list;
	
	/* Initialize array of NODES if not already done */
	if(next_avail_node == NULL){
		int i;
		nodes = malloc(max_nodes * sizeof(NODE));
		lists = malloc(max_nodes * sizeof(LIST));
		next_avail_list = &lists[0];

		for(i = 0; i < max_nodes-1; i++){
			nodes[i].next = &nodes[i+1];
			lists[i].next_list = &lists[i+1];
		}
		nodes[i].next = NULL;
		lists[i].next_list = NULL;

		next_avail_node = &nodes[0];
	}
	if(next_avail_list != NULL){
		list = next_avail_list;
	}else{
		printf("Error: No more lists left\n");
		return NULL;
	}
	
	/* If there is a node available, there can still be another list */
	if(next_avail_node){
		next_avail_list = next_avail_list->next_list; /* Advance to the next available list */
		return list;	
	}else{
		return NULL;
	}	
}


int ListAdd(LIST *list, void *item){
	NODE *new_item;
	NODE *cur;

	/*If the list or item is NULL, print error message and return error code -1*/
	if(list == NULL){
		printf("Error in procedure ListAdd(): Invalid parameter list\n");
		return -1;
	}else if(item == NULL){
		printf("Error in procedure ListAdd(): Invalid parameter item\n");
		return -1;
	}
	
	if(next_avail_node){
		new_item = next_avail_node;
		next_avail_node = next_avail_node->next;
	}else{
		printf("Error: No available nodes.\n");
		return -1;
	}

	/* Set the value of new item and unlink it from the node array*/
	new_item->item = item;
	new_item->next = NULL;
	
	/* Get the current list item */
	cur = list->cur;
	
	/* Link the new item after the current item */
	if(list->head == NULL && cur == NULL){
		list->head = new_item;
		list->tail = new_item;
		new_item->prev = NULL;
		new_item->next = NULL;
	}else{
		new_item->prev = cur;
		if(cur->next != NULL){
			cur->next->prev = new_item;
		}else{
			/* We are adding to the end of the list and the tail needs to be updated */
			list->tail = new_item;
		}

		new_item->next = cur->next;
		cur->next = new_item;
		
	}
	list->cur = new_item;
	list->size ++;
	
	return 0;	/* Success */
}

int ListInsert(LIST *list, void *item){
	NODE *new_item;
	NODE *cur;
	
	/*If the list or item is NULL, print error message and return error code -1*/
	if(list  == NULL){
		printf("Error in procedure ListInsert(): Invalid parameter list\n");
		return -1;
	}else if(item == NULL){
		printf("Error in procedure ListInsert(): Invalid parameter item\n");
		return -1;
	}
	
	if(next_avail_node){
		new_item = next_avail_node;
		next_avail_node = next_avail_node->next;
	}else{
		printf("Error: No available nodes.\n");
		return -1;
	}

	/* Set the value of new item and unlink it from the node array*/
	new_item->item = item;
	new_item->next = NULL;
	
	/* Get the current list item */
	cur = list->cur;
	
	/* Link the new item before the current item */
	if(list->head == NULL && cur == NULL){
		/* The new item is the new head */
		list->head = new_item;
		list->tail = new_item;
		new_item->prev = NULL;
		new_item->next = NULL;
	}else{
		new_item->next = cur;
		if(cur->prev != NULL){
			cur->prev->next = new_item;
			new_item->prev = cur->prev;
		}else{
			/* We are inserting to the beginning of the list and the head needs to be updated */
			list->head = new_item;
		}


		cur->prev = new_item;
	}
	list->cur = new_item;
	list->size ++;

	return 0;	/* Success */
}

int ListAppend(LIST *list, void *item){
	NODE *new_item;
	NODE *cur;
	
	/*If the list or item is NULL, print error message and return error code -1*/
	if(list  == NULL){
		printf("Error in procedure ListInsert(): Invalid parameter list\n");
		return -1;
	}else if(item == NULL){
		printf("Error in procedure ListInsert(): Invalid parameter item\n");
		return -1;
	}
	
	if(next_avail_node){
		new_item = next_avail_node;
		next_avail_node = next_avail_node->next;
	}else{
		printf("Error: No available nodes.\n");
		return -1;
	}

	/* Set the value of new item and unlink it from the node array*/
	new_item->item = item;
	new_item->next = NULL;
	
	/* Get the tail item */
	cur = list->tail;
	
	/* Link the new item to the end of the list */
	if(list->head == NULL && cur == NULL){
		/* The new item is the new head */
		list->head = new_item;
		list->tail = new_item;
		new_item->prev = NULL;
		new_item->next = NULL;
	}else{
		new_item->prev = cur;
		cur->next = new_item;
	}
	list->tail = new_item;

	list->cur = new_item;
	list->size ++;

	return 0;	/* Success */
}

int ListPrepend(LIST *list, void *item){
	NODE *new_item;
	NODE *cur;
	
	/*If the list or item is NULL, print error message and return error code -1*/
	if(list  == NULL){
		printf("Error in procedure ListInsert(): Invalid parameter list\n");
		return -1;
	}else if(item == NULL){
		printf("Error in procedure ListInsert(): Invalid parameter item\n");
		return -1;
	}
	
	if(next_avail_node){
		new_item = next_avail_node;
		next_avail_node = next_avail_node->next;
	}else{
		printf("Error: No available nodes.\n");
		return -1;
	}

	/* Set the value of new item and unlink it from the node array*/
	new_item->item = item;
	new_item->next = NULL;
	
	/* Get the head item */
	cur = list->head;
	
	/* Link the new item to the end of the list */
	if(list->head == NULL && cur == NULL){
		/* The new item is the new head */
		list->head = new_item;
		list->tail = new_item;
		new_item->prev = NULL;
		new_item->next = NULL;
	}else{
		new_item->next = cur;
		cur->prev = new_item;
	}
	list->head = new_item;

	list->cur = new_item;
	list->size ++;

	return 0;	/* Success */
}

void ListConcat(LIST *list1, LIST *list2){
	/*If either list is null, print an error message*/
	if(list1 == NULL){
		printf("Error in procedure ListConcat(): Invalid parameter list1\n");
	}else if(list2 == NULL){
		printf("Error in procedure ListConcat(): Invalid parameter list2\n");
	}
	/* Link the two lists together head to tail */
	list1->tail->next = list2->head;
	list2->head->prev = list1->tail;
	list1->tail = list2->tail;
	list1->size = list1->size + list2->size;

	/* Reset list2 */
	list2->head = NULL;
	list2->cur = NULL;
	list2->tail = NULL;
	list2->size = 0;
}

