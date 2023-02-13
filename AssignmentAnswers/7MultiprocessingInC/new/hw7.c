/*
 * File: hw7.c / Multiprocessing in C
 *
 * Lianrui Yang / CS5600 / Northeastern University
 * Spring 2023 / Feb 06, 2023
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "polybius.h"
#include <pthread.h>
#include <sys/wait.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_LINE 999999 // The maximum number of the whole text.



typedef struct Sentence{
    // Structure of a sentence. Note that this is not a copy of sentence, it is just the position of
    // a sentence. The sentence is stored in buf[MAX_LINE]
    char *ptr; // The pointer of the first character in a sentence
    int char_in_sentence; // The amount of characters within this sentence
} sentence;




int main(void){

    char buf[MAX_LINE]; /*Buffer*/
    FILE *fp;            /*File pointer*/
    int len;             /*num of characters within the text*/
    sentence sentences_a[100];
    if((fp = fopen("test.txt","r")) == NULL){
        perror("Fail to read.\n");
        exit (1) ;
    }
    while(fgets(buf,MAX_LINE,fp) != NULL){
        len = strlen(buf);
        //buf[len-1] = '\0';
    }

    //printf("%s      %d \n", buf, len);
    //printf("%c, %d\n", buf[len-1], len-1);

    int char_in_a_sentence = 0; // amount of characters in a sentence
    int sentence_itr = 0; // this num will iterate, it indicate the order of a sentence.
                          // In the end, it will indicate how many sentences are there in the text.

    // Special Cases
    if(len == 0){
        printf("Error: File does not contain any word.\n");
        return 0;
    }
    if(buf[len - 1] != '.' && buf[len - 1] != '!' && buf[len - 1] != '?'){
        // Check if the text ended with . ? !
        // If it does not ended with . ! ?, maybe the text not contains any sentence or the final sentence has error.
        printf("Error: the final sentence does not ended with '.' or '!' or '?'\n");
        printf("Or the text does not contain a sentence ended with '.' or '!' or '?'\n");
        return 0;
    }


    // Find ptr of each sentence and amount of characters in each sentence.
    for(int i = 0; i < len; i++){
        if (i == 0){ // For the first sentence
            sentences_a[sentence_itr].ptr = &buf[0];
            // Remember the address of the first char in text. This address is the start of the first sentence.
            char_in_a_sentence++; // Count the amount of character.
        }
        else if (buf[i] == '.' || buf[i] == '!' || buf[i] == '?'){ // If find .?!, the sentence ended.
            char_in_a_sentence++; // Count the final character of the sentence.
            sentences_a[sentence_itr].char_in_sentence = char_in_a_sentence; // Remember the amount of char in the sentence
            sentence_itr += 1; // Go to the next sentence
            //printf("Sentence itr = %d\n", sentence_itr);
            char_in_a_sentence = 0; // Clear the amount of character.
            i++;
            // Because after .?!, there will be a ' '. This is to skip ' ' after the prevous sentence.
            if (i+1 < len){ //We are going to the next sentence. If the next sentence exist
                sentences_a[sentence_itr].ptr = &buf[i+1];
                //Remember the address of the first char in the sentence.
            }
            else if (i+1>=len){ // i is larger than len, that means we have reached the end of the text.
                break; // go out of the for loop
            }
        }
        else{ // If in a sentence
            char_in_a_sentence++; // Count the amount of character.
        }
    }
    printf("totoly has %d sentences\n", sentence_itr);



    // Copy each sentences to separate strings.
    char* sentence_ptr[sentence_itr]; // Pointer of each sentence.
    for(int i = 0; i < sentence_itr; i++){
        char* one_sentence = sentences_a[i].ptr;
        sentence_ptr[i] = (char*) malloc(sentences_a[i].char_in_sentence * sizeof(char));
        memmove(sentence_ptr[i], one_sentence, sentences_a[i].char_in_sentence);
    }


    //Because pthread only support 1 argument, if we want to input 2 arguments, we need to Create threadsinput
    // pthread_input is a struct defined in "polybius.h"
    pthread_input pthreadInput[sentence_itr];
    for(int i = 0; i < sentence_itr; i++){
        pthreadInput[i].plaintext = sentence_ptr[i];// input sentence
        pthreadInput[i].output = (char*) malloc(2 * sentences_a[i].char_in_sentence * sizeof(char));// Output encrypted code memory space
        
    }


    pthread_t tid[sentence_itr]; // Create threads
    for(int i = 0; i < sentence_itr; i++){
        pthread_create(&tid[i], NULL, pbEncode, &pthreadInput[i]);
    }

    sleep(1);// Wait for 1s
    for(int i; i < sentence_itr; i++){
        printf("%s\n",pthreadInput[i].output);
    }



    mkdir("output",S_IRWXU); // Make a directory to store the coded sentences.
    for(int i = 0; i<sentence_itr; i++){
        FILE *fp = NULL;
        char filename[100];
        sprintf(filename, "./output/%d.txt", i);// Create a txt file
        fp = fopen(filename, "w+"); // Open the file
        fputs(pthreadInput[i].output, fp);// Write code into the file
        fclose(fp); // Close the file
    }


    for(int i=1;i <sentence_itr; i++){// Release dynamic allocated memory
        free(pthreadInput[i].output);
        free(sentence_ptr[i]);
    }


    return 0;

}


