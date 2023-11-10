#include <stdio.h>
#include <stdlib.h>
#include "stack.c"
#include "structs.h"

int p_table[10][10] = {
    {' ', '+', '-', '*', '/', '^', '(', 'i', ')', '$'},
    {'+', '>', '>', '<', '<', '<', '<', '<', '>', '>'},
    {'-', '>', '>', '<', '<', '<', '<', '<', '>', '>'},
    {'*', '>', '>', '>', '>', '<', '<', '<', '>', '>'},
    {'/', '>', '>', '>', '>', '<', '<', '<', '>', '>'},
    {'^', '>', '>', '>', '>', '<', '<', '<', '>', '>'},
    {'(', '<', '<', '<', '<', '<', '<', '<', '=', 'E'},
    {'i', '>', '>', '>', '>', '>', 'E', 'E', '>', '>'},
    {')', '>', '>', '>', '>', '>', 'E', 'E', '>', '>'},
    {'$', '<', '<', '<', '<', '<', '<', '<', 'E', 'E'}
};

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

int main() {
    Stack expr_stack;
    initializeStack(&expr_stack);
    push(&expr_stack, '$'); // Change: push character instead of string

    Stack vstupni_stack;
    initializeStack(&vstupni_stack);
    push(&vstupni_stack, '(');
    push(&vstupni_stack, 'i'); // Change: push character instead of string
    push(&vstupni_stack, '*');
    push(&vstupni_stack, 'i'); // Change: push character instead of string
    push(&vstupni_stack, ')');
    push(&vstupni_stack, '+');
    push(&vstupni_stack, 'i'); // Change: push character instead of string

    int i = 0;

while (!isEmpty(&vstupni_stack)) {
    char a = peek(&vstupni_stack);
    char b = peek(&expr_stack);
    if (peek(&expr_stack) == '$') {
        push(&expr_stack, '<'); // Change: push character instead of integer
        push(&expr_stack, 'i'); // Change: push character instead of string
        pop(&vstupni_stack);
        printf("ll");
        i++;
    } else {
        switch (p_table[b - ' '][a - ' ']) {
            case '=':
                push(&expr_stack, a);
                pop(&vstupni_stack);
                i++;
                break;
            case '<':
                push(&expr_stack, '<');
                push(&expr_stack, a);
                pop(&vstupni_stack);
                i++;
                break;
            case '>':
                while (peek(&expr_stack) != '<') {
                    pop(&expr_stack);
                }
                pop(&expr_stack);
                char* r = najdi_pravidlo(&expr_stack);
                for (int j = 0; r[j] != '\0'; j++) {
                    push(&expr_stack, r[j]);
                }
                printf("Redukce: %s\n", r);
                break;
            case '$':
                return 0;
        }
    }
}
    while (!isEmpty(&expr_stack)) {
        printf("Top element: %d\n", peek(&expr_stack));
        pop(&expr_stack);
    }
    return 0;
}
