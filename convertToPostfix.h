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

#define SIZE_OF_PRECEDENCE_ARRAY 9
#define START_OF_STRING "S"
#define OPEN_ABSOLUTE_VALUE "//"
#define CLOSED_ABSOLUTE_VALUE "\\"

struct precedence{
    char arithmeticOperator;
    int precedence;
};

int linearSearch(char, struct precedence *);
bool flushBufferedOperatorStack(char *, char *);
void calculateArithmeticExpression(char *);
bool isFlushedOperatorLessThanOrEqualTopStackElement(char, struct CharStack);
bool isFirstLessThanOrEqualSecond(char, char);
void computeStack(struct CharStack *, struct NumStack *);

#endif
