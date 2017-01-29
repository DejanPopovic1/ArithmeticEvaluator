#include "arithmeticEvaluator.h"
#include <stdio.h>
#include <stdlib.h>

#define CLOSING_PARENTHESIS ')'

void convertToPostfix(char *infix){
    char token;
    while((token = getToken(&infix)) != '\0'){
            if(isdigit(token))
            {
                pushNum(&operandStack, token);
            }
            else if(token == CLOSING_PARENTHESIS)
            {
//              flushOperatorStackToNextParenthesis(&operandStack, &operatorStack);
            }
            else if(!isdigit(token))
            {
                pushChar(&operatorStack, token);
            }
    }

}
