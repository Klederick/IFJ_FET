#include <stdio.h>
#include <stdlib.h>
#include "stack.c"
#include "struct.h"
#include "scanner.c"

int p_table[9][9]{
  {' ', '+', '-', '*', '/', '^', '(', 'i', ')', '$'},
  {'+', '>', '>', '<', '<', '<', '<', '<', '>', '>'},
  {'-', '>', '>', '<', '<', '<', '<', '<', '>', '>'},
  {'*', '>', '>', '>', '>', '<', '<', '<', '>', '>'},
  {'/', '>', '>', '>', '>', '<', '<', '<', '>', '>'},
  {'^', '>', '>', '>', '>', '<', '<', '<', '>', '>'},
  {'(', '<', '<', '<', '<', '<', '<', '<', '=', ' '},
  {'i', '>', '>', '>', '>', '>', ' ', ' ', '>', '>'},
  {')', '>', '>', '>', '>', '>', ' ', ' ', '>', '>'},
  {'$', '<', '<', '<', '<', '<', '<', '<', ' ', ' '}
}

Stack expr_stack;
initializeStack(&expr_stack);
push(&expr_stack, "$");
while(1){
    // Aktuální vstupní symbol
    char a = vstup[i];

    // Nejvrchnější terminální symbol na zásobníku
    char b = peek($expr_stack);

    if(peek(&expr_stack) == "$"){
        push($expr_expr, "i");
    }
}