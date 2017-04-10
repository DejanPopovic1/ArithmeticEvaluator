#include <stdio.h>
#include <stdlib.h>
#include "arithmeticEvaluator.h"

#define MAX_STACK_SIZE 200

struct CharStack operatorStack = {.stackPointer = 0};
struct CharStack swappedOperatorStack = {.stackPointer = 0};
struct NumStack operandStack = {.stackPointer = 0};

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
        return 'STACK_EMPTY';
    }
    return stack.stackValues[stack.stackPointer - 1];
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

void swapCharStack(struct CharStack *unSwappedStack){
    swapCharArray(unSwappedStack -> stackValues, unSwappedStack -> stackPointer);
}

//Undefinned reference to this function if it is included below computeStack
void computeStacksSinglePass(struct CharStack *operatorStack, struct NumStack *operandStack){
    double result;
    char operatorCharacter = '\0';
    double secondOperand = popNum(operandStack);
    double firstOperand = popNum(operandStack);
    operatorCharacter = popChar(operatorStack);
    switch(operatorCharacter){
        case '+':
            result = add(firstOperand, secondOperand);
            break;
        case '-':
            result = subtract(firstOperand, secondOperand);
            break;
        case '*':
            result = multiply(firstOperand, secondOperand);
            break;
        case '/':
            result = divide(firstOperand, secondOperand);
            break;
        case '^':
            result = exponentiate(firstOperand, secondOperand);
            break;
    }
    pushNum(operandStack, result);
}

void computeStacks(struct CharStack *operatorStack, struct NumStack *operandStack){
    if (peekChar(*operatorStack) != '('){
        computeStacksSinglePass(operatorStack, operandStack);
    }
    else if (peekChar(*operatorStack) == '('){
        operatorStack -> stackPointer--;
        operatorStack -> stackPointer--;
        while (peekChar(*operatorStack) != ')'){
            computeStacksSinglePass(&operatorStack, &operandStack);
        }
        operatorStack -> stackPointer--;
    }
}
