#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include "convertToPostfix.h"

#define MAX_TOKEN_LENGTH 100

char *getTokenNONLIBRARY(char**);
char peekString(char *);
char *getToken(char **, struct precedence[]);

#endif
