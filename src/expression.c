#ifndef EXPRESSION_C
#define EXPRESSION_C
//  include
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringstack.c"
#include <stdbool.h>
#include "structs.h"
#include <ctype.h>

#define TABLE_SIZE 10
#define MAX_STRING_LENGTH 100
// pravidla 
/*
1 - E -> E + E
2 - E -> E - E
3 - E -> E * E
4 - E -> E / E
5 - E -> (E)
6 - E -> i
7 - E -> E ?? E
*/

char* p_table[10][10] = {
    {"x", "+", "-", "*", "/", "(", "i", ")", "$", "??"},
    {"+", "M", "M", "L", "L", "L", "L", "M", "M", "M"}, //"+", 
    {"-", "M", "M", "L", "L", "L", "L", "M", "M", "M"}, //"-", 
    {"*", "M", "M", "M", "M", "L", "L", "M", "M", "M"}, //"*", 
    {"/", "M", "M", "M", "M", "L", "L", "M", "M", "M"}, //"/", 
    {"(", "L", "L", "L", "L", "L", "L", "Q", "R", "L"}, //"(", 
    {"i", "M", "M", "M", "M", "R", "R", "M", "M", "M"}, //"i", 
    {")", "M", "M", "M", "M", "R", "R", "M", "M", "M"}, //")", 
    {"$", "L", "L", "L", "L", "L", "L", "R", "R", "L"}, //"$", 
    {"??","L", "L", "L", "L", "L", "L", "R", "M", "L"} //"??",
}; 

int findStringInColumn(const char* a) {
    int i, found = 0;

    // Procházení prvního řádku tabulky
    if((isdigit(a[0]) || isalpha(a[0]))){
        a = "i";
    }
    for (i = 0; i < 10; i++) {
        if (strcmp(a, p_table[0][i]) == 0){ // Porovnání řetězce 'a' s hodnotou v tabulce
            printf("příchozí je '%s' at position [%d][%d] in p_table\n", a, 0, i);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("příchozí String '%s' not found in p_table\n", a);
    }
    return i;
}

int findStringInRow(const char* b) {
    int i, found = 0;

    // Procházení prvního řádku tabulky
    if((isdigit(b[0]) || isalpha(b[0]))){
        b = "i";
    }
    for (i = 0; i < 10; i++) {
        if (strcmp(b, p_table[i][0]) == 0) { // Porovnání řetězce 'a' s hodnotou v tabulce
            printf("na expr je '%s' at position [%d][%d] in p_table\n", b, i, 0);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("String '%s' not found in row of p_table\n", b);
    }
    return i;
}

char* getStringFromCoordinates(int col, int row) {
    if (row >= 0 && row < 16 && col >= 0 && col < 16) { // Zkontrolování platných souřadnic
        return p_table[row][col]; // Vrácení řetězce na dané souřadnici
    } else {
        return NULL; // Neplatné souřadnice
    }
}
void add(ExpressionStack* expr_stack, struct Token token, expressionItem tmp) {
    expressionItem less_than;
    less_than.type = TOKEN;
    less_than.value.token.symbol = "<";
    
    expressionItem token_item;
    token_item.type = TOKEN;
    token_item.value.token = token;
    pushE(expr_stack, less_than);
    
    if(tmp.type == NODE) {
        pushE(expr_stack, tmp);
        pushE(expr_stack, token_item);
    } else {
        pushE(expr_stack, token_item);
    }
}

void reduce(ExpressionStack* node_stack, ExpressionStack* expr_stack, struct Token token) {
    expressionItem check;
    check = peekE(expr_stack);

    if(peekE(expr_stack).type == TOKEN){
        printf("TOTO je check %s\n", peekE(expr_stack).value.token.symbol);
    }
    else{
        printf("toto je check NODE\n");

    }
    while (check.type != TOKEN || strcmp(check.value.token.symbol, "<") != 0) {
        printf("toto je check ve while: %s\n", check.value.token.symbol);
        pushE(node_stack, check);
        popE(expr_stack);
        check = peekE(expr_stack);
    }
    printf("toto je check za while: %s\n", check.value.token.symbol);
    printf("vrchol node_stacku: %d\n", node_stack->top);
    if(node_stack->top == 0){
        expressionItem peek;
        peek = peekE(node_stack);
        eNode* e_node = malloc(sizeof(eNode));
        expressionItem node;
        printf("cokoliv\n");
        e_node->token= peek.value.token;
        e_node->right = NULL;
        e_node->left = NULL;
        node.value.e_node = e_node;
        node.type = NODE;
        popE(expr_stack);
        pushE(expr_stack, node);
        if(peekE(expr_stack).type == TOKEN){
            printf("dolar?? %s\n", peekE(expr_stack).value.token.symbol);
        }
        else{
            printf("dolar?? NODE\n");
        }
    }
    else if(node_stack->top == 2){
        expressionItem E;
        E = peekE(node_stack);
        if(E.type == NODE){
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
        else{
            expressionItem peek1;
            popE(node_stack);
            peek1 = peekE(node_stack);
            popE(node_stack);
            popE(node_stack);            
            popE(expr_stack);
            pushE(expr_stack, peek1);
        }
    }
    else{
        printf("CHYBA");
    }
    while(node_stack->top != -1){
        popE(node_stack);
    }
    if(peekE(expr_stack).type == TOKEN){
            printf("toto je za reduce %s\n", peekE(expr_stack).value.token.symbol);
        }
        else{
            printf("´toto je za reduce NODE\n");
        }
    printf("toto je top node_stacku: %d\n", node_stack->top);
}

void equal(ExpressionStack* expr_stack, struct Token token) {
    expressionItem token_item;
    token_item.type = TOKEN;
    token_item.value.token = token;
    
    pushE(expr_stack, token_item);
}

eNode* expression(ExpressionStack* expr_stack, ExpressionStack* node_stack, struct Token token) { 
    printf("\n\n\n");
    ExpressionStack temp_stack;
    initializeExpressionStack(&temp_stack);

    expressionItem b;
    expressionItem tmp;
        // Porovnání vstupního tokenu s vrcholem zásobníku
    /*if (expr_stack->top >= 1 && expr_stack->data[expr_stack->top].value.token.symbol[0] == 'E' && expr_stack->data[expr_stack->top - 1].value.token.symbol[0] == '$') {
        return expr_stack->data[expr_stack->top].value.e_node;
        //printf("KONEC\n\n");
    } else {
        return NULL;
    }*/

    if(isExpressionStackEmpty(expr_stack)){
        struct Token dollar_token;
        dollar_token.ID = 14; // ID může být libovolné, co odpovídá typu tokenu
        dollar_token.symbol = "$";
        dollar_token.spacesBehind = 0; // nastavíme podle potřeby

        b.type = TOKEN;
        b.value.token = dollar_token;
        pushE(expr_stack, b);
    }
    b = peekE(expr_stack);
    
    if(b.type == NODE){
        tmp = peekE(expr_stack);
        popE(expr_stack);
        b = peekE(expr_stack);
    }
    else{
        b.type = TOKEN;
    }
    printf("%s toto je na expr vrchol\n", b.value.token.symbol);
    int positionx = findStringInColumn(token.symbol);
    int positiony = findStringInRow(b.value.token.symbol);
    if(strcmp(token.symbol, b.value.token.symbol) == 0){
        printf("KONEC\n\n\n\n\n");
    }
    char* symbol = getStringFromCoordinates(positionx, positiony);

    printf("hledana operace je: %s\n", symbol);
    if(strcmp(symbol, "L") == 0){
        add(expr_stack, token, tmp);
    }
    else if(strcmp(symbol, "M") == 0){
        if(tmp.type == NODE){
            pushE(expr_stack, tmp);
        }
        reduce(node_stack, expr_stack, token);
        expression(expr_stack, node_stack, token);
    }
    else if(strcmp(symbol, "Q") == 0){
        if(tmp.type == NODE){
            pushE(expr_stack, tmp);
        }
        equal(expr_stack, token);
    }
    else{
        fprintf(stderr, "Nespravna kombinacia tokenov ktora vedie k errorovemu stavu\n");
    }

    // Uložení obsahu expr_stack do temp_stack
    while (!isExpressionStackEmpty(expr_stack)) {
        pushE(&temp_stack, peekE(expr_stack));
        popE(expr_stack);
    }

    // Vypíše obsah temp_stack a vrátí data zpět do expr_stack
    printf("Obsah expr_stack na konci funkce expression:\n");
    while (!isExpressionStackEmpty(&temp_stack)) {
        expressionItem item = peekE(&temp_stack);
        if (item.type == TOKEN) {
            printf("Token na expr: %s\n", item.value.token.symbol);
        } else {
            printf("Node E\n");
        }
        pushE(expr_stack, item);
        popE(&temp_stack);
    }
    printf("\n\n\n");
    return 0;
}
#endif