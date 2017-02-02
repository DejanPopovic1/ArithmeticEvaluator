#include "arithmeticEvaluator.h"
#include <stdio.h>

int main(){
    char* postfix;
    char* infixedUserInput = getKeyboardInput();
    createPostfixStacks(infixedUserInput);
    double myArray [5] = {1.00, 2.00, 5.00, 7, 9};
    swapDoubleArray(&myArray, 5);
    printDoubleArray(myArray, 5);
    printCharacterStack(operatorStack);
    printDoubleStack(operandStack);
    return 0;
}
