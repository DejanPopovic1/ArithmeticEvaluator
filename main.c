#include "arithmeticEvaluator.h"
#include <stdio.h>

int main(){
    char* postfix;
    char* infixedUserInput = getKeyboardInput();
    createPostfixStacks(infixedUserInput);
    //swapCharStack(&operatorStack);
    printDoubleStack(operandStack);
    printCharacterStack(operatorStack);
    computeStacks(&operatorStack, &operandStack);
        printDoubleStack(operandStack);
    printCharacterStack(operatorStack);
    //printDoubleStack(operandStack);
    //printCharacterStack(operatorStack);
    return 0;
}
