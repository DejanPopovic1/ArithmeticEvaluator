#include "arithmeticEvaluator.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

enum PRECEDENCE{
    ADDITION = 1,
    SUBTRACTION = 1,
    MULTIPLICATION = 2,
    DIVISION = 2,
    EXPONENTIATION = 3,
    BRACKETS = 4
};

struct precedence{
    char arithmeticOperator;
    int precedence;
};

struct precedence precedenceArray[] = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}, {'\0', 1}};

int linearSearch(char searchChar, struct precedence *arrayToSearch){
    int i;
    for(i = 0; arrayToSearch[i].arithmeticOperator != '\0'; i++) {
        if(arrayToSearch[i].arithmeticOperator == searchChar) {
            return arrayToSearch[i].precedence;
        }
    }
    return -1;
}

bool flushBufferedOperatorStack(char *signage, char *flushedOperator) {
    bool isThereAnythingToFlush = true;
    *signage = '+';
    char comparitor1;
    char comparitor2;
    while(bufferedOperatorStack.stackPointer > 2){
        comparitor1 = popChar(&bufferedOperatorStack);
        comparitor2 = popChar(&bufferedOperatorStack);
        if(comparitor1 == '-' && comparitor2 == '-') {
            pushChar(&bufferedOperatorStack, '+');
        }
        else if((comparitor1 == '+' && comparitor2 == '-') || (comparitor1 == '-' && comparitor2 == '+')) {
            pushChar(&bufferedOperatorStack, '-');
        }
        else {
            ;
        }
    }
    if(bufferedOperatorStack.stackPointer == 2) {
        *signage = popChar(&bufferedOperatorStack);
        *flushedOperator = popChar(&bufferedOperatorStack);
        return isThereAnythingToFlush;
    }
    else if(bufferedOperatorStack.stackPointer == 1) {
        //*signage = '+';
        *flushedOperator = popChar(&bufferedOperatorStack);
        return isThereAnythingToFlush;
    }
    else if (bufferedOperatorStack.stackPointer == 0) {
        isThereAnythingToFlush = false;
        return isThereAnythingToFlush;
    }
}

void calculateArithmeticExpression(char *infix){
    char charTopStack;
    char charTopBufferStack;
    double numTopStack;
    char token;
    char signage;
    char flushedOperator;
    if(*infix == '-' || *infix == '+') {
        pushNum(&operandStack, (double)('0' - '0'));
    }
    while((token = *infix++) != '\0') {
        if(isdigit(token)) {
            if(flushBufferedOperatorStack(&signage, &flushedOperator)) {//There was something to flush and it was flushed and we are trying to add a digit as above
                while(isFlushedOperatorLessThanOrEqualTopStackElement(flushedOperator, operatorStack)) {//While the flushed operator is of lesser precedence than the operator at the top of the operator stack
                    computeStack(&operatorStack, &operandStack); //Compute the stacks
                }
                pushChar(&operatorStack, flushedOperator); //Until it is finally of greater precdence in which case we can finally push it onto the character stack
                (signage == '-') ? pushNum(&operandStack, (double)(-1)*(token - '0')) : pushNum(&operandStack, (double)(token - '0'));//The number was pushed appropriately
            }
            else {//There was nothing to flush and we are trying to add a digit as above
                pushNum(&operandStack, (double)(token - '0'));
            }


            //if(!(bufferedOperatorStack.stackPointer == 0 && operatorStack.stackPointer == 0)) {//The conditional statement ensures that flushedOperator and Operator stack remain unchanged when the first number is pushed onto the number stack. If this is not here, the operator stack gets pushed junk and the stack pointer moves by one on the first number push

        }
        else {
            pushChar(&bufferedOperatorStack, token);
        }
        charTopBufferStack = bufferedOperatorStack.stackValues[bufferedOperatorStack.stackPointer - 1];
        numTopStack = operandStack.stackValues[operandStack.stackPointer - 1];
        charTopStack = operatorStack.stackValues[operatorStack.stackPointer -1];
int dummyVariable;
dummyVariable = 1;
    }
    while(operatorStack.stackPointer > 0) {
        computeStack(&operatorStack, &operandStack);
    }
}

bool isFlushedOperatorLessThanOrEqualTopStackElement(char comparitor, struct CharStack operatorStack){
    char peekedCharacter = peekChar(operatorStack);
    if(peekedCharacter == 'S') {
        return false;
    }
    return isFirstLessThanOrEqualSecond(comparitor, peekedCharacter);
}

bool isFirstLessThanOrEqualSecond(char a, char b){
    int result = linearSearch(a, precedenceArray) - linearSearch(b, precedenceArray);
    return (result <= 0) ? true : false;
}

void computeStack(struct CharStack *operatorStack, struct NumStack *operandStack){
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
