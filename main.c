#include "arithmeticEvaluator.h"
#include <stdio.h>

int main(){
    char* postfix;
    char* infixedUserInput = getKeyboardInput();
    printf("\n");
    createPostfixStacks(infixedUserInput);
    printDoubleStack(operandStack);
    printCharacterStack(operatorStack);
    return 0;
}
