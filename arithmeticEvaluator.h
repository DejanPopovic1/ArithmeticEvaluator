#ifndef ARITHMETICEVALUATOR_H
#define ARITHMETICEVALUATOR_H

#include <stdbool.h>




void pushChar(struct CharStack *, char pushedValue);
char popChar(struct CharStack *);
void pushNum(struct NumStack *, double);
double popNum(struct NumStack *);
char peekChar(struct CharStack);
void computeStack(struct CharStack *, struct NumStack *);

void printCharacterArray(char*);
void printCharacterStack(struct CharStack);
void printDoubleArray(double*, int);
void printDoubleStack(struct NumStack);

char* getKeyboardInput(void);

void calculateArithmeticExpression(char *);

double add(double, double);
double subtract(double, double);
double multiply(double, double);
double divide(double, double);
double exponentiate(double, double);

bool isFlushedOperatorLessThanOrEqualTopStackElement(char, struct CharStack);
bool isFirstLessThanOrEqualSecond(char, char);

#endif
