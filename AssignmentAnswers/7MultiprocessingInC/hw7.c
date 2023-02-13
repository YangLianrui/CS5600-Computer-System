/*
* YangL.CS5600LearningC.c / Multiprocessing in C
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


#define MAX_LINE 999999

typedef struct Sentence{
    char *ptr; // The pointer of the first character in a sentence
    int char_in_sentence; // The amount of characters within this sentence
} sentence;

int main(void){

    const char table[6][8] = { //Define cipher table
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
        {'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
        {'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
        {'Y', 'Z', '1', '2', '3', '4', '5', '6'},
        {'7', '8', '9', '0', '.', ',', '!', '?'},
        {' ', '@', '#', '$', '%', '&', '*', ';'}
    };



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
        //buf[len-1] = '\0';  /*去掉换行符*/
    }

    //printf("%s      %d \n", buf, len);
    //printf("%c, %d\n", buf[len-1], len-1);

    int char_in_a_sentence = 0;
    int sentence_itr = 0;

    // Special cases
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

    // Find ptr of each sentence and num_character of each sentence.
    for(int i = 0; i < len; i++){
        if (i == 0){
            sentences_a[sentence_itr].ptr = &buf[0];
            //printf("This is sentence %d, its first char is %c\n", sentence_itr, *(sentences_a[sentence_itr].ptr));
            //printf("Sentence itr = %d\n", sentence_itr);
            char_in_a_sentence++;
        }
        else if (buf[i] == '.' || buf[i] == '!' || buf[i] == '?'){
            char_in_a_sentence++;
            sentences_a[sentence_itr].char_in_sentence = char_in_a_sentence;
            //printf("This is sentence %d, it has %d char\n",sentence_itr, sentences_a[sentence_itr].char_in_sentence);
            sentence_itr += 1;
            //printf("Sentence itr = %d\n", sentence_itr);
            char_in_a_sentence = 0;
            i++; // This is to skip ' ' after a sentence.
            if (i+1 < len){
                sentences_a[sentence_itr].ptr = &buf[i+1];
                //printf("This is sentence %d, its first char is %c\n", sentence_itr, *(sentences_a[sentence_itr].ptr));
            }
            else if (i+1>=len){
                break;
            }
        }
        else{
            char_in_a_sentence++;
        }
    }
    printf("totoly has %d sentences\n", sentence_itr);



    // Copy each sentences to separate strings.
    char* sentence_ptr[sentence_itr];
    for(int i = 0; i < sentence_itr; i++){
        char* one_sentence = sentences_a[i].ptr;
        sentence_ptr[i] = (char*) malloc(sentences_a[i].char_in_sentence * sizeof(char));
        memmove(sentence_ptr[i], one_sentence, sentences_a[i].char_in_sentence);
    }

    char* encoded_sentence[sentence_itr];
    for(int i = 0; i < sentence_itr; i++){
        encoded_sentence[i] = (char*) malloc(2 * sentences_a[i].char_in_sentence * sizeof(char));
    }


    for(int i = 0; i<sentence_itr; i++){
        
        int rc = fork();
        if(rc < 0){
            printf("Error: Cannot create child process.\n");
            return 0;
        }
        else if(rc == 0){
            pbEncode(sentence_ptr[i], table, encoded_sentence[i]);
        }
        else {

            FILE *fp = NULL;
            char filename[100];
            sprintf(filename, "output%d.txt", i);
            fp = fopen(filename, "w+");
            printf("%s\n", encoded_sentence[i]);
            fputs(encoded_sentence[i], fp);
            fclose(fp);
        }
    }
    /*
    pthread_t tid[sentence_itr]; // Create threads
    for(int i; i < sentence_itr; i++){
        ret = pthread_create(&tid[i], NULL, pbEncode);
    }

    fclose(fp);
     */
    return 0;

}


