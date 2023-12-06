#ifndef SYMTABLE_C
#define SYMTABLE_C
#include <string.h>

/*
* This code defines functions to manipulate an AVL tree that stores keys and node types. 
* It includes operations like right and left rotations, insertion into the tree, 
* searching, tree traversals (inorder, postorder, preorder), and a function to destroy the tree. 
* Additionally, it contains the tNode structure representing a node in the AVL tree, 
* containing a key, node type, height, and pointers to the left and right child nodes.
*/
int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(tNode_t node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalance(tNode_t node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->lptr) - height(node->rptr);
}

tNode_t newNode(char *key, int nodeType) {
    tNode_t node = (tNode_t)malloc(sizeof(struct tNode));
    if (node == NULL) {
        return NULL;
    }
    node->key = key;
    node->nodeType = nodeType;
    node->height = 1;
    node->lptr = NULL;
    node->rptr = NULL;
    return node;
}

tNode_t rightRotate(tNode_t y) {
    tNode_t x = y->lptr;
    tNode_t T2 = x->rptr;

    x->rptr = y;
    y->lptr = T2;

    y->height = max(height(y->lptr), height(y->rptr)) + 1;
    x->height = max(height(x->lptr), height(x->rptr)) + 1;

    return x;
}

tNode_t leftRotate(tNode_t x) {
    tNode_t y = x->rptr;
    tNode_t T2 = y->lptr;

    y->lptr = x;
    x->rptr = T2;

    x->height = max(height(x->lptr), height(x->rptr)) + 1;
    y->height = max(height(y->lptr), height(y->rptr)) + 1;

    return y;
}

tNode_t insert(tNode_t node, char *key, int nodeType) {
    if (node == NULL) {
        return newNode(key, nodeType);
    }

    if (strcmp(key, node->key) < 0) {
        node->lptr = insert(node->lptr, key, nodeType);
    } else if (strcmp(key, node->key) > 0) {
        node->rptr = insert(node->rptr, key, nodeType);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->lptr), height(node->rptr));

    int balance = getBalance(node);

    if (balance > 1) {
        if (strcmp(key, node->lptr->key) < 0) {
            return rightRotate(node);
        } else {
            node->lptr = leftRotate(node->lptr);
            return rightRotate(node);
        }
    }

    if (balance < -1) {
        if (strcmp(key, node->rptr->key) > 0) {
            return leftRotate(node);
        } else {
            node->rptr = rightRotate(node->rptr);
            return leftRotate(node);
        }
    }

    return node;
}

tNode_t search(tNode_t node, char *key) {
    if (node == NULL || strcmp(key, node->key) == 0) {
        return node;
    }

    if (strcmp(key, node->key) < 0) {
        return search(node->lptr, key);
    }

    return search(node->rptr, key);
}

void symtabInsert(tNode_t *tree, char *key, int nodeType) {
    *tree = insert(*tree, key, nodeType);
}

void symtabInorder(tNode_t tree) {
    if (tree != NULL) {
        symtabInorder(tree->lptr);
        printf("Key: %s, NodeType: %d\n", tree->key, tree->nodeType);
        symtabInorder(tree->rptr);
    }
}

void symtabPostorder(tNode_t tree) {
    if (tree != NULL) {
        symtabPostorder(tree->lptr);
        symtabPostorder(tree->rptr);
        printf("Key: %s, NodeType: %d\n", tree->key, tree->nodeType);
    }
}

void symtabPreorder(tNode_t tree) {
    if (tree != NULL) {
        printf("Key: %s, NodeType: %d\n", tree->key, tree->nodeType);
        symtabPreorder(tree->lptr);
        symtabPreorder(tree->rptr);
    }
}

void destroyTree(tNode_t tree) {
    if (tree == NULL) {
        return;
    }

    destroyTree(tree->lptr);
    destroyTree(tree->rptr);

    free(tree);
}

tNode_t initializeTree() {
    return NULL;
}
#endif