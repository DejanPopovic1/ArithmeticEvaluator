#include "tokenizer.h"

char peekString(char *stringToPeek){
    return *stringToPeek;
}

char *getTokenNONLIBRARY(char** infix) {
    char *returnToken = malloc(2 * sizeof(char));
    *returnToken = **infix;
    *(returnToken + 1) = '\0';
    (*infix)++;
    return returnToken;
}

char *getToken(char **unparsedInput, struct precedence precedenceArray[]){
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
    else if (linearSearch(initialPeekedCharacter, precedenceArray) >= 0) {
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
        fprintf(stderr, "Invalid input character(s)\n");
        exit(-1);
    }
}
