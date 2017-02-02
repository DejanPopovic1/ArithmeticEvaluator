#include <stdio.h>
#include <stdlib.h>
#include "arithmeticEvaluator.h"

#define MAX_STACK_SIZE 100

struct CharStack operatorStack = {.stackPointer = 0};
struct NumStack operandStack = {.stackPointer = 0};

void pushChar(struct CharStack *stack, char pushedValue){
    if (stack -> stackPointer < MAX_STACK_SIZE) {
        stack -> stackValue[stack -> stackPointer++] = pushedValue;
    }
    else {
        fprintf(stderr, "Character Stack full, can't push %g\n", pushedValue);
        exit(-1);
    }
}

char popChar(struct CharStack stack){
    if (stack.stackPointer > 0){
        return stack.stackValue[--stack.stackPointer];
    }
    else {
        fprintf(stderr, "Character Stack empty\n");
        exit(-1);
    }
}

void pushNum(struct NumStack *stack, double pushedValue){
    if (stack -> stackPointer < MAX_STACK_SIZE) {
        stack -> stackValue[stack -> stackPointer++] = pushedValue;
    }
    else {
        fprintf(stderr, "Number Stack full, can't push %g\n", pushedValue);
        exit(-1);
    }
}

double popNum(struct NumStack stack){
    if (stack.stackPointer > 0){
        return stack.stackValue[--stack.stackPointer];
    }
    else {
        fprintf(stderr, "Number Stack empty\n");
        exit(-1);
    }
}
