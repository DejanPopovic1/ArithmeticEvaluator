#ifndef CONVERTTOPOSTFIX_H
#define CONVERTTOPOSTFIX_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "stackUtilities.h"
#include "mathUtilities.h"
#include "inputAndPrintingUtilities.h"

#define SIZE_OF_PRECEDENCE_ARRAY 8

struct precedence{
    char arithmeticOperator;
    int precedence;
};

int linearSearch(char, struct precedence *);
bool flushBufferedOperatorStack(char *, char *);
//char getTokenNONLIBRARY(char**);
void calculateArithmeticExpression(char *);
bool isFlushedOperatorLessThanOrEqualTopStackElement(char, struct CharStack);
bool isFirstLessThanOrEqualSecond(char, char);
void computeStack(struct CharStack *, struct NumStack *);

#endif
