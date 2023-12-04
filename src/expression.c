#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringstack.c"
#include <stdbool.h>
#include "structs.h"

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
    for (i = 0; i < 10; i++) {
        if (strcmp(a, p_table[0][i]) == 0) { // Porovnání řetězce 'a' s hodnotou v tabulce
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

    // Procházení řádku tabulky
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
    if (strcmp(token.symbol, "(") == 0 || strcmp(token.symbol, ")") == 0) {
        return;
    }

    if (strcmp(token.symbol, "+") == 0 || strcmp(token.symbol, "-") == 0 ||
        strcmp(token.symbol, "*") == 0 || strcmp(token.symbol, "/") == 0 ||
        strcmp(token.symbol, "??") == 0) {
        
        expressionItem less_than_item;
        less_than_item.type = TOKEN;
        less_than_item.value.token.symbol = "<";

        while (1) {
            expressionItem top_item = peekE(expr_stack);

            if (top_item.type == TOKEN && strcmp(top_item.value.token.symbol, "<") == 0) {
                popE(expr_stack);
                break;
            } else {
                pushE(node_stack, top_item);
                popE(expr_stack);
            }
        }

        pushE(expr_stack, less_than_item);

        // Interpretace pravidel a vytváření stromové struktury zde:
        eNode* e_node = malloc(sizeof(eNode));
        e_node->token = token;

        // Pravý potomek
        e_node->right = node_stack->data[node_stack->top - 1].value.e_node;
        popE(node_stack);

        // Levý potomek
        e_node->left = node_stack->data[node_stack->top - 1].value.e_node;
        popE(node_stack);

        expressionItem e_item;
        e_item.type = NODE;
        e_item.value.e_node = e_node;
        pushE(expr_stack, e_item);

    } else if(strcmp(token.symbol, "$") == 0) {  
        while (!isExpressionStackEmpty(expr_stack)) {
            expressionItem top_item = peekE(expr_stack);

            if (top_item.type == TOKEN && strcmp(top_item.value.token.symbol, "<") == 0) {
                popE(expr_stack);
            } else {
                pushE(node_stack, top_item);
                popE(expr_stack);
            }
        }

        eNode* e_node = malloc(sizeof(eNode));
        e_node->token = token;
        e_node->right = node_stack->data[node_stack->top - 1].value.e_node;
        popE(node_stack);
        e_node->left = node_stack->data[node_stack->top - 1].value.e_node;
        popE(node_stack);

        expressionItem e_item;
        e_item.type = NODE;
        e_item.value.e_node = e_node;
        pushE(expr_stack, e_item);
    } else {
        // Jiné tokeny (např. identifikátory nebo čísla) prostě přidá na zásobník.
        expressionItem e_item;
        e_item.type = NODE;

        eNode* e_node = malloc(sizeof(eNode));
        e_node->token = token;
        e_node->left = NULL;
        e_node->right = NULL;

        e_item.value.e_node = e_node;
        pushE(expr_stack, e_item);
    }
}


void equal(ExpressionStack* expr_stack, struct Token token) {
    expressionItem token_item;
    token_item.type = TOKEN;
    token_item.value.token = token;
    
    pushE(expr_stack, token_item);
}

int expression(struct Token token){ 
    ExpressionStack expr_stack;
    initializeExpressionStack(&expr_stack);
    ExpressionStack node_stack;
    initializeExpressionStack(&node_stack);   
    ExpressionStack temp_stack;
    initializeExpressionStack(&temp_stack);

    expressionItem b;
    expressionItem tmp;
    if(isExpressionStackEmpty(&expr_stack)){
        struct Token dollar_token;
        dollar_token.ID = 14; // ID může být libovolné, co odpovídá typu tokenu
        dollar_token.symbol = "$";
        dollar_token.spacesBehind = 0; // nastavíme podle potřeby

        b.type = TOKEN;
        b.value.token = dollar_token;
        pushE(&expr_stack, b);
    }
    b = peekE(&expr_stack);
    
    if(b.type == NODE){
        tmp = peekE(&expr_stack);
        popE(&expr_stack);
        b = peekE(&expr_stack);
    }

    int positionx = findStringInColumn(token.symbol);
    int positiony = findStringInRow(b.value.token.symbol);
    char* symbol = getStringFromCoordinates(positionx, positiony);

    printf("hledana operace je: %s\n", symbol);
    if(strcmp(symbol, "L") == 0){
        add(&expr_stack, token, tmp);
    }
    else if(strcmp(symbol, "M") == 0){
        if(tmp.type == NODE){
            pushE(&expr_stack, tmp);
        }
        reduce(&node_stack, &expr_stack, token);
    }
    else if(strcmp(symbol, "Q") == 0){
        equal(&expr_stack, token);
    }
    else{
        fprintf(stderr, "Nespravna kombinacia tokenov ktora vedie k errorovemu stavu\n");
    }
    return 0;
}