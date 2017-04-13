#include "arithmeticEvaluator.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CLOSING_PARENTHESIS ')'

enum CYCLE{
    FIRST_CYCLE = 1,
    SECOND_CYCLE = 2
};

enum PRECEDENCE{
    ADDITION = 1,
    SUBTRACTION = 1,
    MULTIPLICATION = 2,
    DIVISION = 2,
    EXPONENTIATION = 3,
    BRACKETS = 4
};

void createPostfixStacks(char *infix){
    char token;
    double number;
    while((token = getToken(&infix)) != '\0')
    {
        if(isdigit(token))
        {
            pushNum(&operandStack, (double)(token - '0'));
        }
        else if(token == '(')
        {
            pushChar(&operatorStack, token);
        }
        else if(token == ')')
        {
            while(peekChar(operatorStack) != '(')
            {
                computeStacksSinglePass(&operatorStack, &operandStack);
            }
            popChar(&operatorStack);
        }
        else
        {
            while(isTokenLessThanOrEqualTopStackElement(token, operatorStack))
            {
                computeStacksSinglePass(&operatorStack, &operandStack);
            }
            pushChar(&operatorStack, token);
        }
    }
    while(operatorStack.stackPointer > 0)
    {
        computeStacksSinglePass(&operatorStack, &operandStack);
    }
}

bool isTokenLessThanOrEqualTopStackElement(char comparitor, struct CharStack operatorStack){
    char peekedCharacter = peekChar(operatorStack);
    if(peekedCharacter == 'STACK_EMPTY')
    {
        return false;
    }
    return isFirstLessThanOrEqualSecond(comparitor, peekedCharacter);
}

bool isFirstLessThanOrEqualSecond(char a, char b){
    short result;
    switch(a){
        case '+':
            result = ADDITION;
            break;
        case '-':
            result = SUBTRACTION;
            break;
        case '*':
            result = MULTIPLICATION;
            break;
        case '/':
            result = DIVISION;
            break;
        case '^':
            result = EXPONENTIATION;
            break;
    }
    switch(b){
        case '+':
            result -= ADDITION;
            break;
        case '-':
            result -= SUBTRACTION;
            break;
        case '*':
            result -= MULTIPLICATION;
            break;
        case '/':
            result -= DIVISION;
            break;
        case '^':
            result -= EXPONENTIATION;
            break;
    }
    if (result > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
