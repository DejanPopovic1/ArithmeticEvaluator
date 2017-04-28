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

void calculateArithmeticExpression(char *infix){
    char token;
    double number;
    while((token = *infix++) != '\0') {
        if(isdigit(token)) {
            pushNum(&operandStack, (double)(token - '0'));
        }
        else if(token == '(') {
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
            pushChar(&operatorStack, token);
        }
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
