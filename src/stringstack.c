#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

void resize(ExpressionStack *stack){
    stack->size = stack->size + 8;
    expressionItem *temp_arr = malloc(stack->size*sizeof(expressionItem));
    for(int = 0; i < stack->size-8; i++){
        *temp_arr[i] = stack->data[i];
    }
    free(stack->data);
    stack->data = temp_arr;

    if(temp_arr == NULL){
        exit();
    }
}

void initializeExpressionStack(ExpressionStack *stack) {
    stack->size = 8;
    stack->data = malloc(stack->size*sizeof(expressionItem));
    stack->top = -1;
}

int isExpressionStackFull(ExpressionStack *stack) {
    return stack->top == stack->size - 1;
}

int isExpressionStackEmpty(ExpressionStack *stack) {
    return stack->top == -1;
}

void pushE(ExpressionStack *stack, expressionItem item) {
    if (isExpressionStackFull(stack)) {
        resize(stack);
    }
    stack->top++;
    stack->data[stack->top] = item;
}

void popE(ExpressionStack *stack) {
    if (isExpressionStackEmpty(stack)) {
        printf("Expression Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    stack->top--;
}

expressionItem peekToken(ExpressionStack *stack) {
    if (isExpressionStackEmpty(stack)) {
        printf("Expression Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

void dispozeStackE(ExpressionStack *stack){
    if(!isExpressionStackEmpty){
        free(stack->data);
        stack->top = -1;
        stack->data = NULL;
    }
    stack->top = -1;
}