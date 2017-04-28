#include "arithmeticEvaluator.h"
#include <stdio.h>

int main(){
    char* infixedUserInput = getKeyboardInput();
    printf("\n");
    createPostfixStacks(infixedUserInput);
    printDoubleStack(operandStack);
    return 0;
}
