#ifndef STACKUTILITIES_H
#define STACKUTILITIES_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 200
#define STACK_EMPTY E

struct CharStack{
    char stackValues[MAX_STACK_SIZE];
    int stackPointer;
};

struct NumStack{
    double stackValues[MAX_STACK_SIZE];
    int stackPointer;
};

void pushChar(struct CharStack *, char);
char popChar(struct CharStack *);
char peekChar(struct CharStack);
void pushNum(struct NumStack *, double);
double popNum(struct NumStack *);

#endif
