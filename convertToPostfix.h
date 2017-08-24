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
#define SIZE_OF_OPERATORS_BEFORE_OPENING_ABSOLUTE_VALUE_ARRAY 6
#define SIZE_OF_OPERATORS_BEFORE_CLOSING_ABSOLUTE_VALUE_ARRAY 1
#define START_OF_STRING "S"
#define OPEN_ABSOLUTE_VALUE "//"
#define CLOSED_ABSOLUTE_VALUE "\\"

struct precedence{
    char arithmeticOperator;
    int precedence;
};

bool isFirstLessThanOrEqualSecond(char, char);
int linearSearch(char, struct precedence *);
bool isFlushedOperatorLessThanOrEqualTopStackElement(char, struct CharStack);
bool flushBufferedOperatorStack(char *, char *);
void handleNumber(char *, char *, char *);
void handleOpenParenthesis(char *, char *, char *);
void handleClosedParenthesis();
void handleFactorial(char *);
void handleOperator(char *, char *);
void handleOpenAbsoluteValue(char *);
void handleClosedAbsoluteValue(char *);
void calculateArithmeticExpression(char *);
void computeStack(struct CharStack *, struct NumStack *);

#endif
