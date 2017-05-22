#include "mathUtilities.h"

double add(double firstOperand, double secondOperand){
    return firstOperand + secondOperand;
}

double subtract(double firstOperand, double secondOperand){
    return firstOperand - secondOperand;
}

double multiply(double firstOperand, double secondOperand){
    return firstOperand * secondOperand;
}

double divide(double firstOperand, double secondOperand){
    return firstOperand / secondOperand;
}

double exponentiate(double firstOperand, double secondOperand){
    return pow(firstOperand, secondOperand);
}

double factorial(double x) {
    return tgamma(x+1.);
}

double absoluteValue(double x) {
    return abs(x);
}
