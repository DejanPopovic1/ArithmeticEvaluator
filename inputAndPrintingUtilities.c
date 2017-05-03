#include <stdio.h>
#include <stdlib.h>
#include "arithmeticEvaluator.h"
#define MEMORY_ALLOCATE 200

const char* withinArraySeperator = "   ";
const char* interArraySeperator = "\n";

void printCharacterArray(char* arrayToBePrinted){
    for(int i = 0; arrayToBePrinted[i] != '\0'; i++) {
        printf("%c%s", arrayToBePrinted[i], withinArraySeperator);
    }
    printf("%s", interArraySeperator);
}

void printDoubleArray(double* arrayToBePrinted, int sizeOfArray){
    for(int i = 0; i < sizeOfArray; i++) {
        printf("%f%s", arrayToBePrinted[i], withinArraySeperator);
    }
    printf("%s", interArraySeperator);
}

void printCharacterStack(struct CharStack stackToBePrinted){
    int sizeOfStack = stackToBePrinted.stackPointer;
    if (sizeOfStack == 0) {
        printf("Stack Empty");
    }
    char characterArrayToBePrinted[MAX_STACK_SIZE];
    int i;
    for(i = 0; i < sizeOfStack; i++) {
        characterArrayToBePrinted[i] = stackToBePrinted.stackValues[i];
    }
    characterArrayToBePrinted[i] = '\0';
    printCharacterArray(characterArrayToBePrinted);
}

void printDoubleStack(struct NumStack stackToBePrinted){
    int sizeOfStack = stackToBePrinted.stackPointer;
    double numberArrayToBePrinted[MAX_STACK_SIZE];
    int i;
    for(i = 0; i < sizeOfStack; i++) {
        numberArrayToBePrinted[i] = stackToBePrinted.stackValues[i];
    }
    printDoubleArray(numberArrayToBePrinted, sizeOfStack);
}

char* getKeyboardInput(void){
    int i;
    char inputCharacter;
    char* input = malloc(sizeof(char) * MEMORY_ALLOCATE); //Remember to free memory in the caller
    if (input == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(-1);
    }
    for(i = 0; i < MEMORY_ALLOCATE; i++) {
        inputCharacter = getchar();
        if(inputCharacter == '\n'){
            break;
        }
        input[i] = inputCharacter;
    }
    input[i] = '\0';
    return input;
}
