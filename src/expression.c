#include <stdio.h>
#include <stdlib.h>
#include "stack.c"
#include "structs.h"
#include <string.h>
int TABLE_SIZE = 15;
int p_table[15][15] = {
  //{'+'   , '-'   , '*'   , '/'   , '('   , 'i'   , ')'   , '$'   , '=='  , '<='   , '>='   , '>'    , '!='  , '<'    , '??'  },
    {'MORE', 'MORE', 'LESS', 'LESS', 'LESS', 'LESS', 'MORE', 'MORE', 'MORE', 'MORE' , 'MORE' , 'MORE' , 'MORE', 'MORE' , 'MORE'}, //'+', 
    {'MORE', 'MORE', 'LESS', 'LESS', 'LESS', 'LESS', 'MORE', 'MORE', 'MORE', 'MORE' , 'MORE' , 'MORE' , 'MORE', 'MORE' , 'MORE'}, //'-', 
    {'MORE', 'MORE', 'MORE', 'MORE', 'LESS', 'LESS', 'MORE', 'MORE', 'MORE', 'MORE' , 'MORE' , 'MORE' , 'MORE', 'MORE' , 'MORE'}, //'*', 
    {'MORE', 'MORE', 'MORE', 'MORE', 'LESS', 'LESS', 'MORE', 'MORE', 'MORE', 'MORE' , 'MORE' , 'MORE' , 'MORE', 'MORE' , 'MORE'}, //'/', 
    {'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'EQUA', 'ERRR', 'LESS', 'LESS' , 'LESS' , 'LESS' , 'LESS', 'LESS' , 'LESS'}, //'(', 
    {'MORE', 'MORE', 'MORE', 'MORE', 'ERRR', 'ERRR', 'MORE', 'MORE', 'MORE', 'MORE' , 'MORE' , 'MORE' , 'MORE', 'MORE' , 'MORE'}, //'i', 
    {'MORE', 'MORE', 'MORE', 'MORE', 'ERRR', 'ERRR', 'MORE', 'MORE', 'MORE', 'MORE' , 'MORE' , 'MORE' , 'MORE', 'MORE' , 'MORE'}, //')', 
    {'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'ERRR', 'ERRR', 'LESS', 'LESS' , 'LESS' , 'LESS' , 'LESS', 'LESS' , 'LESS'}, //'$', 
    {'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'MORE', 'MORE', 'MORE', 'MORE' , 'MORE' , 'MORE' , 'MORE', 'MORE' , 'MORE'}, //'==',
    {'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'MORE', 'MORE', 'MORE', 'MORE' , 'MORE' , 'MORE' , 'MORE', 'MORE' , 'MORE'}, //'<=',
    {'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'MORE', 'MORE', 'MORE', 'MORE' , 'MORE' , 'MORE' , 'MORE', 'MORE' , 'MORE'}, //'>=',
    {'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'MORE', 'MORE', 'MORE', 'MORE' , 'MORE' , 'MORE' , 'MORE', 'MORE' , 'MORE'}, //'>', 
    {'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'MORE', 'MORE', 'MORE', 'MORE' , 'MORE' , 'MORE' , 'MORE', 'MORE' , 'MORE'}, //'!=',
    {'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'MORE', 'MORE', 'MORE', 'MORE' , 'MORE' , 'MORE' , 'MORE', 'MORE' , 'MORE'}, //'<', 
    {'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'LESS', 'MORE', 'MORE', 'LESS', 'LESS' , 'LESS' , 'LESS' , 'LESS', 'LESS' , 'LESS'} //'??',
};
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
9- E -> E <= E
10- E -> E >= E
11- E -> E != E 
12- E -> E < E
13- E -> E > E 
...
var i : (E == E)
i = 1
i - E -> E op E
if((i == 1) == (a == 2))
*/

void LESS(Stack* expr_stack, char a) {
    push(expr_stack, '<');
    push(expr_stack, a);
}

void MORE(Stack* expr_stack, char a, bool express, char symbol) {
    if (express) {
        switch (symbol) {
            case '+':
                pop(expr_stack);
                pop(expr_stack);
                pop(expr_stack);
                pop(expr_stack);
                printf("Redukce podle pravidla 1\n");
                push(expr_stack, 'E');
                break;

            case '-':
                pop(expr_stack);
                printf("Redukce podle pravidla 2\n");
                push(expr_stack, 'E');
                break;

            case '*':
                printf("Redukce podle pravidla 3\n");
                push(expr_stack, 'E');
            case '/':
                printf("Redukce podle pravidla 4\n");
                push(expr_stack, 'E');
            case '()':
                printf("Redukce podle pravidla 5\n");
                push(expr_stack, 'E');
            case 'i':
                printf("Redukce podle pravidla 6\n");
                push(expr_stack, 'E');
            case '??':
                printf("Redukce podle pravidla 7\n");   
                push(expr_stack, 'E');
            case '==':
                printf("Redukce podle pravidla 8\n");
                push(expr_stack, 'E');
            case '<=':
                printf("Redukce podle pravidla 9\n");
                push(expr_stack, 'E');
            case '>=':
                printf("Redukce podle pravidla 10\n");
                push(expr_stack, 'E');
            case '!=':
                printf("Redukce podle pravidla 11\n");
                push(expr_stack, 'E');
            case '<':
                printf("Redukce podle pravidla 12\n");
                push(expr_stack, 'E');
            case '>':
                printf("Redukce podle pravidla 13\n");
                push(expr_stack, 'E');
            default:
                printf("nebylo nalezeno pravidlo")
        }
    }
}

void EQUA(Stack* expr_stack, char a) {
    push(expr_stack, a);
}

void ERRR(a, b){
 //syntax err   
}


int main() {
    bool express = false
    Stack expr_stack;
    initializeStack(&expr_stack);
    push(&expr_stack, '$'); // Change: push character instead of string

    Stack vstupni_stack;
    initializeStack(&vstupni_stack);
    push(&vstupni_stack, 'i'); // Change: push character instead of string
    push(&vstupni_stack, '^');
    push(&vstupni_stack, ')');
    push(&vstupni_stack, 'i'); // Change: push character instead of string
    push(&vstupni_stack, '*');
    push(&vstupni_stack, 'i'); // Change: push character instead of string
    push(&vstupni_stack, '(');

    while (!isEmpty(&vstupni_stack)) {
        char a = peek(&vstupni_stack);
        char b = peek(&expr_stack);
        if (b == 'E'){
            pop(&expr_stack);
            b = peek(&expr_stack);
            push(&expr_stack, 'E');
            express = true;
        }
        
        int surx = -1; int sury = -1;
        
        for(int i = 0; i < TABLE_SIZE; i++){
            if(strcmp(p_table[0][i],a)){
                surx = i;
            }
        }

        for(int i = 0; i < TABLE_SIZE; i++){
            if(strcmp(p_table[0][i],b)){
                sury = i;
            }
        }

        if((sury == -1) || (surx == -1)){
            fprintf(stderr,"Znak z expression nie je validny"); //error vypis ak nenajdem znak v tabulke
        }
        switch(p_table[surx][sury]){
            case 'MORE': MORE(expr_stack, a, express, b); break;
            case 'LESS': LESS(expr_stack, a); break;
            case 'EQUA': EQUA(expr_stack, a); break;
            case 'ERRR': fprintf(stderr,"Nespravna kombinacia tokenov ktora vedie k errorovemu stavu"); break; //error vypis ak nenajdem znak v tabulke
        }
        
        
    }
}
