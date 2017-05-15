#include "convertToPostfix.h"
#include "tokenizer.h"

struct CharStack operatorStack = {.stackPointer = 0};
struct CharStack bufferedOperatorStack = {.stackPointer = 0};
struct NumStack operandStack = {.stackPointer = 0};

/*Although '(' and ')' has higher precedence than all other operators, it must be any value lower than the other operators to ensure its priority*/
struct precedence precedenceArray[SIZE_OF_PRECEDENCE_ARRAY] = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}, {'(', 0}, {')', 0}};

bool isFirstLessThanOrEqualSecond(char a, char b){
    int result = linearSearch(a, precedenceArray) - linearSearch(b, precedenceArray);
    return (result <= 0) ? true : false;
}

int linearSearch(char searchChar, struct precedence *arrayToSearch){
    int i;
    for(i = 0; i < SIZE_OF_PRECEDENCE_ARRAY; i++) {
        if(arrayToSearch[i].arithmeticOperator == searchChar) {
            return arrayToSearch[i].precedence;
        }
    }
    return -1;
}

bool isFlushedOperatorLessThanOrEqualTopStackElement(char comparitor, struct CharStack operatorStack){
    if(operatorStack.stackPointer == 0) {
        return false;
    }
    char peekedCharacter = peekChar(operatorStack);
    return isFirstLessThanOrEqualSecond(comparitor, peekedCharacter);
}

bool flushBufferedOperatorStack(char *signage, char *flushedOperator) {
    bool isThereAnythingToFlush = true;
    *signage = '+';
    char comparitor1;
    char comparitor2;
    while(bufferedOperatorStack.stackPointer > 2) {
        comparitor1 = popChar(&bufferedOperatorStack);
        comparitor2 = popChar(&bufferedOperatorStack);
        if(comparitor1 == '-' && comparitor2 == '-') {
            pushChar(&bufferedOperatorStack, '+');
        }
        else if((comparitor1 == '+' && comparitor2 == '-') || (comparitor1 == '-' && comparitor2 == '+')) {
            pushChar(&bufferedOperatorStack, '-');
        }
        else {
            ;
        }
    }
    if(bufferedOperatorStack.stackPointer == 2) {
        *signage = popChar(&bufferedOperatorStack);
        *flushedOperator = popChar(&bufferedOperatorStack);
        return isThereAnythingToFlush;
    }
    else if(bufferedOperatorStack.stackPointer == 1) {
        //*signage = '+';
        *flushedOperator = popChar(&bufferedOperatorStack);
        return isThereAnythingToFlush;
    }
    else if (bufferedOperatorStack.stackPointer == 0) {
        isThereAnythingToFlush = false;
        return isThereAnythingToFlush;
    }
    return isThereAnythingToFlush;
}

void calculateArithmeticExpression(char *infix){
    char *token = "0";
    char previousToken[MAX_TOKEN_LENGTH];
    char signage;
    char flushedOperator;
    if(*infix == '-' || *infix == '+') {
        pushNum(&operandStack, (double)('0' - '0'));
    }
    while(1) {
        if (strcmp(token, "") == 0) {
            break;
        }
        token = getToken(&infix, precedenceArray);
        if(isdigit(*token)) {
            if(flushBufferedOperatorStack(&signage, &flushedOperator)) {//There was something to flush and it was flushed and we are trying to add a digit as above
                while(isFlushedOperatorLessThanOrEqualTopStackElement(flushedOperator, operatorStack)) {//While the flushed operator is of lesser precedence than the operator at the top of the operator stack
                    computeStack(&operatorStack, &operandStack); //Compute the stacks
                }
                pushChar(&operatorStack, flushedOperator); //Until it is finally of greater precdence in which case we can finally push it onto the character stack
                (signage == '-') ? pushNum(&operandStack, (-1)*strtod(token, NULL)) : pushNum(&operandStack, strtod(token, NULL));//The number was pushed appropriately
            }
            else {//There was nothing to flush and we are trying to add a digit as above
                pushNum(&operandStack, strtod(token, NULL));
            }
        }
        else if(strcmp(token, "(") == 0) {
            if(flushBufferedOperatorStack(&signage, &flushedOperator)) {//There was something to flush and it was flushed and we are trying to add a opening parenthesis as above
                while(isFlushedOperatorLessThanOrEqualTopStackElement(flushedOperator, operatorStack)) {//While the flushed operator is of lesser precedence than the operator at the top of the operator stack
                    computeStack(&operatorStack, &operandStack); //Compute the stacks
                }
                pushChar(&operatorStack, flushedOperator); //Until it is finally of greater precdence in which case we can finally push it onto the character stack
                if(signage == '+') {//The opening parenthesis was pushed appropriately
                    pushChar(&operatorStack, *token);
                }
                else {//An invisible '-1' is pushed onto the number stack. An invisible * is pushed onto the operator stack. The opening parenthesis was pushed appropriately
                    pushNum(&operandStack, (double)(-1));
                    pushChar(&operatorStack, '*');
                    pushChar(&operatorStack, *token);
                }
            }
            else {//There was nothing to flush and we are trying to add an opening parenthesis as above. This will happen either as (1+1) or 1+((1+1)+1)
                pushChar(&operatorStack, *token);
            }
        }
        else if(strcmp(token, ")") == 0) {
            while (peekChar(operatorStack) != '(') {
                computeStack(&operatorStack, &operandStack);
            }
            popChar(&operatorStack);
        }
        else {
            if(strcmp(previousToken, "(") == 0) {
                pushNum(&operandStack, 0);
            }
            pushChar(&bufferedOperatorStack, *token);
        }
        strcpy(previousToken, token);
        if(!(strcmp(token, "") == 0)) {
            free(token);
        }
    }
    while(operatorStack.stackPointer > 0) {
        computeStack(&operatorStack, &operandStack);
    }
    free(token);
    printDoubleStack(operandStack);
}

void computeStack(struct CharStack *operatorStack, struct NumStack *operandStack){
    double result;
    char operatorCharacter = '\0';
    double secondOperand = popNum(operandStack);
    double firstOperand = popNum(operandStack);
    operatorCharacter = popChar(operatorStack);
    switch(operatorCharacter){
        case '+':
            result = add(firstOperand, secondOperand);
            break;
        case '-':
            result = subtract(firstOperand, secondOperand);
            break;
        case '*':
            result = multiply(firstOperand, secondOperand);
            break;
        case '/':
            result = divide(firstOperand, secondOperand);
            break;
        case '^':
            result = exponentiate(firstOperand, secondOperand);
            break;
    }
    pushNum(operandStack, result);
}
