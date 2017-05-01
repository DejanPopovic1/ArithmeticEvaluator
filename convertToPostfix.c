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

bool mergeSignage(char *lastToken, char token){
    if(isdigit(*lastToken) || isdigit(token)) {
        *lastToken = token;
        return false;
    }
    else if (token == '+') {
        return true;
    }
    else if (token == '(' || token == ')') {
        return false;
    }
    else if(*lastToken == '+'){
        popChar(&operatorStack);
        pushChar(&operatorStack, '-');
        *lastToken = '-';
        return true;
    }
    else if(*lastToken == '-'){
        popChar(&operatorStack);
        pushChar(&operatorStack, '+');
        *lastToken = '+';
        return true;
    }
}

void calculateArithmeticExpression(char *infix){
    bool isDoubleSign = false;
    char token;
    char lastToken = '+';
    double number;
    while((token = *infix++) != '\0') {
        isDoubleSign = mergeSignage(&lastToken, token);
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
        else if (isDoubleSign == false) {
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
