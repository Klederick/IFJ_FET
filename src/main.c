#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

//#include "error.c"
//#include "scanner.c"
//include "parser.c"
//#include "generace.c"
#include "stack.c"
#include "symtable.c"

int main() {
    // Inicializace datových struktur nebo provádění dalších potřebných kroků
    //Stack stack;
    //initializeStack(&stack);

    while (true) {
        // Zde můžete provádět scanner a parser
        // Načtení vstupního kódu, volání scanneru a parseru
        // Kontrola, zda je statement prázdný nebo ne

        if (/* statement je prázdný */) {
            break; // Výstup ze smyčky, protože nemá smysl generovat kód
        } else {
            // Zde můžete spustit generátor kódu
            // generace(&stack);
        }
    }

    return 0;
}

