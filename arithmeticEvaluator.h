#ifndef ARITHMETICEVALUATOR_H
#define ARITHMETICEVALUATOR_H

#define MAX_STACK_SIZE 100

extern struct CharStack operatorStack;
extern struct CharStack SwappedOperatorStack;
extern struct NumStack operandStack;

struct CharStack{
    char stackValues[MAX_STACK_SIZE];
    int stackPointer;
};

struct NumStack{
    double stackValues[MAX_STACK_SIZE];
    int stackPointer;
};

void swapDoubleArray(double *, int);
void swapCharArray(double *, int sizeOfArray);

void pushChar(struct CharStack *, char pushedValue);
char popChar(struct CharStack);
void pushNum(struct NumStack *, double);
double popNum(struct NumStack);

void printCharacterArray(char*);
void printCharacterStack(struct CharStack);
void printDoubleArray(double*, int);
void printDoubleStack(struct NumStack);
//void swapCharStack(struct CharStack *);

char* getKeyboardInput(void);
char getToken(char **);

void createPostfixStacks(char *);

#endif
