#ifndef GENERATION_C
#define GENERATION_C
//  include
#include <stdio.h>

struct AVLNode {
    char* key;                // The value or key held by the node
    struct AVLNode *left;   // Pointer to the left child node
    struct AVLNode *right;  // Pointer to the right child node
    int height;             // Height of the node in the tree
};

void printStrings(char *strings[]) {
    int length = 0;
    while (strings[length] != NULL) {
        printf("%s", strings[length]);
        length++;
        if(strings[length] != NULL) printf(" ");
    }
    printf("\n");
}

int generator() {
    char *instruction[10];
    instruction[0]="Hello";
    instruction[1]="Bonjour";
    instruction[2]=NULL;
    printStrings(instruction);
        
    return 0;
}
int main(){
    generator();
    return 0;
}
#endif