#ifndef INPUTANDPRINTINGUTILITIES_H
#define INPUTANDPRINTINGUTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include "stackUtilities.h"

#define MEMORY_ALLOCATE 200

void printCharacterArray(char*);
void printDoubleArray(double* arrayToBePrinted, int sizeOfArray);
void printCharacterStack(struct CharStack);
void printDoubleStack(struct NumStack);
char* getKeyboardInput(void);

#endif
