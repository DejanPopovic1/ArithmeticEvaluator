#include "arithmeticEvaluator.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

bool flushBufferedOperatorStack() {
    char comparitor1;
    char comparitor2;
    char poppedOperator;
    char secondPoppedOperator;
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
        poppedOperator = popChar(&bufferedOperatorStack);
        //if(poppedOperator == '*' || poppedOperator == '/') {
        //    secondPoppedOperator = popChar(&bufferedOperatorStack);
        //    pushChar(&operatorStack, secondPoppedOperator);
        //    pushChar(&operatorStack, poppedOperator);
        //    return false;
        //}
        //else {
            pushChar(&operatorStack, popChar(&bufferedOperatorStack));
            return (poppedOperator == '-') ? true : false;
        //}
    }
    else if(bufferedOperatorStack.stackPointer == 1) {
       pushChar(&operatorStack, popChar(&bufferedOperatorStack));
       return false;
    }
    else {
        return false;
    }
}

void calculateArithmeticExpression(char *infix){
    char charTopStack;
    char charTopBufferStack;
    double numTopStack;
    char token;
    if(*infix == '-') {
        pushNum(&operandStack, (double)('0' - '0'));
    }
    while((token = *infix++) != '\0') {
        if(isdigit(token)) {
            (flushBufferedOperatorStack()) ? pushNum(&operandStack, -1*(double)(token - '0')) : pushNum(&operandStack, (double)(token - '0'));
        }
        else if(token == '(') {
            flushBufferedOperatorStack();
            pushChar(&operatorStack, token);
        }
        else if(token == ')') {
            while(peekChar(operatorStack) != '(') {
                computeStack(&operatorStack, &operandStack);
            }
            popChar(&operatorStack);
        }
        else {
            while(isTokenLessThanOrEqualTopStackElement(token, operatorStack)) {
                computeStack(&operatorStack, &operandStack);
            }
            pushChar(&bufferedOperatorStack, token);
        }
        charTopBufferStack = bufferedOperatorStack.stackValues[bufferedOperatorStack.stackPointer - 1];
        numTopStack = operandStack.stackValues[operandStack.stackPointer - 1];
        charTopStack = operatorStack.stackValues[operatorStack.stackPointer -1];
    }
    while(operatorStack.stackPointer > 0) {
        computeStack(&operatorStack, &operandStack);
    }
}

bool isTokenLessThanOrEqualTopStackElement(char comparitor, struct CharStack operatorStack){
    char peekedCharacter = peekChar(operatorStack);
    if(peekedCharacter == 'STACK_EMPTY') {
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
