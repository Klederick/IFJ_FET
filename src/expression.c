
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringstack.c"
#include <stdbool.h>

#define TABLE_SIZE 16

// pravidla 
/*
1 - E -> E + E
2 - E -> E - E
3 - E -> E * E
4 - E -> E / E
5 - E -> (E)
6 - E -> i
7 - E -> E ?? E
8 - E -> E == E
9 - E -> E <= E
10 - E -> E >= E
11 - E -> E != E 
12 - E -> E < E
13 - E -> E > E 
*/

char* p_table[16][16] = {
    {"x", "+", "-", "*", "/", "(", "i", ")", "$", "==", "<=", ">=", ">", "!=", "<", "??"},
    {"+", "M", "M", "L", "L", "L", "L", "M", "M", "M", "M" , "M" , "M" , "M", "M" , "M"}, //"+", 
    {"-", "M", "M", "L", "L", "L", "L", "M", "M", "M", "M" , "M" , "M" , "M", "M" , "M"}, //"-", 
    {"*", "M", "M", "M", "M", "L", "L", "M", "M", "M", "M" , "M" , "M" , "M", "M" , "M"}, //"*", 
    {"/", "M", "M", "M", "M", "L", "L", "M", "M", "M", "M" , "M" , "M" , "M", "M" , "M"}, //"/", 
    {"(", "L", "L", "L", "L", "L", "L", "Q", "R", "L", "L" , "L" , "L" , "L", "L" , "L"}, //"(", 
    {"i", "M", "M", "M", "M", "R", "R", "M", "M", "M", "M" , "M" , "M" , "M", "M" , "M"}, //"i", 
    {")", "M", "M", "M", "M", "R", "R", "M", "M", "M", "M" , "M" , "M" , "M", "M" , "M"}, //")", 
    {"$", "L", "L", "L", "L", "L", "L", "R", "R", "L", "L" , "L" , "L" , "L", "L" , "L"}, //"$", 
    {"==","L", "L", "L", "L", "L", "L", "M", "M", "M", "M" , "M" , "M" , "M", "M" , "M"}, //"==",
    {"<=","L", "L", "L", "L", "L", "L", "M", "M", "M", "M" , "M" , "M" , "M", "M" , "M"}, //"<=",
    {">=","L", "L", "L", "L", "L", "L", "M", "M", "M", "M" , "M" , "M" , "M", "M" , "M"}, //">=",
    {">", "L", "L", "L", "L", "L", "L", "M", "M", "M", "M" , "M" , "M" , "M", "M" , "M"}, //">", 
    {"!=","L", "L", "L", "L", "L", "L", "M", "M", "M", "M" , "M" , "M" , "M", "M" , "M"}, //"!=",
    {"<", "L", "L", "L", "L", "L", "L", "M", "M", "M", "M" , "M" , "M" , "M", "M" , "M"}, //"<", 
    {"??","L", "L", "L", "L", "L", "L", "M", "M", "L", "L" , "L" , "L" , "L", "L" , "L"} //"??",
}; 

int findStringInColumn(const char* a) {
    int i, found = 0;

    // Procházení prvního řádku tabulky
    for (i = 0; i < 16; i++) {
        if (strcmp(a, p_table[0][i]) == 0) { // Porovnání řetězce 'a' s hodnotou v tabulce
            printf("příchozí je '%s' at position [%d][%d] in p_table\n", a, 0, i);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("příchozí String '%s' not found in p_table\n", a);
        // return string ....
    }
    return i;
}

int findStringInRow(const char* b) {
    int i, found = 0;

    // Procházení řádku tabulky
    for (i = 0; i < 16; i++) {
        if (strcmp(b, p_table[i][0]) == 0) { // Porovnání řetězce 'a' s hodnotou v tabulce
            printf("na expr je '%s' at position [%d][%d] in p_table\n", b, i, 0);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("String '%s' not found in row of p_table\n", b);
        // return string ....
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

void add(StringStack* expr_stack, const char* a, bool E){
    if(E){
        printf("mame ecko\n");
        popString(expr_stack);
        pushString(expr_stack, "<");
        pushString(expr_stack, "E");
        pushString(expr_stack, a);
    }
    else{
        pushString(expr_stack, "<");
        pushString(expr_stack, a);
    }
}
void reduce(StringStack* expr_stack, const char* a, bool E, StringStack* vstupni_stack){
    char b[MAX_STRING_LENGTH];
    char c[MAX_STRING_LENGTH];
    if (strcmp(a,"+") == 0 || strcmp(a,"-") == 0 || strcmp(a,"*") == 0 || strcmp(a,"/") == 0){
        if(E){
            popString(expr_stack);
            popString(expr_stack);
            popString(expr_stack);
            popString(expr_stack);
        }
        else{
            popString(expr_stack);
            popString(expr_stack);
        }
        printf("Redukce podle pravidla 1-4\n");
        pushString(expr_stack, "E");   
    }
    else if (strcmp(a,")") == 0){
        // Check for "("
        if(E){
            printf("MAME TU ECKO\n");

            strcpy(c, peekString(expr_stack));
            popString(expr_stack);

            if (strcmp(c,"(") != 0) {
                printf("Chybi zavorka\n");
            }
            popString(expr_stack);
            popString(expr_stack);
            printf("Redukce podle pravidla 5\n");
            pushString(expr_stack, "E");
            popString(vstupni_stack);
        }
        else{
            popString(expr_stack);
            popString(expr_stack);
            pushString(expr_stack, "E");
        }
    }
    else if (strcmp(a, "??") == 0 || strcmp(a, "==") == 0 || strcmp(a, "<=") == 0 || strcmp(a,">=") == 0 || strcmp(a, "!=") == 0 || strcmp(a, ">") == 0 || (strcmp(a,"<") == 0)){
        popString(expr_stack);
        popString(expr_stack);
        popString(expr_stack);
        popString(expr_stack);
        printf("Redukce podle pravidla nekolik 6-12\n");
        pushString(expr_stack, "E");
    }
    else if (strcmp(a, "$") == 0){
        if(E){
            popString(expr_stack);
            popString(expr_stack);
            popString(expr_stack);
            popString(expr_stack);

            pushString(expr_stack, "E");
        }
        else{
            popString(expr_stack);
            popString(expr_stack);
            pushString(expr_stack, "E");
            printf("posledni");
        }
    }
    else{
        popString(expr_stack);
        printf("Redukce podle pravidla 6\n");
        pushString(expr_stack, "E");

    }
}
void equal(StringStack* expr_stack, const char* a){
    pushString(expr_stack, a);
}
int main() {
    bool E = false;
    StringStack expr_stack;
    initializeStringStack(&expr_stack);
    pushString(&expr_stack, "$"); // Change: push character instead of string

    StringStack vstupni_stack;
    initializeStringStack(&vstupni_stack);

    // Vložení expression "(i*i)+i" na zásobník
    pushString(&vstupni_stack, "$");
    pushString(&vstupni_stack, "i");
    pushString(&vstupni_stack, "+");
    pushString(&vstupni_stack, ")");
    pushString(&vstupni_stack, "i");
    pushString(&vstupni_stack, "*");
    pushString(&vstupni_stack, "i");
    pushString(&vstupni_stack, "(");

    StringStack temp_stack;
    initializeStringStack(&temp_stack);
    /*
    printf("Top element: %s\n", peekString(&vstupni_stack));
    printf("Popped element: %s\n", popString(&vstupni_stack));
    printf("Popped element: %s\n", popString(&vstupni_stack));

    printf("Is string stack empty? %s\n", isStringStackEmpty(&vstupni_stack) ? "Yes" : "No");
    */
    char b[MAX_STRING_LENGTH];
    strcpy(b, peekString(&expr_stack));

    if(strcmp(b, "$") == 0){
        while(!isStringStackEmpty(&vstupni_stack)){
            E = false;
            char c[MAX_STRING_LENGTH];
            char a[MAX_STRING_LENGTH];
            strcpy(a, peekString(&vstupni_stack));
            char b[MAX_STRING_LENGTH];
            strcpy(b, peekString(&expr_stack));
            if(strcmp(a, "$") == 0){
                popString(&expr_stack);
                strcpy(c, peekString(&expr_stack));
                if(strcmp(c, "$") == 0){
                    //printf("konec expression");
                    break;
                }
                pushString(&expr_stack, c);
            }
            if(strcmp(b, "E") == 0){
                E = true;
                strcpy(c, peekString(&expr_stack));
                popString(&expr_stack);
                strcpy(b, peekString(&expr_stack));
                pushString(&expr_stack, c);
                if (strcmp(b,"+") == 0 || strcmp(b,"-") == 0 || strcmp(b,"*") == 0 || strcmp(b,"/") == 0){
                    reduce(&expr_stack, b, E, &vstupni_stack);
                    printf("BLLBBL\n");            
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
                    printf("\n");
                    printf("BLLBBL\n\n");            
                }
            }
            int positionx = findStringInColumn(a);
            int positiony = findStringInRow(b);
            char* symbol = getStringFromCoordinates(positionx, positiony);

            printf("hledana operace je: %s\n", symbol);

            if(strcmp(symbol, "L") == 0){
                popString(&vstupni_stack);
                printf("popnul jsem vstupni stack\n");
                add(&expr_stack, a, E);
            }
            else if(strcmp(symbol, "M") == 0){
                reduce(&expr_stack, a, E, &vstupni_stack);
            }
            else if(strcmp(symbol, "Q") == 0){
                equal(&expr_stack, a);
            }
            else{
                fprintf(stderr, "Nespravna kombinacia tokenov ktora vedie k errorovemu stavu\n");
                
                break;
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
            
            strcpy(a, peekString(&vstupni_stack));
            printf("\nObsah zásobníku vstupni_stackX:  %s\n", a);
            printf("\n\n");
        }
    }
    return 0;
}
