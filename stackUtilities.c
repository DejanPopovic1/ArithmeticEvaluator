#include <stdio.h>

#define MAX_STACK_SIZE 100

struct CharStack{
    char stackValue[MAX_STACK_SIZE];
    int stackPointer;
};

struct CharStack operatorStack;

void pushChar(struct CharStack *stack, char pushedValue){
    if (stack -> stackPointer < MAX_STACK_SIZE) {
        stack -> stackValue[stack -> stackPointer++] = pushedValue;
    }
    else {
        fprintf(stderr, "Character Stack full, can't push %g\n", pushedValue);
        exit(-1);
    }
}
