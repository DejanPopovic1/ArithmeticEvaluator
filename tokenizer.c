#include "tokenizer.h"

char peekString(char *stringToPeek){
    return *stringToPeek;
}

char *getToken(char **unparsedInput, struct precedence precedenceArray[]){
    char initialPeekedCharacter = peekString(*unparsedInput);
    char *token = malloc(MAX_TOKEN_LENGTH * sizeof(char));
    int i;
    if(isdigit(initialPeekedCharacter)) {//The token is a number
        *token = initialPeekedCharacter;
        (*unparsedInput)++;
        for(i = 1; isdigit(peekString(*unparsedInput)) || peekString(*unparsedInput) == '.'; i++) {
            *(token + i) = peekString(*unparsedInput);
            (*unparsedInput)++;
        }
        *(token + i) = '\0';
        return token;
    }
    else if (linearSearch(initialPeekedCharacter, precedenceArray) >= 0) {//The token is an operator contained in the operator array
        *token = initialPeekedCharacter;
        *(token + 1) = '\0';
        (*unparsedInput)++;
        return token;
    }
    else if(initialPeekedCharacter == '\0') {
        *token = initialPeekedCharacter;
        return token;
    }
    else {
        printf("%s\n", token);
        fprintf(stderr, "Invalid input character(s)\n");
        exit(-1);
    }
}
