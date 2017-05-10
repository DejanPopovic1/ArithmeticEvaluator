#include "tokenizer.h"

static char peekString(char *stringToPeek){
    return *stringToPeek;
}

char *getToken(char **unparsedInput){
    char initialPeekedCharacter = peekString(*unparsedInput);
    char *token = malloc(MAX_TOKEN_LENGTH * sizeof(char));
    int i;
    if(isdigit(initialPeekedCharacter)) {
        *token = initialPeekedCharacter;
        (*unparsedInput)++;
        for(i = 1; isdigit(peekString(*unparsedInput)); i++) {
            *(token + i) = peekString(*unparsedInput);
            (*unparsedInput)++;
        }
        *(token + i) = '\0';
        return token;
    }
    else if (initialPeekedCharacter == '(' || initialPeekedCharacter == ')' || initialPeekedCharacter == '+' || initialPeekedCharacter == '\0' ) {
        *token = initialPeekedCharacter;
        *(token + 1) = '\0';
        return token;
    }
    else {
        fprintf(stderr, "Invalid input character(s)\n");
        exit(-1);
    }
}
