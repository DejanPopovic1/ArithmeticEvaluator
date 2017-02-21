#include <stdio.h>
#include <stdlib.h>
#include "arithmeticEvaluator.h"
#define MEMORY_ALLOCATE 20

const char* withinArraySeperator = "   ";
const char* interArraySeperator = "\n";

void printCharacterArray(char* arrayToBePrinted){
    for(int i = 0; arrayToBePrinted[i] != '\0'; i++)
    {
        printf("%c%s", arrayToBePrinted[i], withinArraySeperator);
    }
    printf("%s", interArraySeperator);
}

void printDoubleArray(double* arrayToBePrinted, int sizeOfArray){
    for(int i = 0; i < sizeOfArray; i++)
    {
        printf("%f%s", arrayToBePrinted[i], withinArraySeperator);
    }
    printf("%s", interArraySeperator);
}

void printCharacterStack(struct CharStack stackToBePrinted){
    int sizeOfStack = stackToBePrinted.stackPointer;
    char characterArrayToBePrinted[MAX_STACK_SIZE];
    int i = 0;
    for(i; i < sizeOfStack; i++)
    {
        characterArrayToBePrinted[i] = stackToBePrinted.stackValues[i];
    }
    characterArrayToBePrinted[i] = '\0';
    printCharacterArray(characterArrayToBePrinted);
}

void printDoubleStack(struct NumStack stackToBePrinted){
    int sizeOfStack = stackToBePrinted.stackPointer;
    double numberArrayToBePrinted[MAX_STACK_SIZE];
    int i = 0;
    for(i; i < sizeOfStack; i++)
    {
        numberArrayToBePrinted[i] = stackToBePrinted.stackValues[i];
    }
    printDoubleArray(numberArrayToBePrinted, sizeOfStack);
}

char* getKeyboardInput(void){
    char* input = malloc(sizeof(char) * MEMORY_ALLOCATE); //Still have to free memory
    if (input == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(-1);
    }
    int i;
    char inputCharacter;
    for(i = 0; i < MEMORY_ALLOCATE; i++){
        inputCharacter = getchar();
        if(inputCharacter == '\n'){
            break;
        }
        input[i] = inputCharacter;
    }
    input[i] = '\0';
    return input;
}

char getToken(char **inputString){
    char returnCharacter = **inputString;
    *inputString = *inputString + 1;    //Still have to free memory
    return returnCharacter;
}

char peekToken(char *inputString){
    return inputString[0];
}
