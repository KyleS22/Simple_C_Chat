/*
* queue.h
* author:
*     Kyle Seidenthal
*
* date: 26-06-18
* description: Queue interface built on a linked list library
*/

#ifndef INCLUDE_QUEUE
#define INCLUDE_QUEUE

#include "list.h"

typedef struct QUEUE{
	struct LIST *list;
}QUEUE;

/*
 * Function: QueueCreate
 * ---------------------
 *
 * Create a new empty queue.
 *
 * Return: Reference to the new queue.
 * 	   Void on failure
 */
struct QUEUE *QueueCreate();


/*
 * Function: QueueCount
 * --------------------
 *
 * Count the number of items in the queue.
 *
 * Return: The number of items in the queue.
 */
int QueueCount(struct QUEUE *queue);

/*
 * Function: Enqueue
 * -----------------
 *
 * Add a new item to the queue.
 *
 * return: 0 on success
 * 	   -1 on failure
 */
int Enqueue(struct QUEUE *queue, void *item);

/*
 * Function: Dequeue
 * -----------------
 *
 * Get the next item from the queue.
 *
 * return: The next item in the queue.
 */
void *Dequeue(struct QUEUE *queue);


#endif // INCLUDE_QUEUE
