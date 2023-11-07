/*
- 1 - chyba v programu v rámci lexikální analýzy (chybná struktura aktuálního lexému).
• 2 - chyba v programu v rámci syntaktické analýzy (chybná syntaxe programu, chybějící hlavička, atp.).
• 3 - sémantická chyba v programu – nedefinovaná funkce, redefinice proměnné.
• 4 - sémantická chyba v programu – špatný počet/typ parametrů u volání funkce či
špatný typ návratové hodnoty z funkce.
• 5 - sémantická chyba v programu – použití nedefinované nebo neinicializované proměnné.
• 6 - sémantická chyba v programu – chybějící/přebývající výraz v příkazu návratu
z funkce.
• 7 - sémantická chyba typové kompatibility v aritmetických, řetězcových a relačních
výrazech.
• 8 - sémantická chyba odvození typu – typ proměnné nebo parametru není uveden a
nelze odvodit od použitého výrazu.
• 9 - ostatní sémantické chyby.
• 99 - interní chyba překladače tj. neovlivněná vstupním programem (např. chyba alokace paměti atd.).
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef ERROR_C
#define ERROR_C

void handleExit(int errorCode) {
    exit(errorCode);
}

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

#endif
