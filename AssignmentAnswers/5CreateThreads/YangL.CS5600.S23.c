/* File: YangL.CS5600.S23.c
 * Author: Lianrui Yang
 * Course: CS 5600 NEU, BOSTON, MA
 * Date: Jan 30, 2023
 * Answer for question 1 2 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int global_array[1000];// The global array that can be written and read by both threads

/****************************BELOW: Question 1 Functions***********************************************/
void *worker(void *data) {
    char *name = (char*)data;
    for (int i = 0; i < 120; i++){
        usleep(50000);
        printf("Hi from thread name = %s\n", name);
    }
    printf("Thread %s done!\n", name);
    return NULL;
}



/****************************BELOW: Question 2 Functions and Structs***********************************************/
typedef struct // Construct a struct so that 2 arguments can be passed through pthread_create()
{
    char * text; // This text is to store "X"/"Y"
    unsigned long pid; // This pid is to sotre process id of a process
} input;

void *workerq2(void *arg) {
    input *inp = (input*)arg;
    inp->pid = (unsigned long)pthread_self(); // Assign process id of this process to pid
    for (int i = 0; i < 120; i++){
        usleep(50000);
        printf("Hi from thread name = %s\n", inp->text);
    }
    return NULL;
}
/*****************************BELOW: Question 3 Functions and Structs**********************************************/
typedef struct
{
    char * text;// Construct a struct so that multiple arguments can be used in function worker
                // Here, we only have 1 argument, so this struct is not quite necessary.
} inputq3;

void *write_workerq3(void *arg) {
    inputq3 *inp = (inputq3*)arg;
    for (int i = 0; i < 5; i++){
        usleep(40000);
        global_array[i] = i; // Write i to global_array[i]
        printf("Hi from thread name = %s, it wtites %d\n", inp->text, global_array[i]);
    }
    return NULL;
}

void *read_workerq3(void *arg) {
    inputq3 *inp = (inputq3*)arg;
    for (int i = 0; i < 5; i++){
        usleep(50000);
        printf("Hi from thread name = %s, it reads %d\n", inp->text, global_array[i]); // Print i from global_array[i]
    }
    return NULL;
}
/******************************************************************************************/


int main(void){
    // QUESTION 1 starts
    printf("Answer for Question 1 starts.\n");
    pthread_t th1, th2;
    pthread_create(&th1, NULL, worker, "X");
    pthread_create(&th2, NULL, worker, "Y");
    sleep(5);
    printf("Exiting from main program\n");

    sleep(10);//Wait 10 seconds to isolate different parts

    pthread_t th3, th4;
    pthread_create(&th3, NULL, worker, "X");
    pthread_create(&th4, NULL, worker, "Y");
    sleep(5);
    printf("exiting from main program\n");
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);

    sleep(10);//Wait 10 seconds to isolate different parts

    pthread_t th5, th6;
    pthread_create(&th5, NULL, worker, "X");// "X" is the argument that will be passed to worker in th1.
    pthread_create(&th6, NULL, worker, "Y");
    sleep(1);
    printf("====> Cancelling Thread Y!!\n");
    pthread_cancel(th5);
    usleep(100000);
    printf("====> Cancelling Thread X!!\n");
    pthread_cancel(th6);
    printf("exiting from main program\n");

    printf("Answer for Question 1 ends. Please wait 10s for Q2.\n");
    // QUESTION 1 ends
    sleep(10);


    // Question 2 starts
    printf("Answer for Question 2 starts.\n");
    input input1 = {"X", 0};
    input input2 = {"Y", 0};
    pthread_t th7, th8;
    pthread_create(&th7, NULL, workerq2, &input1);
    pthread_create(&th8, NULL, workerq2, &input2);
    sleep(1);
    printf("====> Cancelling Thread id = %lu!!\n", input1.pid);
    pthread_cancel(th7);
    usleep(100000);
    printf("====> Cancelling Thread id = %lu!\n", input2.pid);
    pthread_cancel(th8);
    printf("exiting from main program\n");
    printf("Answer for Question 2 ends. Please wait 10s for Q3.\n");
    // Question 2 ends
    sleep(10);


    // Question 3 starts
    printf("Answer for Question 3 starts.\n");
    inputq3 input9 = {"X"};
    inputq3 input10 = {"Y"};
    pthread_t th9, th10;
    pthread_create(&th9, NULL, write_workerq3, &input9);
    pthread_create(&th10, NULL, read_workerq3, &input10);
    sleep(1);
    printf("====> Cancelling Thread %s!!\n", input9.text);
    pthread_cancel(th9);
    usleep(100000);
    printf("====> Cancelling Thread %s!\n", input10.text);
    pthread_cancel(th10);
    printf("exiting from main program\n");
    printf("Answer ends");
    return 0;
}

/*
 * Answer for question 4:
 * From observation, generally, the action of the code of Question 3 is consistent.
 * It can firstly write 0 and then read 0. Next, it can write 1 and 1 is then being read by another thread.
 * That means the code can organize two threads and manage them write and read rhythmically.
 * However, there are some mistakes occasionally. When read_worker being executed firstly, consistency cannot be guaranteed.
 * If read is executed first, a number or some numbers may be skipped and cannot be printed.
 * By searching, peraps semaphore is a useful tool to solve this problem. Semaphore can guarantee only 1 threads access the
 * shared memory. So, there will be no conflicts or "step on".
 *
 */