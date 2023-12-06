#include "parser.c"
/**
 * @file main.c
 * @brief main
 * 
 * IFJ a IAL projekt: Implementácia prekladača imperatívneho jazyka IFJ23
 * 
 * @author Frederick Tóth <xtothf00>
 * @author Andrej Mikuš <xmikus19>
 * @author Tom Široký <xsirok10>
 * @author Michael Babušík <xbabus01>
 */
int main(int argc, char* argv[]) {

    printf(".IFJcode23\n");
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
    printf("starting parsing\n");
    parse(file);

    return 0;
}

