#include "convertToPostfix.h"
#include "tokenizer.h"

struct CharStack operatorStack = {.stackPointer = 0};
struct CharStack bufferedOperatorStack = {.stackPointer = 0};
struct NumStack operandStack = {.stackPointer = 0};

/*Although '(' and ')' has higher precedence than all other operators, it must be any value lower than the other operators to ensure its priority*/
struct precedence precedenceArray[SIZE_OF_PRECEDENCE_ARRAY] = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}, {'!', 4}, {'(', 0}, {')', 0}, {'|', 0}};
char *operatorsBeforeOpeningAbsoluteValue[SIZE_OF_OPERATORS_BEFORE_OPENING_ABSOLUTE_VALUE_ARRAY] = {"+", "-", "*", "/", "^", "("};
char *operatorsBeforeClosingAbsoluteValue[SIZE_OF_OPERATORS_BEFORE_CLOSING_ABSOLUTE_VALUE_ARRAY] = {")"};

bool isFirstLessThanOrEqualSecond(char a, char b) {
    int result = linearSearch(a, precedenceArray) - linearSearch(b, precedenceArray);
    return (result <= 0) ? true : false;
}

int linearOperatorSearch(char *searchString, char *arrayToSearch[], int sizeOfArray) {
    int i;
    for(i = 0; i < sizeOfArray; i++) {
        if(strcmp(arrayToSearch[i], searchString) == 0) {
            return i;
        }
    }
    return -1;
}

int linearSearch(char searchChar, struct precedence *arrayToSearch) {
    int i;
    for(i = 0; i < SIZE_OF_PRECEDENCE_ARRAY; i++) {
        if(arrayToSearch[i].arithmeticOperator == searchChar) {
            return arrayToSearch[i].precedence;
        }
    }
    return -1;
}

bool isFlushedOperatorLessThanOrEqualTopStackElement(char comparitor, struct CharStack operatorStack) {
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

void handleNumber(char *signage, char *flushedOperator, char *token){
    if(flushBufferedOperatorStack(signage, flushedOperator)) {//There was something to flush and it was flushed and we are trying to add a digit as above
        while(isFlushedOperatorLessThanOrEqualTopStackElement(*flushedOperator, operatorStack)) {//While the flushed operator is of lesser precedence than the operator at the top of the operator stack
            computeStack(&operatorStack, &operandStack); //Compute the stacks
        }
        pushChar(&operatorStack, *flushedOperator); //Until it is finally of greater precdence in which case we can finally push it onto the character stack
        (*signage == '-') ? pushNum(&operandStack, (-1)*strtod(token, NULL)) : pushNum(&operandStack, strtod(token, NULL));//The number was pushed appropriately
    }
    else {//There was nothing to flush and we are trying to add a digit as above
        pushNum(&operandStack, strtod(token, NULL));
    }
}

void handleOpenParenthesis(char *signage, char *flushedOperator, char *token){
    if(flushBufferedOperatorStack(signage, flushedOperator)) {//There was something to flush and it was flushed and we are trying to add an opening parenthesis as above
        while(isFlushedOperatorLessThanOrEqualTopStackElement(*flushedOperator, operatorStack)) {//While the flushed operator is of lesser precedence than the operator at the top of the operator stack
            computeStack(&operatorStack, &operandStack); //Compute the stacks
        }
        pushChar(&operatorStack, *flushedOperator); //Until it is finally of greater precdence in which case we can finally push it onto the character stack
        if(*signage == '+') {//The opening parenthesis was pushed appropriately
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

void handleClosedParenthesis(){

    while (peekChar(operatorStack) != '(') {
        computeStack(&operatorStack, &operandStack);
    }
    popChar(&operatorStack);
}

void handleFactorial(char *token){
    pushNum(&operandStack, (double)1);//This is a dummy addition to the stack used so that we dont have to complicate compute stack. It gets popped never to be used
    pushChar(&operatorStack, *token);
    computeStack(&operatorStack, &operandStack);
}

void handleOperator(char *previousToken, char *token){
    if(strcmp(previousToken, "(") == 0) {//An operator was reached AND it is immediately after an opening bracket, i.e, (-3). This adds a dummy zero value
        pushNum(&operandStack, 0);
    }
    pushChar(&bufferedOperatorStack, *token);//An operator was reached
}

//void handleClosedModulusOLD(){
//    while (peekChar(operatorStack) != '|') {
//        computeStack(&operatorStack, &operandStack);
//    }
//    popChar(&operatorStack);
//}

//void handleModulusOLD(char *signage, char *flushedOperator, char *token){
//    if(containsChar(&operatorStack, token) < 0){
//        handleOpenParenthesis(signage, flushedOperator, token);
//    }
//    else if(containsChar(&operatorStack, token) >= 0){
//        handleClosedModulusOLD();
//    }
//}

void handleOpenAbsoluteValue(char *token){

};

void handleClosedAbsoluteValue(char *token){

};

void calculateArithmeticExpression(char *infix){
    //char *token = "0";
    char tokenInitialiser[] = "0";
    char *token = NULL;
    char previousTokenInitialiser[MAX_TOKEN_LENGTH] = START_OF_STRING;
    char *previousToken = previousTokenInitialiser;
    char signage;
    char flushedOperator;
    if(*infix == '-' || *infix == '+') {
        pushNum(&operandStack, (double)('0' - '0'));
    }
    printf("%d\n\n\n", linearOperatorSearch("(", operatorsBeforeOpeningAbsoluteValue, SIZE_OF_OPERATORS_BEFORE_OPENING_ABSOLUTE_VALUE_ARRAY));
    while(1) {


        token = getToken(&infix, precedenceArray);
        if (strcmp(token, "") == 0) {
            break;
        }
        if(isdigit(*token)) {
            handleNumber(&signage, &flushedOperator, token);
        }
        else if(strcmp(token, "(") == 0) {
            handleOpenParenthesis(&signage, &flushedOperator, token);
        }
        else if(strcmp(token, ")") == 0) {
            handleClosedParenthesis();
        }
        else if (strcmp(token, "!") == 0) {
            handleFactorial(token);
        }
        //|| strcmp(previousToken, "+") == 0 || strcmp(previousToken, "-") == 0 || strcmp(previousToken, "*") == 0 || strcmp(previousToken, "/") == 0 || strcmp(previousToken, "^") == 0



        else if (strcmp(token, "|") == 0 && ( strcmp(previousToken, START_OF_STRING)  == 0 )) {
            strcpy(token, OPEN_ABSOLUTE_VALUE);
            handleClosedAbsoluteValue(token);
            printf("OPENING_ABSOLUTE_VALUE (First Rule)\n");
        }
        else if (strcmp(token, "|") == 0 && (strcmp(previousToken, OPEN_ABSOLUTE_VALUE) == 0)) {
            strcpy(token, OPEN_ABSOLUTE_VALUE);
            handleClosedAbsoluteValue(token);
            printf("OPENING_ABSOLUTE_VALUE (Second Rule)\n");
        }


        else if (strcmp(token, "|") == 0 && (linearOperatorSearch(previousToken, operatorsBeforeOpeningAbsoluteValue, SIZE_OF_OPERATORS_BEFORE_OPENING_ABSOLUTE_VALUE_ARRAY) >= 0)) {
            strcpy(token, OPEN_ABSOLUTE_VALUE);
            handleClosedAbsoluteValue(token);
            printf("OPENING_ABSOLUTE_VALUE (Third Rule)\n");
        }
        else if (strcmp(token, "|") == 0 && (isdigit(*previousToken))) {
            strcpy(token, CLOSED_ABSOLUTE_VALUE);
            handleClosedAbsoluteValue(token);
            printf("CLOSING_ABSOLUTE_VALUE\n");
        }
        else if (strcmp(token, "|") == 0 && strcmp(previousToken, CLOSED_ABSOLUTE_VALUE) == 0) {
            strcpy(token, CLOSED_ABSOLUTE_VALUE);
            handleClosedAbsoluteValue(token);
            printf("CLOSING_ABSOLUTE_VALUE\n");
        }
        else if (strcmp(token, "|") == 0 && (linearOperatorSearch(previousToken, operatorsBeforeClosingAbsoluteValue, SIZE_OF_OPERATORS_BEFORE_OPENING_ABSOLUTE_VALUE_ARRAY) >= 0)) {
            strcpy(token, CLOSED_ABSOLUTE_VALUE);
            handleClosedAbsoluteValue(token);
            printf("CLOSING_ABSOLUTE_VALUE\n");
        }
        else {//Token is an operator. PLEASE MAKE THIS EXPLICIT
            handleOperator(previousToken, token);
        }
        strcpy(previousToken, token);
        if(!(strcmp(token, "") == 0)) {
            free(token);
        }
        //printCharacterStack(operatorStack);
        //printf("%d", operatorStack.stackPointer);
        //printDoubleStack(operandStack);
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
        case '!':
            result = factorial(firstOperand);
            break;
    }
    pushNum(operandStack, result);
}
