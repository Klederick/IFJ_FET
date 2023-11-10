#include <stdio.h>
#include <stdlib.h>
/*STACK.C*/

#ifndef STRUCTS_H
#define STRUCTS_H
#define MAX_SIZE 100

struct Token {
    char ID;
    char *symbol;
    int spacesBehind;
};

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

/*void initializeStack(Stack *stack);

int isFull(Stack *stack);

int isEmpty(Stack *stack);

void push(Stack *stack, int value);

int pop(Stack *stack);

int peek(Stack *stack);*/


/*SYMTABLE.C*/
typedef struct tNode {
    char *key;
    int nodeType;
    int height;
    struct tNode *lptr;
    struct tNode *rptr;
} *tNode_t;

/*
int max(int a, int b);

int height(tNode_t node);

int getBalance(tNode_t node);

tNode_t newNode(char *key, int nodeType);

tNode_t rightRotate(tNode_t y);

tNode_t leftRotate(tNode_t x);

tNode_t insert(tNode_t node, char *key, int nodeType);

tNode_t search(tNode_t node, char *key);

void symtabInsert(tNode_t *tree, char *key, int nodeType);

void symtabInorder(tNode_t tree);

void symtabPostorder(tNode_t tree);

void symtabPreorder(tNode_t tree);

void destroyTree(tNode_t tree);

tNode_t initializeTree();
*/
#endif // STRUCTS_H