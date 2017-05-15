#include "stackUtilities.h"

void pushChar(struct CharStack *stack, char pushedValue){
    if (stack -> stackPointer < MAX_STACK_SIZE) {
        stack -> stackValues[stack -> stackPointer++] = pushedValue;
    }
    else {
        fprintf(stderr, "Character Stack full, can't push %g\n", pushedValue);
        exit(-1);
    }
}

char popChar(struct CharStack *stack){
    if (stack -> stackPointer > 0){
        return stack -> stackValues[--stack -> stackPointer];
    }
    else {
        fprintf(stderr, "Character Stack empty\n");
        exit(-1);
    }
}

char peekChar(struct CharStack stack){
    if(!stack.stackPointer){
        fprintf(stderr, "Character Stack is empty, can't peek \n");
        exit(-1);
    }
    return stack.stackValues[--stack.stackPointer];
}

void pushNum(struct NumStack *stack, double pushedValue){
    if (stack -> stackPointer < MAX_STACK_SIZE) {
        stack -> stackValues[stack -> stackPointer++] = pushedValue;
    }
    else {
        fprintf(stderr, "Number Stack full, can't push %g\n", pushedValue);
        exit(-1);
    }
}

double popNum(struct NumStack *stack){
    if (stack -> stackPointer > 0){
        return stack -> stackValues[--stack -> stackPointer];
    }
    else {
        fprintf(stderr, "Number Stack empty\n");
        exit(-1);
    }
}
