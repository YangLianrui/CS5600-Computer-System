/* File: YangL.CS5600.S23_3_1.c
 * Author: Lianrui Yang
 * Course: CS 5600 NEU, BOSTON, MA
 * Date: Jan 30, 2023
 * Answer for question 3
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int global_array[1000];// The global array that can be written and read by both threads

typedef struct
{
    char * text;// Construct a struct so that multiple arguments can be used in function worker
                // Here, we only have 1 argument, so this struct is not quite necessary.
} inputq3;

void *write_workerq3(void *arg) {
    inputq3 *inp = (inputq3*)arg;
    for (int i = 0; i < 5; i++){
        usleep(50000);
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

int main(void)
{
    inputq3 input1 = {"X"};
    inputq3 input2 = {"Y"};
    int pid1, pid2;
    pthread_t th1, th2;
    pthread_create(&th1, NULL, write_workerq3, &input1);
    pthread_create(&th2, NULL, read_workerq3, &input2);
    sleep(1);
    printf("====> Cancelling Thread %s!!\n", input1.text);
    pthread_cancel(th2);
    usleep(100000);
    printf("====> Cancelling Thread %s!\n", input2.text);
    pthread_cancel(th1);
    printf("exiting from main program\n");
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