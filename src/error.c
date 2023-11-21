/*
* This file contains functions to hande error situations and safely exit program.
* 1 - chyba v programu v rámci lexikální analýzy (chybná struktura aktuálního lexému).
* 2 - chyba v programu v rámci syntaktické analýzy (chybná syntaxe programu, chybějící hlavička, atp.).
* 3 - sémantická chyba v programu – nedefinovaná funkce, redefinice proměnné.
* 4 - sémantická chyba v programu – špatný počet/typ parametrů u volání funkce či špatný typ návratové hodnoty z funkce.
* 5 - sémantická chyba v programu – použití nedefinované nebo neinicializované proměnné.
* 6 - sémantická chyba v programu – chybějící/přebývající výraz v příkazu návratu z funkce.
* 7 - sémantická chyba typové kompatibility v aritmetických, řetězcových a relačních výrazech.
* 8 - sémantická chyba odvození typu – typ proměnné nebo parametru není uveden a nelze odvodit od použitého výrazu.
* 9 - ostatní sémantické chyby.
* 99 - interní chyba překladače tj. neovlivněná vstupním programem (např. chyba alokace paměti atd.).
*/

#include <stdio.h>
#include <stdlib.h>
#include "dynamic.c"

/*
* --HELP-- Function to kill program.
* Input -> Error number.
*/
void handleExit(int errorCode) {
    exit(errorCode);
}

/*
* --USER-- Function to exit program.
* Input -> Error number.
*/
void ThrowError(int errorCode) {
    fprintf(stderr, "\033[0;31m");
    fprintf(stderr, "[ERROR]");
    fprintf(stderr, "\033[0m");

    switch (errorCode) {
        case 1:
            fprintf(stderr, " Error during lexical analysis (Invalid structure of the current token).");
            break;

        case 2:
            fprintf(stderr, " Syntax error (Invalid program syntax, missing header, etc.).");
            break;

        case 3:
            fprintf(stderr, " Undefined function.");
            break;

        case 4:
            fprintf(stderr, " Invalid number or type of parameters used in the function or invalid return type.");
            break;

        case 5:
            fprintf(stderr, " Undefined or uninitialized variable.");
            break;

        case 6:
            fprintf(stderr, " Missing/extra expression in the return statement.");
            break;

        case 7:
            fprintf(stderr, " Type mismatch in arithmetic, string, or relational expressions.");
            break;

        case 8:
            fprintf(stderr, " Type derivation error - missing/undeducible variable or parameter type.");
            break;

        case 9:
            fprintf(stderr, " Other semantic errors.");
            break;

        case 99:
            fprintf(stderr, " Internal compiler error (e.g., memory allocation error).");
            break;
    }

    fprintf(stderr, "\n");
    handleExit(errorCode);
}

/*
* --USER-- Function to remove dynamically allocated memory and exit program.
* Input -> Error number and dynamic structure pointer.
*/
void ThrowErrorStructure(int errorCode, struct Dynamic* head){
    DeleteDynamicStructure(head);
    ThrowError(errorCode);
}
/*
int main() {
    struct Dynamic* head = InitDynamic();
    DeleteDynamicStructure(head);
    Stack* s1 = CreateDynamic(&head, 1);
    Stack* s2 = CreateDynamic(&head, 1);
    Stack* s3 = CreateDynamic(&head, 1);
    tNode_t* n1 = CreateDynamic(&head, 2);
    *n1 = NULL;
    symtabInsert(n1, "func1", 1);
    symtabInsert(n1, "func2", 1);
    symtabInsert(n1, "varB", 2);
    symtabInsert(n1, "varA", 2);
    tNode_t* n2 = CreateDynamic(&head, 2);
    *n2 = NULL;
    symtabInsert(n2, "func1", 1);
    symtabInsert(n2, "func2", 1);
    symtabInsert(n2, "varB", 2);
    symtabInsert(n2, "varA", 2);
    if(DeleteDynamic(&head,s1)){printf("yes\n");}
    else {printf("no\n");}
    if(UpdateDynamic(head, n1, n1)){printf("UPDATED\n");}
    else {printf("UPDATE_CRASH\n");}
    if(DeleteDynamic(&head,n1)){printf("yes\n");}
    else {printf("no\n");}
    if(DeleteDynamic(&head,NULL)){printf("yes\n");}
    else {printf("no\n");}
    tNode_t* n3 = CreateDynamic(&head, 2);
    *n3 = NULL;
    Stack* s4 = CreateDynamic(&head, 1);
    //DeleteDynamicStructure(head);
    ThrowErrorStructure(99, head);
    printf("\nCHYBA\n");
    return 0;
}*/