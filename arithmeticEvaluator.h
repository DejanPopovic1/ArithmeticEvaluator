#define MAX_STACK_SIZE 100

extern struct CharStack operatorStack;
extern struct NumStack operandStack;

struct CharStack{
    char stackValue[MAX_STACK_SIZE];
    int stackPointer;
};

struct NumStack{
    double stackValue[MAX_STACK_SIZE];
    int stackPointer;
};

void pushChar(struct CharStack *, char pushedValue);
char popChar(struct CharStack);

void printCharacterArray(char*);
void printCharacterStack(struct CharStack);
char* getKeyboardInput(void);
char getToken(char **);

void convertToPostfix(char *);
