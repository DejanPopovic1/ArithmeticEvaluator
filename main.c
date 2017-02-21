#include "arithmeticEvaluator.h"
#include <stdio.h>

int main(){
    char* postfix;
    char* infixedUserInput = getKeyboardInput();
    printf("\n");
    createPostfixStacks(infixedUserInput);

    printDoubleStack(operandStack);
    printCharacterStack(operatorStack);



//    computeStacks(&operatorStack, &operandStack);
//    printf("\n");
//    computeStacks(&operatorStack, &operandStack);
//    printDoubleStack(operandStack);
//    printCharacterStack(operatorStack);
//
//    printf("\n");
//    computeStacks(&operatorStack, &operandStack);
//    printDoubleStack(operandStack);
//    printCharacterStack(operatorStack);

    //computeStacks(&operatorStack, &operandStack);
    //printf("\n");
    //printDoubleStack(operandStack);
    //printCharacterStack(operatorStack);
    return 0;
}
