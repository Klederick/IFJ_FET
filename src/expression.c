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
...
var i : (E == E)
i = 1
i - E -> E op E
if((i == 1) == (a == 2))
*/
char* najdi_pravidlo(Stack* expr_stack) {
    char b = peek(expr_stack);
    switch (b) {
        case '+':
            return "E+E";
        case '-':
            return "E-E";
        case '*':
            return "E*E";
        case '/':
            return "E/E";
        case '^':
            return "E^E";
        case '(':
            return "(E)";
        default:
            return "i";
    }
}

void LESS(Stack* expr_stack, char a) {
    // Najdi na zásobníku nejvrchnější terminální symbol-b
    char b;
    while (!isEmpty(expr_stack)) {
        b = pop(expr_stack);
        if (b == '+' || b == '-' || b == '*' || b == '/' || b == '^' || b == '(') {
            break;
        }
    }

    // Hned za symbol-b vlož do zásobníku symbol <
    push(expr_stack, '<');

    // Předti symbol 'a' ze vstupu a dej jej na vrchol zásobníku
    push(expr_stack, a);
}

MORE(a, b){

}

EQUA(a, b){

}
ERRR(a, b){
    
}


int main() {
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
            fprintf(stderr,"Znak z expression nie je validny") //error vypis ak nenajdem znak v tabulke
        }

        
        
    }
}
