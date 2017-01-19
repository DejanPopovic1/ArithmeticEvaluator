#include <stdio.h>
#define MEMORY_ALLOCATE 20

const char* withinArraySeperator = "   ";
const char* betweenArraySeperator = "\n";

void printCharacterArray(char* arrayToBePrinted){
    for(char i = 0; arrayToBePrinted[i] != '\0'; i++){
        printf("%c%s", arrayToBePrinted[i], withinArraySeperator);
    }
}

char* getKeyboardInput(void){
    char* input = malloc(sizeof(char) * MEMORY_ALLOCATE);
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
