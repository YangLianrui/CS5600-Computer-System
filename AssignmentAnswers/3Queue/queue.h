#ifndef QUEUE_H
#define QUEUE_H

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

queue_t* CreateQueue(int MaxSize );
int IsFull(queue_t* queue);
int IsEmpty(queue_t* queue);
void DestroyQueue(queue_t* queue);
void enqueue(queue_t* queue, process_t* element);
int qsize(queue_t* queue);
void* dequeue(queue_t* queue);
process_t* dequeueProcess(queue_t* queue);

#endif