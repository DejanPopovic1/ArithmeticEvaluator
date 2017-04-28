#include "arithmeticEvaluator.h"
#include <stdio.h>

int main(){
    char* infixedUserInput = getKeyboardInput();
    printf("\n");
    calculateArithmeticExpression(infixedUserInput);
    printDoubleStack(operandStack);
    free(infixedUserInput);
    return 0;
}
