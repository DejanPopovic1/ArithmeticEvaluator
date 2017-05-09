#include <stdio.h>
#include "convertToPostfix.h"
#include "inputAndPrintingUtilities.h"

int main(){
    char* infixedUserInput = getKeyboardInput();
    printf("\n");
    calculateArithmeticExpression(infixedUserInput);
    free(infixedUserInput);
    return 0;
}
