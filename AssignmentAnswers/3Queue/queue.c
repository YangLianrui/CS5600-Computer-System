#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
/*
typedef struct Process_t {//Define process structure, it can be declared by "process_t p"
    int identifier;
    char* name;
    int priority;
}process_t;

typedef struct Queue_t {
	void* data;
	int Front, Rear;//Pointer to front q node and reat q node
	int MaxSize;//The maximal size of a queue
}queue_t;
*/
queue_t* CreateQueue(int MaxSize ) {
    queue_t* queue = (queue_t*)malloc(sizeof(struct queue_t*));
    queue->data = (process_t*)malloc((MaxSize) * sizeof(process_t*));
    queue->Front = queue->Rear = 0;
    queue->MaxSize = MaxSize;
	printf("A queue is created.\n");
    return queue;
}

int IsFull(queue_t* queue) {
    return ((queue->Rear+1)%queue->MaxSize == queue->Front);
}

int IsEmpty(queue_t* queue){
    return (queue->Front == queue->Rear);
}

void DestroyQueue(queue_t* queue) {
    if (queue) {
        if (queue->data) {
            free(queue->data);
        }
        free(queue);
    }
    printf("A queue is destroied.\n");
}

void enqueue(queue_t* queue, process_t* element) {
	if (IsFull(queue)) {
        printf("Queue is full and the element cannot be enqueued.\n");
		return;
    }
    *((process_t**)(queue->data) + queue->Rear) = element;
    printf("Element id %d is enqueued.\n", (*((process_t**)queue->data+queue->Rear))->identifier);
    queue->Rear = (queue->Rear + 1) % queue->MaxSize;
	//printf("queue->Front is %d\n", queue->Front);
	//printf("queue->Rear is %d\n", queue->Rear);

}
int qsize(queue_t* queue) {
	if (IsEmpty(queue)) {
        printf("Error, the queue is empty and can cannot be dequeued!!!.\n");
		return 0;
    }
	return (queue->Rear) - (queue->Front);
}

void* dequeue(queue_t* queue){
	if (IsEmpty(queue)) {
        printf("Error, the queue is empty and can cannot be dequeued.\n");
		return NULL;//Return NULL as the pointer of data
    }
    else {
		//printf("Before Dequeue, node %d is current front.\n",queue->Front);
		process_t** dataptr = (process_t**)queue->data + queue->Front;//Save current ptr of front data
		queue->Front = (queue->Front + 1) % queue->MaxSize;// Change current ptr to the next
		//printf("After Dequeue, node %d is current front.\n",queue->Front);
		printf("Element %d has been dequeued.\n", (*dataptr)->identifier);//Print the fetched data->identifier
		return *dataptr;
	}
}


process_t* dequeueProcess(queue_t* queue){
    if (IsEmpty(queue)) {
        printf("Error, the queue is empty and can cannot be dequeued!!!.\n");
		return NULL;
    }
    int maxPriority = 0;
    int i_max_prio;
	process_t* max_process = NULL;
	for (int i = queue->Front; i < (queue->Rear); i++){//Find the element that has the highest priority
		process_t** ptr = (process_t**)queue->data + i;//current ptr of ith data
		if ((*ptr)->priority >= maxPriority) {
			maxPriority = (*ptr)->priority;
            i_max_prio = i;
			max_process = *ptr;// Store the data/process that has the highest priority
		}
	}
	//printf("The highest Priority is %d, its id is %d\n", maxPriority, (max_process)->identifier);
	for (int i = queue->Front; i < (queue->Rear); i++) {//Rmove queue node that has the highest priority
        if (i > i_max_prio) {
            *((process_t**)(queue->data) + i - 1) = *((process_t**)(queue->data) + i);
		}
	}
	queue->Rear = queue->Rear - 1;
	for(int i = queue->Front; i < (queue->Rear); i++){
		printf("Process id = %d is still remain after removing id = %d\n", (*((process_t**)(queue->data) + i))->identifier, (max_process)->identifier);
	}
    return max_process;
}
