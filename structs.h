#include <stdio.h>
#include <stdlib.h>

#ifndef STRUCT.H
#define STRUCT.H


/*STACK.C*/
typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void initializeStack(Stack *stack)

int isFull(Stack *stack)

int isEmpty(Stack *stack)

void push(Stack *stack, int value)

int pop(Stack *stack)

int peek(Stack *stack)