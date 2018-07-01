/*
* testQueue.c
* author:
*     Kyle Seidenthal
*
* date: 26-06-18
* description: Tests for the queue library
*/

#define TESTNRM "\x1B[0m"
#define TESTPASS "\x1B[32m"
#define TESTFAIL "\x1B[31m"

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "debug.h"

void testCreateQueue(){
	struct QUEUE *queue;
	struct QUEUE *queue2;	

	queue = QueueCreate();
	
	assert(queue != NULL && "Error creating first queue\n");

	queue2 = QueueCreate();

	assert(queue2 != NULL && "Error creating second queue\n");

}

void testEnqueue(){
	struct QUEUE *queue;

	int item1 = 1;
	int item2 = 2;
	int item3 = 3;
	int item4 = 4;
	int item5 = 5;
	int itemArray [15];
	int finalItem = 100;

	
	int i;
	for(i = 0; i < 15; i++){
		itemArray[i] = i;
	}
	
	queue = QueueCreate();
	
	assert(Enqueue(queue, &item1) == 0  && "Error adding first item to queue.");
	
	assert(*(int *)queue->list->head->item == item1 && "The head of the queue is not the first item.");

	assert(*(int *)queue->list->tail->item == item1 && "The tail of the queue is not the first item.");

	assert(Enqueue(queue, &item2) == 0 && "Error adding second item to queue.");
	
	assert(*(int *)queue->list->tail->item == item2 && "The tail of the queue is not the second item.");

	assert(*(int *)queue->list->head->item == item1 && "The head of the queue is not the first");

	assert(Enqueue(queue, &item3) == 0 && "Error adding third item to queue.");

	assert(*(int *)queue->list->head->item == item1 && "The head of the queue is not the first item");
	
	assert(*(int *)queue->list->tail->item == item3 && *(int *)queue->list->tail->item != item2 && "The tail of the queue is not the third item");

	assert(Enqueue(queue, &item4) == 0 && "Error adding fourth item to queue");
	
	assert(*(int *)queue->list->head->item == item1 && "The head of the queue is not the first item");
	
	assert(*(int *)queue->list->tail->item == item4 && *(int *)queue->list->tail->item != item3 && "The tail of the queue is not the fourth item");

	assert(Enqueue(queue, &item5) == 0 && "Error adding fifth item to queue");
	
	assert(*(int *)queue->list->head->item == item1 && "The head of the queue is not the first item");
	
	assert(*(int *)queue->list->tail->item == item5 && *(int *)queue->list->tail->item != item4 && "The tail of the queue is not the fifth item");

	for(i = 0; i < 15; i++){
		Enqueue(queue, &itemArray[i]);
	}

	assert(*(int *)queue->list->tail->item == itemArray[14] && "The tail is not the expected item");

	// Should not be able to add any more items
	assert(Enqueue(queue, &finalItem) != 0 && "Enqueued an item to a full queue");


	

}

void testDequeue(){
	
	struct QUEUE *queue;

	int item1 = 1;
	int item2 = 2;
	int item3 = 3;

	void* nextItem;

	queue = QueueCreate();

	Enqueue(queue, &item1);
	Enqueue(queue, &item2);
	Enqueue(queue, &item3);

	nextItem = Dequeue(queue);

	assert(*(int*)nextItem == item1 && "The dequeued item is not the first item");
	assert(*(int*)queue->list->head->item == item2 && "The head of the queue is not the second item");

	nextItem = Dequeue(queue);
	
	assert(*(int*)nextItem == item2 && "The dequeued item is not the second item");
	assert(*(int*)queue->list->head->item == item3 && "The head of the queue is not the third item");

	nextItem = Dequeue(queue);
	
	assert(*(int*)nextItem == item3 && "The dequeued item is not the third item");

	// Queue is empty, so the next item should be null
	nextItem = Dequeue(queue);

	assert(nextItem == NULL && "The dequeued item is not null");


}

void testQueueCount(){
	struct QUEUE *queue;

	int item1 = 1;
	int item2 = 2;
	int item3 = 3;


	int count;

	queue = QueueCreate();

	count = QueueCount(queue);

	assert(count == 0 && "The queue is not empty as expected");

	Enqueue(queue, &item1);

	count = QueueCount(queue);

	assert(count == 1 && "The queue does not have 1 element as expected");

	Enqueue(queue, &item2);

	count = QueueCount(queue);

	assert(count == 2 && "The queue does not have 2 elements as expected");

	Enqueue(queue, &item3);

	count = QueueCount(queue);

	assert(count == 3 && "The queue does not have 3 elements as expected");

	Dequeue(queue);

	count = QueueCount(queue);

	assert(count == 2 && "The queue does not have 2 elements as expected");

	Dequeue(queue);

	count = QueueCount(queue);

	assert(count == 1 && "The queue does not have 1 element as expected");

	Dequeue(queue);

	count = QueueCount(queue);

	assert(count == 0 && "The queue does not have 0 elements as expected");
	
}

int main(){

	printf("============= TESTS BEGIN ===========================\n\n");

	testCreateQueue();
	testEnqueue();
	testQueueCount();
	testDequeue();

	printf("\n%s============= ALL TESTS PASSED ===================%s\n", TESTPASS, TESTNRM);	
	return 0;
}
