/*
* list.h
* author:
*     Kyle Seidenthal
*
* date: 23-06-18
* description:
* 	Linked list implementation
*/

#ifndef INCLUDE_LIST
#define INCLUDE_LIST

/* The max number of lists allowed to be created */
extern int max_lists;

/* The max number of nodes allowed per list */
#define max_nodes 20

/* Node structure for containing list elements */
typedef struct NODE{
        void *item; 
        struct NODE *next;
        struct NODE *prev;
}NODE;

/* List structure to represent a list */
typedef struct LIST{
        struct NODE *head;
        struct NODE *tail;
        struct NODE *cur;
        struct LIST *next_list;
        int size;
}LIST;


extern LIST *lists;

extern NODE *nodes;

extern LIST *next_avail_list;

extern NODE *next_avail_node;


/* 
 * Function: ListCreate
 * --------------------
 *
 * Create a new empty list
 *
 * Return: Reference to the new list
 *         Void on failure
 */
struct LIST *ListCreate();

/* 
 * Function: ListCount
 * -------------------
 *
 * Returns the number of items in list.
 */
int ListCount(struct LIST *list);

/* 
 * Function: ListFirst
 * -------------------
 *
 * Returns a pointer to the first item in list
 * and makes the first item the current item.
 */
void *ListFirst(struct LIST *list);

/* 
 * Function: ListLast
 * ------------------
 *
 * Returns a pointer to the last item in list
 * and makes the last item the current one.
 */
void *ListLast(struct LIST *list);

/* 
 * Function: ListNext
 * ------------------
 *
 * Advance list's current item by one,  and
 * returns a pointer to the new current item.
 * Returns NULL if the operation attempts to
 * advance the current item beyond the end of
 * the list.
 */
void *ListNext(struct LIST *list);


/* 
 * Function: ListPrev
 * -----------------
 *
 * Back up list's current item by one, and 
 * returns a pointer to the new current item.
 * Returns NULL if the operation attempts to
 * back up the current item beyond the start 
 * of the list.
 */
void *ListPrev(struct LIST *list);

/*
 * Function: ListCurr
 * -----------------
 * Returns a pointer to the current item in list.*/
void *ListCurr(struct LIST *list);

/* 
 * Function: ListAdd
 * -----------------
 *
 * Adds a new item to list directly after the current
 * item, and makes item the current item.
 * If the current pointer is at the end of the list,
 * the item is added at the end.
 *
 * Return: 0 on success
 *        -1 on failure
 */
int ListAdd(struct LIST *list, void *item);

/* 
 * Function: ListInsert
 * --------------------
 *
 * Adds item to list directly before the current item,
 * and makes the new item the current one.
 * If the current pointer is at the start of the list,
 * the item is added at the start.
 *
 * Return: 0 on success
 *        -1 on failure
 */
int ListInsert(struct LIST *list, void *item);

/* 
 * Function: ListAppend
 * --------------------
 *
 * Adds item to the end of list, and makes the new item
 * the current one.
 *
 * Return: 0 on success
 *        -1 on failure
 */
int ListAppend(struct LIST *list, void *item);

/* 
 * Function: ListPrepend
 * ---------------------
 *
 * Adds item to the front of list, and makes the new item
 * the current one.
 *
 * Return: 0 on success
 *        -1 on failure
 */
int ListPrepend(struct LIST *list, void *item);


/* 
 * Function: List Remove
 * ---------------------
 *
 * Return current item and take it out of list.
 * Make the next item the current one.
 */
void *ListRemove(struct LIST *list);

/* 
 * Function: ListConcat
 * --------------------
 *
 * Adds list2 to the end of list1.  The current
 * pointer is set to the current pointer of list1.
 * List2 no longer exists after the operation.
 */
void ListConcat(struct LIST *list1, struct LIST *list2);

/* 
 * Function: ListFree
 * ------------------
 *
 * Delete list.
 * itemFree is a pointer to a routine that frees an item.
 */
void ListFree(struct LIST *list, void (*itemFree)(void *itemToBeFreed));

/* 
 * Function: ListTrim
 * ------------------
 *
 * Return last item and take it out of list.  
 * Make the new last item the current one.
 */
void *ListTrim(struct LIST *list);

/* 
 * Function: ListSearch
 * --------------------
 *
 * Searches list stating at the current item until
 * the end is reached or a match is found.
 * A match is determined by the comparitor parameter,
 * which is a routine that takes as its first arg an item
 * pointer, and its second arg comparisonArg.
 * Comparator returns 0 if the the item and comparisonArg
 * don't match and returns 1 if the item and comparisonArg 
 * do match.
 * If a match is found, the current pointer is left at the 
 * matched item and the pointer to that item is returned.
 * If no match is found, the current pointer is left at the
 * end of the list and a NULL pointer is returned.
 */
void *ListSearch(struct LIST *list, int (*comparator)(void *item, void *comparisonArg), void *comparisonArg);


#endif /* INCLUDE_LIST */
                                         
