#include "arithmeticEvaluator.h"
#include <stdio.h>

int main(){
    char* postfix;
    //char* infixedUserInput = getKeyboardInput();
    //createPostfixStacks(infixedUserInput);
    pushChar(&operatorStack, '-');
    pushChar(&operatorStack, '+');
    pushChar(&operatorStack, '*');
    pushChar(&operatorStack, '/');
    printCharacterStack(operatorStack);
    swapCharStack(&operatorStack);
    printCharacterStack(operatorStack);
    return 0;
}
