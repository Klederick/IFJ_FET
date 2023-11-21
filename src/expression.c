#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringstack.c"
#include <stdbool.h>

#define TABLE_SIZE 10

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

void add(StringStack* node_stack, StringStack* expr_stack, const char* a, bool E){
    char tmp[MAX_STRING_LENGTH];

    pushString(expr_stack, "<");
    pushString(expr_stack, a);
}
void reduce(StringStack* node_stack, StringStack* expr_stack, const char* a, bool E){

    if (strcmp(a,"+") == 0 || strcmp(a,"-") == 0 || strcmp(a,"*") == 0 || strcmp(a,"/") == 0){
        while(strcmp(peekString(expr_stack), "<") != 0){
            pushString(node_stack, peekString(expr_stack));
            popString(expr_stack);
        }
        eNode *e_node = malloc(sizeof(eNode));
        e_node->left = peekString(node_stack); 
        popString(node_stack);
        e_node->token = peekString(node_stack); 
        popString(node_stack);
        e_node->right = peekString(node_stack);
        popString(node_stack);


        popString(expr_stack);
        pushString(expr_stack, "E");
    }
    else if (strcmp(a,")") == 0){

    }
    else if (strcmp(a, "??") == 0){

    }
    else if (strcmp(a, "$") == 0){

    }
    else{

    }
    
}
void equal(StringStack* expr_stack, const char* a){
    
}
int expression(const char* a){ 
    char tmp[MAX_STRING_LENGTH];
    tmp = NULL;
    char b[MAX_STRING_LENGTH];
    bool E = false;

    ExpressionStack expr_stack;
    initializeExpressionStack(&expr_stack);
    ExpressionStack node_stack;
    initializeExpressionStack(&node_stack);

    ExpressionStack temp_stack;
    initializeExpressionStack(&temp_stack);

    strcpy(b, peekString(&expr_stack));
    
    if(strcmp(b, "E")==0){
        tmp = peekString(&expr_stack);
        popString(&expr_stack);
        strcpy(b, peekString(&expr_stack));
    }

    int positionx = findStringInColumn(a);
    int positiony = findStringInRow(b);
    char* symbol = getStringFromCoordinates(positionx, positiony);

    printf("hledana operace je: %s\n", symbol);
    if(strcmp(symbol, "L") == 0){
        add(&node_stack, &expr_stack, a, E);
    }
    else if(strcmp(symbol, "M") == 0){
        if(tmp != NULL){
            pushString(&expr_stack, tmp);
        }
        reduce(&expr_stack, a, E);
    }
    else if(strcmp(symbol, "Q") == 0){
        equal(&expr_stack, a);
    }
    else{
        fprintf(stderr, "Nespravna kombinacia tokenov ktora vedie k errorovemu stavu\n");
    }

    strcpy(b, peekString(&expr_stack));
    printf("Obsah zásobníku expr_stack:\n");
    while (!isStringStackEmpty(&expr_stack)) {
        char* item = popString(&expr_stack);
        pushString(&temp_stack, item);
    }

    // Vrácení položek zpět na zásobník vstupni_stack
    while (!isStringStackEmpty(&temp_stack)) {
        char* item = popString(&temp_stack);
        printf("%s ", item);
        pushString(&expr_stack, item);
    }
    if(expr_stack.top == 0)
    popToken(&expr_stack);
    return 0;
}


main(){
    char pole[100][100] = {"2", "+", "2", "$"};
    int i = 0;
    while(i < 4){
        expression(pole[i]);
        i++;
    }
}