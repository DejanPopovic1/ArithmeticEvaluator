#include "arithmeticEvaluator.h"
#include <stdio.h>

int main(){
    char* postfix;
    char* infixedUserInput = getKeyboardInput();
    void convertToPostfix(infixedUserInput);
    printCharacterStack(operatorStack);
    return 0;
}
