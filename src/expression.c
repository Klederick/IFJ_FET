#ifndef EXPRESSION_C
#define EXPRESSION_C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringstack.c"
#include <stdbool.h>
#include "structs.h"
#include <ctype.h>
#include "error.c"

#define TABLE_SIZE 10
#define MAX_STRING_LENGTH 100

eNode* expression(ExpressionStack* expr_stack, ExpressionStack* node_stack, struct Token token);

char* p_table[10][10] = {
    {"x", "+", "-", "*", "/", "(", "i", ")", "$", "??"},
    {"+", "M", "M", "L", "L", "L", "L", "M", "M", "M"}, //"+", 
    {"-", "M", "M", "L", "L", "L", "L", "M", "M", "M"}, //"-", 
    {"*", "M", "M", "M", "M", "L", "L", "M", "M", "M"}, //"", 
    {"/", "M", "M", "M", "M", "L", "L", "M", "M", "M"}, //"/", 
    {"(", "L", "L", "L", "L", "L", "L", "Q", "R", "L"}, //"(", 
    {"i", "M", "M", "M", "M", "R", "R", "M", "M", "M"}, //"i", 
    {")", "M", "M", "M", "M", "R", "R", "M", "M", "M"}, //")", 
    {"$", "L", "L", "L", "L", "L", "L", "R", "R", "L"}, //"$", 
    {"??","L", "L", "L", "L", "L", "L", "R", "M", "L"} //"??",
};

int findStringInColumn(const char* a) {
    int i, found = 0;

    if ((isdigit(a[0]) || isalpha(a[0]))) {
        a = "i";
    }
    for (i = 0; i < 10; i++) {
        if (strcmp(a, p_table[0][i]) == 0) {
            found = 1;
            break;
        }
    }
    return i;
}

int findStringInRow(const char* b) {
    int i, found = 0;

    if ((isdigit(b[0]) || isalpha(b[0]))) {
        b = "i";
    }
    for (i = 0; i < 10; i++) {
        if (strcmp(b, p_table[i][0]) == 0) {
            found = 1;
            break;
        }
    }
    return i;
}

char* getStringFromCoordinates(int col, int row) {
    if (row >= 0 && row < 16 && col >= 0 && col < 16) {
        return p_table[row][col];
    }
    else {
        return NULL;
    }
}
void add(ExpressionStack* expr_stack, struct Token token, expressionItem tmp, ExpressionStack* temp_stack) {
    expressionItem less_than;
    less_than.type = TOKEN;
    less_than.value.token.symbol = "<";

    expressionItem token_item;
    token_item.type = TOKEN;
    token_item.value.token = token;
    pushE(expr_stack, less_than);

    if (tmp.type == NODE) { 
        pushE(expr_stack, tmp);
        pushE(expr_stack, token_item);
    }
    else {
        pushE(expr_stack, token_item);
    }
}


void reduce(ExpressionStack* node_stack, ExpressionStack* expr_stack, struct Token token) {
    expressionItem check;
    check = peekE(expr_stack);

    while (check.type != TOKEN || strcmp(check.value.token.symbol, "<") != 0) {
        pushE(node_stack, check);
        popE(expr_stack);
        check = peekE(expr_stack);
    }
    if (node_stack->top == 0) {
        expressionItem peek;
        peek = peekE(node_stack);
        eNode* e_node = malloc(sizeof(eNode));
        expressionItem node;
        e_node->token = peek.value.token;
        e_node->right = NULL;
        e_node->left = NULL;
        node.value.e_node = e_node;
        node.type = NODE;
        popE(expr_stack);
        pushE(expr_stack, node);
    }
    else if (node_stack->top == 2) {
        expressionItem E;
        E = peekE(node_stack);
        if (E.type == NODE) {
            expressionItem peek1;
            expressionItem peek2;
            expressionItem peek3;
            expressionItem node;
            peek1 = peekE(node_stack);
            popE(node_stack);
            peek2 = peekE(node_stack);
            popE(node_stack);
            peek3 = peekE(node_stack);
            eNode* e_node = malloc(sizeof(eNode));
            e_node->token = peek2.value.token;
            e_node->right = peek3.value.e_node;
            e_node->left = peek1.value.e_node;
            node.value.e_node = e_node;
            node.type = NODE;
            popE(expr_stack);
            pushE(expr_stack, node);
        }
        else {
            expressionItem peek1;
            popE(node_stack);
            peek1 = peekE(node_stack);
            popE(node_stack);
            popE(node_stack);
            popE(expr_stack);
            pushE(expr_stack, peek1);
        }
    }
    else {
        ThrowError(2);
    }
    while (node_stack->top != -1) {
        popE(node_stack);
    }
    expression(expr_stack, node_stack, token);
}

void equal(ExpressionStack* expr_stack, struct Token token) {
    expressionItem token_item;
    token_item.type = TOKEN;
    token_item.value.token = token;

    pushE(expr_stack, token_item);
}

eNode* expression(ExpressionStack* expr_stack, ExpressionStack* node_stack, struct Token token) {

    ExpressionStack temp_stack;
    initializeExpressionStack(&temp_stack);

    expressionItem b;
    expressionItem tmp;
    if (isExpressionStackEmpty(expr_stack)) {
        struct Token dollar_token;
        dollar_token.ID = 14;
        dollar_token.symbol = "$";
        dollar_token.spacesBehind = 0;

        b.type = TOKEN;
        b.value.token = dollar_token;
        pushE(expr_stack, b);
    }
    b = peekE(expr_stack);

    if (b.type == NODE) {
        tmp = peekE(expr_stack);
        popE(expr_stack);
        b = peekE(expr_stack);
    }
    else {
        b.type = TOKEN;
    }

    int positionx = findStringInColumn(token.symbol);
    int positiony = findStringInRow(b.value.token.symbol);
    if (strcmp(token.symbol, "$") == 0 && strcmp(b.value.token.symbol, "$") == 0) {
        pushE(expr_stack, tmp);
        eNode* root = expr_stack->data[expr_stack->top].value.e_node;
        return expr_stack->data[expr_stack->top].value.e_node;
    }
    char* symbol = getStringFromCoordinates(positionx, positiony);

    if (strcmp(symbol, "L") == 0) {
        add(expr_stack, token, tmp, &temp_stack);
    }
    else if (strcmp(symbol, "M") == 0) {
        if (tmp.type == NODE) {
            pushE(expr_stack, tmp);
        }
        reduce(node_stack, expr_stack, token);
    }
    else if (strcmp(symbol, "Q") == 0) {
        if (tmp.type == NODE) {
            pushE(expr_stack, tmp);
        }
        equal(expr_stack, token);
    }
    else {
        ThrowError(2);
    }
    return 0;
}
#endif