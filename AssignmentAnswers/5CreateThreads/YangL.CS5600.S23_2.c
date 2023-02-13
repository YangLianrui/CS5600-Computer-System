/* File: YangL.CS5600.S23_2_1.c
 * Author: Lianrui Yang
 * Course: CS 5600 NEU, BOSTON, MA
 * Date: Jan 30, 2023
 * Answer for question 2
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
typedef struct // Construct a struct so that 2 arguments can be passed through pthread_create()
{
    char * text; // This text is to store "X"/"Y"
    unsigned long pid; // This pid is to sotre process id of a process
} input;

void *worker(void *arg) {
    input *inp = (input*)arg;
    inp->pid = (unsigned long)pthread_self(); // Assign process id of this process to pid
    for (int i = 0; i < 120; i++){
        usleep(50000);
        printf("Hi from thread name = %s\n", inp->text);
    }
    return NULL;
}

int main(void)
{
    input input1 = {"X", 0};
    input input2 = {"Y", 0};
    int pid1, pid2;
    pthread_t th1, th2;
    pthread_create(&th1, NULL, worker, &input1);
    pthread_create(&th2, NULL, worker, &input2);
    sleep(1);
    printf("====> Cancelling Thread %lu!!\n", input1.pid);
    pthread_cancel(th2);
    usleep(100000);
    printf("====> Cancelling Thread %lu!\n", input2.pid);
    pthread_cancel(th1);
    printf("exiting from main program\n");
    return 0;
}










