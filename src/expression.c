#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stringstack.c"
#include "error.c"

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

void add(ExpressionStack* expr_stack, struct Token token, struct Token tmp){
    expressionItem less;
    less.value.token.symbol = "<";
    pushE(expr_stack, less);
    pushE(expr_stack, tmp);
    pushE(expr_stack, token);
}
void reduce(ExpressionStack* node_stack, ExpressionStack* expr_stack, struct Token token){
/*
    if (strcmp(token.symbol,"+") == 0 || strcmp(token.symbol,"-") == 0 || strcmp(token.symbol,"*") == 0 || strcmp(token.symbol,"/") == 0){
        
        while(true){
            expressionItem tmp = peekE(expr_stack);
            if(tmp.type == TOKEN && (strcmp(tmp.symbol, "<")==0)){
                popE(expr_stack);


                return;
            }
            else{
                pushE(node_stack, tmp);
                popE(expr_stack);
            }
        }
        eNode *e_node = malloc(sizeof(eNode));
        e_node->left = peekString(node_stack); 
        popString(node_stack);
        e_node->token = peekString(node_stack); 
        popString(node_stack);
        e_node->right = peekString(node_stack);
        popString(node_stack);
    }
    else if (strcmp(a,")") == 0){

    }
    else if (strcmp(a, "??") == 0){

    }
    else if (strcmp(a, "$") == 0){

    }
    else{

    }
 */   
}
void equal(ExpressionStack* expr_stack, const char* a){

}

//ExpressionStack expr_stack;
//initializeExpressionStack(&expr_stack);
//ExpressionStack node_stack;
//initializeExpressionStack(&node_stack);   
//ExpressionStack temp_stack;
//initializeExpressionStack(&temp_stack);

int expression(struct Token token){ 

    expressionItem b = peekE(expr_stack);
    
    if(b.type == NODE){
        expressionItem tmp = peekE(&expr_stack);
        popE(&expr_stack);
        b = peekE(&expr_stack);
        //printf("token b peekE\n%s", token.symbol);
    }

    int positionx = findStringInColumn(token.symbol);
    int positiony = findStringInRow(b.value.token.symbol);
    char* symbol = getStringFromCoordinates(positionx, positiony);

    printf("hledana operace je: %s\n", symbol);
    if(strcmp(symbol, "L") == 0){
        add(&expr_stack, token, tmp);
    }
    else if(strcmp(symbol, "M") == 0){
        if(tmp != NULL){
            pushE(&expr_stack, tmp);
        }
        reduce(&node_stack, &expr_stack, token);
    }
    else if(strcmp(symbol, "Q") == 0){
        equal(&expr_stack, token.symbol);
    }
    else{
        fprintf(stderr, "Nespravna kombinacia tokenov ktora vedie k errorovemu stavu\n");
    }
    /*
    strcpy(b, peekE(&expr_stack));
    printf("Obsah zásobníku expr_stack:\n");
    while (!isExpressionStackEmpty(&expr_stack)) {
        char* item = popE(&expr_stack);
        pushE(&temp_stack, item);
    }

    // Vrácení položek zpět na zásobník vstupni_stack
    while (!isExpressionStackEmpty(&temp_stack)) {
        char* item = popE(&temp_stack);
        printf("%s ", item);
        pushE(&expr_stack, item);
    }*/
    return 0;
}