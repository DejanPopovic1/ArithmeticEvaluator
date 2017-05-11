#ifndef CONVERTTOPOSTFIX_H
#define CONVERTTOPOSTFIX_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "stackUtilities.h"
#include "mathUtilities.h"
#include "inputAndPrintingUtilities.h"

#define SIZE_OF_PRECEDENCE_ARRAY 7

enum PRECEDENCE_PRIORITY{
    ADDITION = 1,
    SUBTRACTION = 1,
    MULTIPLICATION = 2,
    DIVISION = 2,
    EXPONENTIATION = 3,
    BRACKETS = 4
};

struct precedence{
    char arithmeticOperator;
    int precedence;
};

int linearSearch(char, struct precedence *);
bool flushBufferedOperatorStack(char *, char *);
char getTokenNONLIBRARY(char**);
void calculateArithmeticExpression(char *);
bool isFlushedOperatorLessThanOrEqualTopStackElement(char, struct CharStack);
bool isFirstLessThanOrEqualSecond(char, char);
void computeStack(struct CharStack *, struct NumStack *);

#endif
