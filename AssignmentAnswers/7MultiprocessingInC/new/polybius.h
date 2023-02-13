#ifndef POLYBIUS_H
#define POLYBIUS_H


typedef struct Pthread_input{
    const char* plaintext; // The amount of characters within this sentence
    char* output;
} pthread_input;

// Definition of polybius.h
void* pbEncode(void* input);
int pbDecode(const char* ciphertext, char table[6][8]);

#endif