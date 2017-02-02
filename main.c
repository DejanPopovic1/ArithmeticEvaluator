#include "arithmeticEvaluator.h"
#include <stdio.h>

int main(){
    char* postfix;
    char* infixedUserInput = getKeyboardInput();
    convertToPostfix(infixedUserInput);
    printCharacterStack(operatorStack);
    printDoubleStack(operandStack);
    return 0;
}
