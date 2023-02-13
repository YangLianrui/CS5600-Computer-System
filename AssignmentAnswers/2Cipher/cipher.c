#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include "polybius.h"

 /* Define Polybius Square
     *    0 1 2 3 4 5 6 7
     * 0  A B C D E F G H
     * 1  I J K L M N O P
     * 2  Q R S T U V W X
     * 3  Y Z 1 2 3 4 5 6
     * 4  7 8 9 0 . , ! ?
     * 5    @ # $ % & * ;
     *
     * e.g.
     * 'A' will be encoded as 00, 'B' as 01, '#' as 52
     * a blank space will be encoded as 50
     */

int main(int argc, char* argv[]) {
    const char table[6][8] = {
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
        {'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
        {'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
        {'Y', 'Z', '1', '2', '3', '4', '5', '6'},
        {'7', '8', '9', '0', '.', ',', '!', '?'},
        {' ', '@', '#', '$', '%', '&', '*', ';'}
    };


    // check the validation of uesr input
    if(argc != 3) { //   ./a "dsfkjaskNLk lksdafk"
        printf("For encode text please use: %s -e <text>\nFor decode text please use: %s -d <text>\n", argv[0],argv[0]);
        return 1;
    }
    else if(strcmp(argv[1], "-e") != 0 && strcmp(argv[1], "-d") != 0) {// If the second arugument is not -e or -d
        printf("Invalid option: %s\nPlease try again.\n", argv[1]);
        return 1;
    }
    // Encode edition
    else if(strcmp(argv[1], "-e") == 0) {
        char* string = argv[2];
        pbEncode(string, table);
        return 0;
    }
    /// Decode edition
    else if(strcmp(argv[1], "-d") == 0) {
        char* string = argv[2];
        pbDecode(string, table);
        return 0;
    }
    else{
        printf("Error, please check your input!");
        return 1;
    }
}