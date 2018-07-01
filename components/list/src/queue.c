/*
* queue.c
* author:
*     Kyle Seidenthal
*
* date: 26-06-18
* description: Implementation of queue interface on a list library
*/

#include "list.h"
#include "queue.h"
#include "debug.h"
#include <stdlib.h>

struct QUEUE *QueueCreate(){
	QUEUE *queue = malloc(sizeof(QUEUE));

	LIST *list = ListCreate();

	queue->list = list;

	return queue;
}

int QueueCount(struct QUEUE *queue){
	return ListCount(queue->list);
}

int Enqueue(struct QUEUE *queue, void* item){
	int ret = ListAppend(queue->list, item);
	
	DEBUG_LOG("%s %d\n", "Return value of list append:", ret);

	return ret;
}

void *Dequeue(struct QUEUE *queue){
	ListFirst(queue->list);
	return ListRemove(queue->list);
}
