#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_STRING_LENGTH 50

typedef struct {
    char strings[MAX_SIZE][MAX_STRING_LENGTH];
    int top;
} StringStack;

void initializeStringStack(StringStack *stack) {
    stack->top = -1;
}

int isStringStackFull(StringStack *stack) {
    return stack->top == MAX_SIZE - 1;
}

int isStringStackEmpty(StringStack *stack) {
    return stack->top == -1;
}

void pushString(StringStack *stack, const char *value) {
    if (isStringStackFull(stack)) {
        printf("String Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->top++;
    strcpy(stack->strings[stack->top], value);
}

char* popString(StringStack *stack) {
    if (isStringStackEmpty(stack)) {
        printf("String Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->strings[stack->top--];
}

char* peekString(StringStack *stack) {
    if (isStringStackEmpty(stack)) {
        printf("String Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->strings[stack->top];
}