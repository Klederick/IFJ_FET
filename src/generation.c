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

void printStrings(const char *strings[], int length) {
    int repeat = sizeof(*strings) / sizeof(*strings[0]);
    for (int i = 0; i < repeat; i++) {
        printf("%s\n", strings[i]);
    }
}

int generator() {
    
    const char *myStrings[] = {"Hello", "This", "Is", "A", "List", "Of", "Strings"};

    int numStrings = sizeof(myStrings) / sizeof(myStrings[0]);

    printStrings(myStrings, numStrings);
    
    
    return 0;
}
#endif