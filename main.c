#include "arithmeticEvaluator.h"
#include <stdio.h>

int main(){
    char* postfix;
    char* infixedUserInput = getKeyboardInput();
    pushChar(&operatorStack, '-');
    pushChar(&operatorStack, '+');
    pushChar(&operatorStack, '*');
    pushChar(&operatorStack, '/');
    printCharacterStack(operatorStack);
    swapCharStack(&operatorStack);
    return 0;
}
