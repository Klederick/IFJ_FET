


#include "parser.c"

//#include "error.c"
//#include "scanner.c"
//#include "generace.c"
//#include "stack.c"
//#include "symtable.c"
//#include "structs.h"

int main(int argc, char* argv[]) {
    // Inicializace datových struktur nebo provádění dalších potřebných kroků
    //Stack stack;
    //initializeStack(&stack);
    if (argc != 2) {
        fprintf(stderr,"Pouzitie: %s <filename>\n", argv[0]);
        return -1;
    }
        FILE *file = fopen(argv[1], "r");
        // check if file exists
        if (file == NULL) {
            fprintf(stderr,"Error \n");
            ThrowError(1);
        }
    parse(file);

    return 0;
}

