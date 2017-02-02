#include <stdio.h>
#include "arithmeticEvaluator.h"
#define MEMORY_ALLOCATE 20

const char* withinArraySeperator = "   ";

void printCharacterArray(char* arrayToBePrinted){
    for(int i = 0; arrayToBePrinted[i] != '\0'; i++)
    {
        printf("%c%s", arrayToBePrinted[i], withinArraySeperator);
    }
}

void printDoubleArray(double* arrayToBePrinted, int sizeOfArray){
    for(int i = 0; arrayToBePrinted[i] < 3; i++)
    {
        printf("%d%s", arrayToBePrinted[i], withinArraySeperator);
    }
}

void printCharacterStack(struct CharStack stackToBePrinted){
    int sizeOfStack = stackToBePrinted.stackPointer;
    char characterArrayToBePrinted[MAX_STACK_SIZE];
    int i = 0;
    for(i; i < sizeOfStack; i++)
    {
        characterArrayToBePrinted[i] = stackToBePrinted.stackValue[i];
    }
    characterArrayToBePrinted[i] = '\0';
    printCharacterArray(characterArrayToBePrinted);
}

void printDoubleStack(struct CharStack stackToBePrinted){
    int sizeOfStack = stackToBePrinted.stackPointer;
    double characterArrayToBePrinted[MAX_STACK_SIZE];
    int i = 0;
    for(i; i < sizeOfStack; i++)
    {
        characterArrayToBePrinted[i] = stackToBePrinted.stackValue[i];
    }
    printCharacterArray(characterArrayToBePrinted);
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
