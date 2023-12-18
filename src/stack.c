#ifndef STACK_C
#define STACK_C
#include "structs.h"
/**
 * @file stack.c
 * @brief int stack
 * 
 * IFJ a IAL projekt: Implementácia prekladača imperatívneho jazyka IFJ23
 * 
 * @author Frederick Tóth <xtothf00>
 * @author Andrej Mikuš <xmikus19>
 * @author Tom Široký <xsirok10>
 * @author Michael Babušík <xbabus01>
 */
 
/*
* This code defines a stack implementation using an array. 
* It includes functions to initialize a stack, check if it's full or empty, 
* push elements onto the stack, pop elements from the stack, 
* peek at the top element without removing it, and free the memory allocated for the stack.
*/
void initializeStack(Stack *stack) {
    stack->top = -1;
}

int isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->data[++stack->top] = value;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

void freestack(Stack* stack){
    while(stack->top > -1){
        pop(stack);
    }
}
#endif