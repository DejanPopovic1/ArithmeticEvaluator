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
    while((token = getToken(&infix)) != '\0'){
        if(isdigit(token))
        {
//            if(isNextStackElementGreaterOrEqualPrecedanceThanToken(token, operatorStack)){
//                computeStacks(&operatorStack, &operandStack);
//                pushChar(&operatorStack, token);
//            }
//            else
//            {
                    //pushNum(&operandStack, (double)(token - '0'));


                    pushNum(&operandStack, (double)(token - '0'));


//            }
        }
        else if(token == ')'){
            pushChar(&operatorStack, token);
            //computeStacks(&operatorStack, &operandStack);
        }
        else if(!isdigit(token))
        {
            if(token == '+')
            {
                char peekedToken = getToken(&infix);
                pushNum(&operandStack, (double)(peekedToken - '0'));
                pushChar(&operatorStack, token);
            }
            else if (token == '-')
            {
                char peekedToken = getToken(&infix);
                pushNum(&operandStack, (-1)*(double)(peekedToken - '0'));
                pushChar(&operatorStack, '+');
            }

        }
    }
    //Flush the remaining stacks

    while(operatorStack.stackPointer > 0){
        computeStacks(&operatorStack, &operandStack);
//
    }
}

bool isNextStackElementGreaterOrEqualPrecedanceThanToken(char comparitor, struct CharStack operatorStack){
    char peekedCharacter = peekChar(operatorStack);
    return isGreaterOrEqualPrecedance(comparitor, peekedCharacter);
}

bool isGreaterOrEqualPrecedance(char comparitor, char peekedCharacter){
    unsigned short result;
    switch(comparitor){
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
    }
    switch(peekedCharacter){
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
    }
    if (result > 0){
        return false;
    }
    else {
        return true;
    }
}
