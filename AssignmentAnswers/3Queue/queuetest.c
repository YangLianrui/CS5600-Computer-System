#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{	process_t process0 = {0, "ZERO", 0};
 	process_t process1 = {1, "ONE", 1};
 	process_t process2 = {2, "TWO", 999};
 	process_t process3 = {3, "THREE",8};
 	process_t process4 = {4, "FOUR", 9};
  	process_t process5 = {5, "FIVE", 4};
	process_t process6 = {6, "SIX", 10};
 	printf("Process %d Name is %s Priority %d.\n",process0.identifier, process0.name, process0.priority);
 	printf("Process %d Name is %s Priority %d.\n",process1.identifier, process1.name, process1.priority);
 	printf("Process %d Name is %s Priority %d.\n",process2.identifier, process2.name, process2.priority);
 	printf("Process %d Name is %s Priority %d.\n",process3.identifier, process3.name, process3.priority);
 	printf("Process %d Name is %s Priority %d.\n",process4.identifier, process4.name, process4.priority);
 	printf("Process %d Name is %s Priority %d.\n",process5.identifier, process5.name, process5.priority);
 	printf("Process %d Name is %s Priority %d.\n",process6.identifier, process6.name, process6.priority);

 	queue_t* queue = CreateQueue(100);
	if (IsFull(queue)){
		printf("Queue is full now.\n");
	}
 	else if (IsEmpty(queue)){
		printf("Queue is empty now.\n");
	}
 	else{
		printf("Queue is not empty and is not full.\n");
	}

  	printf("********Below is the test of enqueue, dequeue and qsize functions********\n");

 	enqueue(queue, &process0);
 	enqueue(queue, &process1);
 	enqueue(queue, &process2);
 	enqueue(queue, &process3);
 	enqueue(queue, &process4);
  	enqueue(queue, &process5);
   	enqueue(queue, &process6);

 	//process_t* ptr = dequeueProcess(queue);
	printf("Queue size is %d now.\n",qsize(queue));
    process_t* data0 = dequeue(queue);
 	process_t* data1 = dequeue(queue);
 	process_t* data2 = dequeue(queue);
	process_t* data3 = dequeue(queue);
 	printf("Queue size is %d now.\n",qsize(queue));
	process_t* data4 = dequeue(queue);
 	process_t* data5 = dequeue(queue);
 	process_t* data6 = dequeue(queue);
  	printf("Queue size is %d now.\n",qsize(queue));
	printf("********Below is the test of dequeueProcess function********\n");


 	enqueue(queue, &process0);
 	enqueue(queue, &process1);
 	enqueue(queue, &process2);
 	enqueue(queue, &process3);
 	enqueue(queue, &process4);
  	enqueue(queue, &process5);
   	enqueue(queue, &process6);
 	process_t* process_fetched = dequeueProcess(queue);
	printf("The process that has highest priority is id = %d, its priority is %d.\n",process_fetched->identifier,process_fetched->priority);
    return 0;
    
} 