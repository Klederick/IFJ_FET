


#include "parser.c"

//#include "error.c"
//#include "scanner.c"
//#include "generace.c"
//#include "stack.c"
//#include "symtable.c"
//#include "structs.h"

int main(int argc, char* argv[]) {
    //ExpressionStack expr_stack;
    //initializeExpressionStack(&expr_stack);
    //ExpressionStack node_stack;
    //initializeExpressionStack(&node_stack);   
    // Inicializace datových struktur nebo provádění dalších potřebných kroků
    //Stack stack;
    //initializeStack(&stack);
    printf(stdout,".IFJcode23");
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

