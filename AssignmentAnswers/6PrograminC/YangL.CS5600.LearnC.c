/*
* YangL.CS5600LearningC.c / Program in C
*
* Lianrui Yang / CS5600 / Northeastern University
* Spring 2023 / Feb 02, 2023
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

float mpg2kml(float input){ // Takes miles per gallon as an argument and returns the equivalent kilometers per liter
    float kml = 0.42517006802721 * input;
    return kml;

}

float mpg2lphm(float input){ // takes miles per gallon as an argument and returns the equivalent number of liter per 100 kilometers.
    float lphm = 235.2 * input;
    return lphm;
}

float kml2mpg(float input){ //takes the kilometers per liter and returns miles per gallon.
    float mpg = 2.352 * input;
    return mpg;
}

int main(void){
    float input = 10; // Test case 1
    //printf("Enter miles per gallon: \n");
    //scanf("%f", &input);
    if (input < 0){
        printf("Input cannot less than 0!\n");
        return 0;
    }
    else{}
    printf("Kilometers per liter: %f\n", mpg2kml(input));
    printf("Number of liter per 100 kilometers: %f\n", mpg2lphm(input));

    float input1 = 10; // Test case 2
    //printf("Enter kilometers per liter: \n");
    //scanf("%f", &input1);
    if (input1 < 0){
        printf("Input cannot less than 0!\n");
        return 0;
    }
    printf("Miles per gallon: %f\n", kml2mpg(input1));
    return 0;
}


