#include "arithmeticEvaluator.h"
#include <stdio.h>
#include <stdlib.h>

#define CLOSING_PARENTHESIS ')'

void createPostfixStacks(char *infix){
    char token;
    while((token = getToken(&infix)) != '\0'){
            if(isdigit(token))
            {
                pushNum(&operandStack, (double)(token - '0'));
            }
            else if(token == CLOSING_PARENTHESIS)
            {
              computeStacks(&operatorStack, &operandStack);
            }
            else if(!isdigit(token))
            {
                pushChar(&operatorStack, token);
            }
    }
}

