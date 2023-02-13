#ifndef POLYBIUS_H
#define POLYBIUS_H

// Definition of polybius.h
int pbEncode(const char* plaintext, char table[6][8]);
int pbDecode(const char* ciphertext, char table[6][8]);

#endif