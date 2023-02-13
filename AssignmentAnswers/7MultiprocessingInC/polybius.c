#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include "polybius.h"

#define ROW 6
#define COL 8


// Encode the plaintext using the table
// In table[6][8], I defined a Polybius Square Table to map
// character/symbol/number to a two digits code. Some special symbols including
// ? ! @ # $ % & * have been included. For encode function, if the input
// message contains an unknown symbol, the symbol will be mapped as 00.
// In some cases, if we use to many given symbols, a Linux system warning
// may happen. For example: -bash: !@#: event not found
int pbEncode(const char* plaintext, char table[ROW][COL], char* output) {
    int i;
    int row;
    int col;
    int j = 0;
    printf("The original message is: %s\n",plaintext);
    printf("The encoded message is: ");
    for (i = 0; i < (int)strlen(plaintext); i++) {
        for (row = 0; row < ROW; row++) {
            for (col = 0; col < COL; col++) {
                if (table[row][col] == toupper(plaintext[i])) {
                    // Modify lower cases of letter to upper cases
                    //printf("%d%d", row, col);// print ciphertext of a single character
                    output[j] = row + '0';
                    j++;
                    output[j] = col + '0';
                    j++;
                }
            }
        }
    }
    printf("\n");
    return 0;
}



// Decode the ciphertext using the table
// For codes that are not included in table, such as 99, 79,
// The pbDecode will decode it as a randam character/symbol/number.
int pbDecode(const char* ciphertext, char table[ROW][COL]) {
    int i;
    int row;
    int col;
	printf("The decoded message is: ");
    for (i = 0; i < (int)strlen(ciphertext); i += 2) {
		row = ciphertext[i] - '0';// Convert char to int
		col = ciphertext[i + 1] - '0';
		printf("%c", table[row][col]);
    }
	printf("\n");
    return 0;
}
