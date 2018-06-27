/*
* queue.c
* author:
*     Kyle Seidenthal
*
* date: 26-06-18
* description: Implementation of queue interface on a list library
*/

#include "queue.h"
#include "debug.h"


struct QUEUE *QueueCreate(){
	QUEUE *queue;

	LIST *list = ListCreate();

	queue->list = list;

	return queue;
}

int QueueCount(struct QUEUE *queue){
	return ListCount(queue->list);
}

int Enqueue(struct QUEUE *queue, void* item){
	return ListAppend(queue->list, item);
}

void *Dequeue(struct QUEUE *queue){
	ListFirst(queue->list);
	return ListRemove(queue->list);
}
