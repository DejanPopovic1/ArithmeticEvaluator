void swapDoubleArray(double *unswappedArray, int sizeOfArray){
    double temporaryElement;
    for(int i = 0; i < sizeOfArray; i++, sizeOfArray--){
        temporaryElement = unswappedArray[i];
        unswappedArray[i] = unswappedArray[sizeOfArray - 1];
        unswappedArray[sizeOfArray - 1] = temporaryElement;
    }
}

void swapCharArray(char *unswappedArray, int sizeOfArray){
    char temporaryElement;
    for(int i = 0; i < sizeOfArray; i++, sizeOfArray--){
        temporaryElement = unswappedArray[i];
        unswappedArray[i] = unswappedArray[sizeOfArray - 1];
        unswappedArray[sizeOfArray - 1] = temporaryElement;
    }
}
