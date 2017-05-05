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
    while(bufferedOperatorStack.stackPointer > 2) {
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

void consolidateSignage(char **newInfix, bool *signage) {
    *signage = false;
    char peekedToken;
    char shiftedOperator;
    while(true){
        peekedToken = *(*newInfix + 1);
//        peekedSecondToken = *(*newInfix + 2);
        if (isdigit(**newInfix) || **newInfix == '(' || **newInfix == ')' || isdigit(peekedToken) || peekedToken == '(' || peekedToken == ')' ) {return;}//REFACTOR everything except operators
        //if (true) {return;}
        if((**newInfix) == '-' && peekedToken == '-') {
            *newInfix = *newInfix + 1;
            **newInfix = '+';
        }
        else if((**newInfix) == '-' || peekedToken == '-') {
            *newInfix = *newInfix + 1;
            **newInfix = '-';
        }
        else if((**newInfix) == '+' || peekedToken == '+') {
            *newInfix = *newInfix + 1;
        }
        else if(peekedToken == '+') {//ASSUMING THIS IS ALL OPERATORS
            shiftedOperator = **newInfix;
            *newInfix = *newInfix + 1;
            **newInfix = shiftedOperator;
            *signage = false;
        }
        else if(peekedToken == '-') {//ASSUMING THIS IS ALL OPERATORS
            shiftedOperator = **newInfix;
            *newInfix = *newInfix + 1;
            **newInfix = shiftedOperator;
            *signage = true;
        }
    }
}

void calculateArithmeticExpression(char *infix){
    char token = '0';
    char peekedToken;
    bool signage;
    if(*infix == '-' || *infix == '+') {
        pushNum(&operandStack, (double)('0' - '0'));
    }
    while((token = *infix) != '\0') {//read in token

        //Consolidate function will change token and advance the pointer if necassary.
        consolidateSignage(&infix, &signage);
        token = *infix;
        peekedToken = *(infix + 1); //Keep peek ahead intact after consolidating signs
        infix++;//move to next token
        if(isdigit(token)) {
            pushNum(&operandStack, (double)(token - '0'));
        }
        else if(token == '(') {
            if(peekedToken == '+' || peekedToken == '-') {
                pushNum(&operandStack, 0);
            }
            pushChar(&operatorStack, token);
        }
        else if(token == ')') {
            while (peekChar(operatorStack) != '(') {
                computeStack(&operatorStack, &operandStack);
            }
            popChar(&operatorStack);
        }
        else {
            while (isFlushedOperatorLessThanOrEqualTopStackElement(token, operatorStack)) {
                computeStack(&operatorStack, &operandStack);
            }
            pushChar(&operatorStack, token);
        }
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
