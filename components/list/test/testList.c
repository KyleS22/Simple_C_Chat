/*
* mytestlist.c
* Authors:
*     Kyle Seidenthal
*    
*     Nico Dimaano
*
* Date: 13-09-16
* Description: Test cases for the list library
*/

#define TESTNRM "\x1B[0m"
#define TESTPASS "\x1B[32m"
#define TESTFAIL "\x1B[31m"

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Dummy function to test with ListFree() */
void itemFree(void *itemToBeFreed){
	assert(itemToBeFreed);		
}

/* Dummy function to test with ListSearch()*/
int comparator(void *item, void *comparisonArg){
	if(item == comparisonArg){
		return 1;
	}else{
		return 0;
	}
}

int main(){

	/*Define test variables*/       

	struct LIST *test_list;		/* A test list */
	
	struct LIST *list_two;		/* A second test list*/

	struct LIST *listArray[18];	/* An array if lists to create */

	struct LIST *finalList;

	int error;			/*A place to store return values from functions*/

	void *returnItem;		/* A place to store return values from void* functions when not expecting an integer */

	/* Define items to add to the list */
	int item1 = 42;		/* An item to add to the list*/
	int item2 = 84;
	int item3 = 3;
	int item4 = 4;
	int item5 = 5;
	int itemArray [15];
	int finalItem = 100;
	int itemCheck;

	int i;
	for(i = 0; i < 15; i ++){
		itemArray[i] = i;
	}
	

	/* TESTING FOR ListCreate() */
	printf("TESTING ListCreate()...\n");

	test_list = ListCreate();
	list_two = ListCreate();
	
	if(test_list == NULL){
		printf("Error with function ListCreate()\n");
		assert(0);
	}else{
		printf("Got to procedure ListCreate()\n");
	}

	if(list_two == NULL){
		printf("Error with function ListCreate()\n");
		assert(0);
	}else{
		printf("Successfully created a second list\n");
	}

	/* Test to ensure the head is null */
	if(test_list->head != NULL){
		printf("Error with function ListCreate(): Head is not null");
		assert(0);
	}else{
		printf("The head of the list is NULL as expected\n");
	}
	
	/* Test to ensure the size is 0 */
	if(test_list->size != 0){
		printf("Error with function ListCreate(): Size is not 0");
		assert(0);
	}else{
		printf("The size is 0 as expected\n");
	}
	
	if(test_list->cur != test_list->head){
		printf("Error with function ListCreate(): cur is not head");
		assert(0);
	}else{
		printf("The current item is the head as expected\n");
	}

	/* Now we will test the case where the user creates the max amount of lists */
	for(i = 0; i < 18; i++){
		listArray[i] = ListCreate();
	}

	if(listArray == NULL){
		printf("Error: listArray is NULL\n");
		assert(0);
	}

	printf("Successfully Created 18 more lists\n");
	
	printf("The next statement should be an error about there being no lists left\n");
	finalList = ListCreate();
	
	if(finalList != NULL){
		printf("Error finalList is NULL\n");
		assert(0);
	}

	
	printf("\n");

	/*TESTING FOR ListAdd() */
	printf("TESTING ListAdd()....");

	error = ListAdd(test_list,  &item1);

	/* 0 is success */
	if(error == 0){
		printf("Got to procedure ListAdd()\n");
		printf("Added item 1 successfuly\n");
	}
	
	/* Ensure item 1 is the head */
	if(*(int *)test_list->head->item != item1){
		printf("Error with ListAdd(): Item not added correctly\n");
		assert(0);
	}else{
		printf("The new item is currently the head as expected\n");
	}
	
	/* Make sure the item1 is the tail */
	if(*(int *)test_list->tail->item != item1){
		printf("Error with ListAdd(): tail should be item1\n");
		assert(0);
	}else{
		printf("Tail is item1 as expected\n");
	}
	
	/* Ensure the size was updated correctly */
	if(test_list->size != 1){
		printf("Error with ListAdd(): Incorrect size\n");
		assert(0);
	}else{
		printf("The size of the list is 1 as expected\n");
	}

	/* Add item 2 */
	error = ListAdd(test_list, &item2);
	
	/* Make sure there was no error inserting item2 */	
	if(error != 0){
		printf("Error inserting item 2\n");
		assert(0);
	}else{
		printf("Successfully added item 2\n");
	}

	/* Make sure the current node is item2 */
	if(*(int *)test_list->cur->item != item2){
		printf("Error with ListAdd(): item2 inserted incorrectly\n");
		assert(0);
	}else{
		printf("The current node is item2 as expected\n");
	}
	
	/* Make sure the size was updated correctly */
	if(test_list->size != 2){
		printf("Error with ListAdd(): incorrect size\n");
		assert(0);
	}else{
		printf("The size is 2 as expected\n");
	}

	/* Make sure the item before the current item is still item1 */
	if(*(int *)test_list->cur->prev->item != item1){
		printf("Error with ListAdd(): item1 is not prev to item2\n");
		assert(0);
	}else{
		printf("The item before item2 is item1 as expected\n");
	}
	
	/* Make sure item1 is still the head of the list */
	if(*(int *)test_list->head->item != item1){
		printf("Error with ListAdd(): head should be item1\n");
		assert(0);
	}else{
		printf("Item1 is still the head as expected\n");
	}

	/* Make sure the new item is the tail */
	if(*(int *)test_list->tail->item != item2){
		printf("Error with ListAdd(): tail should be item2\n");
		assert(0);
	}else{
		printf("tail is item2 as expected\n");
	}
	
	/* Make sure the last item in the list points to NULL */
	if(test_list->cur->next != NULL){
		printf("Error, end of list is not null\n");
		assert(0);
	}else{
		printf("The last item in the list points to NULL as expected\n");
	}

	printf("\n");


	/*TESTING FOR ListInsert() */
	printf("Testing ListInsert()....");

	error = ListInsert(test_list, &item3);

	if(error == 0){
		printf("Got to procedure ListInsert()\n");
		printf("Item3 inserted successfully\n");
	}
	/* Ensure the current item is the item we inserted */
	if(*(int *)test_list->cur->item != item3){
		printf("Error with ListInsert(): Current item should be item 3\n");
		assert(0);
	}else{
		printf("The current item is item3 as expected\n");
	}

	if(*(int *)test_list->cur->next->item != item2){
		printf("Error with ListInsert(): next item should be item2 \n");
		assert(0);
	}else{
		printf("The next item is item2 as expected\n");
	}

	if(*(int *)test_list->head->item != item1){
		printf("Error with ListInsert(): head should be item 1 \n");
		assert(0);
	}else{
		printf("The head is still item1 as expected\n");
	}

	if(*(int *)test_list->cur->prev->item != item1){
		printf("Error with ListInsert(): prev item should be item1 \n");
		assert(0);
	}else{
		printf("The prev item is item 1 as expected\n");
	}

	if(test_list->size != 3){
		printf("Error with ListInsert(): size is not 3\n");
		assert(0);
	}else{
		printf("Size is 3 as expected\n");
	}

	printf("\n");

	/*TESTING FOR ListAppend() */
	printf("Testing ListAppend()....");
	error = ListAppend(test_list, &item4);

	if(error == 0){
		printf("Got to procedure ListAppend()\n");
		printf("item4 added successfully\n");
	}

	/* Check to make sure the list cur is the new item */
	if(*(int *)test_list->cur->item != item4){
		printf("Error with ListAppend(): Item not appended correctly\n");
		assert(0);	
	}else{
		printf("List cur is item4 as expected\n");
	}

	/* Check to see if the tail was updated correctly */
	if(*(int *)test_list->tail->item != item4){
		printf("Error with ListAppend(): Tail should be item4\n");
		assert(0);	
	}else{
		printf("Tail is item4 as expected\n");
	}

	/* Check that the previous item is still item2 */
	if(*(int *)test_list->cur->prev->item != item2){
		printf("Error with ListAppend(): Prev item should be item2\n");
		assert(0);	
	}else{
		printf("The previous item is item 2 as expected\n");
	}

	/* Check that size was updated */
	if(test_list->size != 4){
		printf("Error with ListAppend(): Size should be 4\n");
		assert(0);	
	}else{
		printf("Size is 4 as expected\n");
	}

	printf("\n");

	/*TESTING FOR ListPrepend() */
	printf("Testing ListPrepend()....");

	error = ListPrepend(test_list, &item5);

	if(error == 0){
		printf("Got to procedure ListPrepend()\n");
		printf("Successfully added item5\n");

	}

	/* Test that the current item is item5 */
	if(*(int *)test_list->cur->item != item5){
		printf("Error with ListPrepend(): Current item should be item5\n");
		assert(0);	
	}else{
		printf("The current item is item5 as expected\n");
	}

	/* Test that the head is item5 */
	if(*(int *)test_list->head->item != item5){
		printf("Error with ListPrepend(): head should be item5\n");
		assert(0);	
	}else{
		printf("The head item is item5 as expected\n");
	}

	/* Test that the next item is still item1 */
	if(*(int *)test_list->cur->next->item != item1){
		printf("Error with ListPrepend(): next item should be item1\n");
		assert(0);	
	}else{
		printf("The next item is item1 as expected\n");
	}

	printf("\n");

	/* Now to test the add functions more thouroughly, we will fill list 2 */
	for(i = 0; i < 15; i++){
		error = ListAdd(list_two, &itemArray[i]);

		if(error != 0){
			printf("Error adding item to list_two\n");
			assert(0);	
		}else if(i == 14){
			printf("Successfully added 15 items to list_two\n");
		}
	}

	/* By adding finalItem to list_two, we should get an error about there being no nodes left */
	printf("The next statement should be an error about there being no nodes left\n");
	error = ListAdd(list_two, &finalItem);

	if(error == 0){
		printf("Error.  Should have rejected adding finalItem\n");

		assert(0);	
	}

	printf("\n");

	/*TESTING FOR ListConcat() */
	printf("Testing ListConcat()....");
	itemCheck = *(int *)list_two->tail->item;	/* Save the tail item of list2 to compare with the new tail of list 1 */
	ListConcat(test_list, list_two);

	printf("Got to procedure ListConcat()\n");
	
	/* Make sure the tail was updated properly */
	if(*(int *)test_list->tail->item != itemCheck){
		printf("Error with ListConcat(): tail not set properly\n");
		assert(0);	
	}else{
		printf("The new tail is 15 as expected \n");
	}
	
	/* Make sure the head, cur and tail were reset for list_two */
	if(list_two->head != NULL){
		printf("Error with ListConcat(): head is not NULL\n");
		assert(0);	
	}else{
		printf("The head of list_two was successfully reset\n");
	}

	if(list_two->cur != NULL){
		printf("Error with ListConcat(): cur was not properly reset\n");
		assert(0);	
	}else{
		printf("The current item of list_two has been successfully reset\n");
	}

	if(list_two->tail != NULL){
		printf("Error with ListConcat(): tail was not properly reset\n");	
		assert(0);	
	}else{
		printf("The tail of list_two has been successfully reset\n");
	}

	printf("\n");

	/* TESTING FOR ListCount */
	printf("Testing ListCount()....");
	error = ListCount(test_list);

	if(error != -1){
		printf("Got to procedure ListCount()\n");
	}

	/* test_list should have 20 nodes in it */
	if(error != 20){
		printf("Error with procedure ListCount(): Count should be 20 for test_list\n");
		assert(0);	
	}else{
		printf("ListCount was 20 for test_list as expected\n");
	}

	error = ListCount(list_two);	
	/* list_two should be empty */
	if(error != 0){
		printf("Error with procedure ListCount(): Count should be 0 for list_two\n");
		assert(0);	
	}else{
		printf("ListCount was 0 for list_two as expected\n");
	}

	printf("\n");
	
	/* TESTING FOR ListFirst() */
	printf("Testing ListFirst()...");	
	error = *(int *)ListFirst(test_list);
	printf("Got to procedure ListFirst()\n");

	/* Make sure the item is what we think it is */
	if(error != item5){
		printf("There was an error with ListFirst(): Item should be item5\n");
		assert(0);	
	}else{
		printf("The first item is item5 as expected\n");
	}
	/* Make sure list cur was set */
	if(*(int *)test_list->cur->item != item5){
		printf("There was an error with ListFirst(): Item should be item5\n");
		assert(0);	
	}else{
		printf("The current item is item5 as expected\n");
	}

	printf("\n");

	/* TESTING FOR ListLast */
	printf("Testing ListLast()....");
	/* Get the tail of test_list */
	itemCheck = *(int *)test_list->tail->item;

	error = *(int *)ListLast(test_list);
	printf("Got to procedure ListLast()\n");

	/* Make sure the returned item is correct */
	if(error != itemCheck){
		printf("There was an error with ListLast(): Last item should be itemCheck\n");
		assert(0);	
	}else{
		printf("ListLast was itemCheck as Expected\n");
	}

	/* Make sure the cur for test_list was set properly */
	if(*(int *)test_list->cur->item != itemCheck){
		printf("There was an error with ListLast(): Current item should be itemCheck\n");
		assert(0);	
	}else{
		printf("Current item was itemCheck as expected\n");
	}

	printf("\n");

	/* TESTING FOR ListNext */
	printf("Testing ListNext()....");

	ListFirst(test_list);	/* Set test_lists cur to the first item */

	error = *(int *)ListNext(test_list);
	printf("Got to procedure ListNext()\n");

	/* Make sure the returned item is item1 */
	if(error != item1){
		printf("There was an error with ListNext(): Next item should be item1\n");
		assert(0);	
	}else{
		printf("The next item was item1 as expected.\n");
	}

	/* Make sure test_list's cur is item1 */
	if(*(int *)test_list->cur->item != item1){
		printf("There was an error with ListNext(): test_list's cur should be item1\n");
		assert(0);	
	}else{
		printf("The current item is item1 as expected\n");
	}

	error = *(int *) ListNext(test_list);	/* Go to the next item */

	/* Make sure the returned item is item3 */
	if(error != item3){
		printf("There was an error with ListNext(): Next item should be item3\n");
		assert(0);	
	}else{
		printf("The next item was item3 as expected.\n");
	}

	/* Make sure test_list's cur is item3 */
	if(*(int *)test_list->cur->item != item3){
		printf("There was an error with ListNext(): test_list's cur should be item3\n");
		assert(0);	
	}else{
		printf("The current item is item3 as expected\n");
	}
	
	ListLast(test_list);	/* Go to the last item in the list */

	/* Make sure the returned value is NULL */
	returnItem = ListNext(test_list);

	if(returnItem != NULL){
		printf("There was an error with ListNext(): The next item should be NULL\n");
		assert(0);	
	}else{
		printf("The next item was NULL as expected\n");
	}

	printf("\n");

	/* TESTING FOR ListPrev */
	printf("Testinf ListPrev()....");
	ListLast(test_list);	/* Set test_lists cur to the last item */

	returnItem = ListPrev(test_list);
	printf("Got to procedure ListPrev()\n");

	/* Make sure the returned item is 13 */
	if(*(int *)returnItem != 13){
		printf("There was an error with ListPrev(): Prev item should be 13\n");
		assert(0);	
	}else{
		printf("The prev item was 13 as expected.\n");
	}

	/* Make sure test_list's cur is 13 */
	if(*(int *)test_list->cur->item != 13){
		printf("There was an error with ListPrev(): test_list's cur should be 13\n");
		assert(0);	
	}else{
		printf("The current item is 13 as expected\n");
	}

	returnItem = ListPrev(test_list);	/* Go to the prev item */

	/* Make sure the returned item is 12 */
	if(*(int *)returnItem != 12){
		printf("There was an error with ListPrev(): Next item should be 12\n");
		assert(0);	
	}else{
		printf("The next item was 12 as expected.\n");
	}

	/* Make sure test_list's cur is 12 */
	if(*(int *)test_list->cur->item != 12){
		printf("There was an error with ListPrev(): test_list's cur should be 12\n");
		assert(0);	
	}else{
		printf("The current item is 12 as expected\n");
	}
	
	ListFirst(test_list);	/* Go to the first item in the list */

	/* Make sure the returned value is NULL */
	returnItem = ListPrev(test_list);

	if(returnItem != NULL){
		printf("There was an error with ListPrev(): The prev item should be NULL\n");
		assert(0);	
	}else{
		printf("The prev item was NULL as expected\n");
	}

	printf("\n");

	/* TESTING FOR ListCurr */
	printf("Testing ListCurr()....");
	ListFirst(test_list);

	returnItem  = ListCurr(test_list);
	printf("Got to procedure ListCurr()\n");

	/* Make sure the returned item is item5 */
	if(*(int *)returnItem != item5){
		printf("There was an error with ListCurr(): The current item should be item5.\n");
		assert(0);	
	}else{
		printf("The current item was item5 as expected.\n");
	}

	ListNext(test_list);			/* Move to the next item */
	returnItem = ListCurr(test_list);	/* Get the current item */

	if(*(int *)returnItem != item1){
		printf("There was an error with ListCurr(): The current item should be item1\n");	
		assert(0);	
	}else{
		printf("The current item was item1 as expected.\n");
	}

	printf("\n");

	/* TESTING FOR ListSearch */
	printf("Testing ListSearch()....\n");

	/* Make sure the comparator function works */
	error = comparator(&item1, &item1);
	if(error == 1){
		printf("Comparator function works as expected for comparing equal items\n");
	}else{
		printf("Comparator function does not work as expected\n");
		assert(0);	
	}

	error = comparator(&item1, &item2);
	if(error == 0){
		printf("Comparator function works as expected for comparing non-equal items\n");
	}else{
		printf("Comparator function does not work as expected\n");
		assert(0);	
	}

	/* Search list_two (which is empty) for item1 */
	printf("Expecting error about searching empty list....");
	returnItem = ListSearch(list_two, *comparator, &item1);
	if(returnItem != NULL){
		printf("There was an error with ListSearch: Searching an empty list returned incorrect result\n");
			
	}else{
		printf("Search for item1 in list_two returned NULL as expected\n");
	}
	
	
	/* Go to the first item in test_list and search for item1 */
	ListFirst(test_list);
	returnItem = ListSearch(test_list, *comparator, &item1);
	
	if(*(int *)returnItem != item1){
		printf("There was an error with ListSearch(): Search for item1 in test_list was unsuccessful\n");
		assert(0);	
	}else{
		printf("item1 was found in test_list as expected.\n");
	}

	/* Make sure the list's cur was updated */
	if(*(int *)test_list->cur->item != item1){
		printf("There was an error with ListSearch(): The current pointer of the list was not upated\n");
		assert(0);	
	}else{
		printf("The current pointer of the list was updated properly\n");
	}


	/* Search test_list for an item that does not exist in the list */
	returnItem = ListSearch(test_list, *comparator, &finalItem);

	if(returnItem != NULL){
		printf("There was an error with ListSearch(): an item that does not exist was found\n");
		assert(0);	
	}else{
		printf("Non-existant item not found, which really is a good thing\n");
	}

	printf("\n");
		

	/* TESTING FOR ListRemove */
	ListFirst(test_list);
	printf("Tesitng ListRemove()....");
	
	returnItem = ListRemove(test_list);
	printf("Got to procedure ListRemove()\n");
	
	/* Make sure the returned item is the item we expect */
	if(*(int *)returnItem != item5){
		printf("There was an error with ListRemove(): The removed item should be item5\n");
		assert(0);	
	}else{
		printf("item5 removed successfully\n");
	}

	/* Make sure the head was reset properly */
	if(*(int *)test_list->head->item != item1){
		printf("There was an error with ListRemove(): Thead head was not reset properly\n");
		assert(0);	
	}else{
		printf("The new head is item1 as expected\n");
	}

	/* Make sure the current item is item1 */
	if(*(int *)test_list->cur->item != item1){
		printf("There was an error with ListRemove(): The current item is not item1\n");
		assert(0);	
	}else{
		printf("The current item is item1 as expected\n");
	}


	ListLast(test_list);

	returnItem = ListRemove(test_list);

	/* Make sure the returned item is the item we expect */
	if(*(int *)returnItem != 14){
		printf("There was an error with ListRemove(): The removed item should be 14\n");
		assert(0);	
	}else{
		printf("14 removed successfully\n");
	}

	/* Make sure the tail was updated properly */
	if(*(int *)test_list->tail->item != 13){
		printf("There was an error with ListRemove(): The tail was not updated properly\n");
		assert(0);	
	}else{
		printf("The tail was updated properly\n");
	}

	/* Make sure the current item was updated */
	if(*(int *)test_list->cur->item != 13){
		printf("There was an error with ListRemove(): The current item was not updated properly\n");
		assert(0);	
	}else{
		printf("The current item is 13 as expected\n");
	}
	
	returnItem = ListFirst(test_list);

	returnItem = ListSearch(test_list, *comparator, &item2);	/* Place the cursor on item2 to delete it */
	if(returnItem == NULL){
		printf("There was an error with ListSearch(): could not find item2\n");
		assert(0);	
	}

	returnItem = ListRemove(test_list);


	/* Make sure the returned item is the item we expect */
	if(*(int *)returnItem != item2){
		printf("There was an error with ListRemove(): The wrong item was removed\n");
		assert(0);	
	}else{
		printf("item2 removed successfully\n");
	}

	/* Make sure the current item was properly updated */
	if(*(int *)test_list->cur->item != item4){
		printf("There was an error with ListRemove(): The current item is not item4\n");
		assert(0);	
	}else{
		printf("The current item is item4 as expected\n");
	}

	/* Make sure the previous item is item3 */
	if(*(int *)test_list->cur->prev->item != item3){
		printf("There was an error with ListRemove(): The previous item should be item3\n");
		assert(0);	
	}else{
		printf("The previous item is item3 as expected\n");
	}

	/* Make usre the next item is 0 */
	if(*(int *)test_list->cur->next->item != 0){
		printf("There was an error with ListRemove(): The next item should be 0\n");
		assert(0);	
	}else{
		printf("The next item is 0 as expected\n");
	}

	/* Now we delete all items from the list, and test the case where we remove an item from the empty list */
	
	ListFirst(test_list);
	for(i = test_list->size; i > 0; i--){
		ListRemove(test_list);
	}
	printf("Successfully removed all items\n");

	printf("The next statement should be an error about deleting from an empty list....");
	returnItem = ListRemove(test_list);

	/* Make sure the returned item is NULL */
	if(returnItem != NULL){
		printf("Error with ListRemove(): Should have returned NULL\n");
		assert(0);	
	}
	
	printf("\n");
	
	/* TESTING FOR ListTrim() */
	printf("Testing ListTrim()....");
	/* Populate the list */
	ListAdd(test_list, &item1);
	ListAdd(test_list, &item2);
	ListAdd(test_list, &item3);

	returnItem = ListTrim(test_list);
	printf("Got to procedure ListTrim()\n");
	if(*(int *)returnItem != item3){
		printf("Error with ListTrim(): Did not delete the last item\n");
		assert(0);	
	}else{
		printf("item3 deleted successfully\n");
	}

	returnItem = ListTrim(test_list);
	if(*(int *)returnItem != item2){
		printf("Error with ListTrim(): Did not delete item2\n");
		assert(0);	
	}else{
		printf("item2 deleted successfully\n");
	}

	returnItem = ListTrim(test_list);
	if(*(int *)returnItem != item1){
		printf("Error with ListTrim(): Did not delete item2\n");
		assert(0);	
	}else{
		printf("item1 deleted successfully\n");
	}

	printf("The next statement should be an error about deleting from an empty list....");
	returnItem = ListTrim(test_list);
	if(returnItem != NULL){
		printf("Error with ListTrim(): Deleted from empty list\n");
		assert(0);	
	}
	
	printf("\n");



	/* TESTING FOR ListFree */
	printf("Testing ListFree()....");
	/* Add some items to test_list */
	error = ListAdd(test_list, &item1);
	if(error != 0){
		printf("Something went wrong\n");
		assert(0);	
	}

	error = ListAdd(test_list, &item2);
	if(error != 0){
		printf("Something went wrong\n");
		assert(0);	
	}

	error = ListAdd(test_list, &item3);
	if(error != 0){
		printf("Something went wrong\n");
		assert(0);	
	}

	ListFree(test_list, itemFree);
	printf("Got to procedure ListFree()\n");

	if(test_list->head != NULL){
	       printf("test_list was not properly freed\n");
		assert(0);	
	}else{
		printf("test_list was successfully freed\n");
	}

	printf("\n");

	printf("%s ALL TESTS PASSED %s\n\n", TESTPASS, TESTNRM);
	return 0;
}
