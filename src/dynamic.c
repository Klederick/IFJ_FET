#ifndef DYNAMIC_C
#define DYNAMIC_C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "stack.c"
#include "symtable.c"
#include <string.h>
/**
 * @file dynamic.c
 * @brief dynamic structure
 * 
 * IFJ a IAL projekt: Implementácia prekladača imperatívneho jazyka IFJ23
 * 
 * @author Frederick Tóth <xtothf00>
 * @author Andrej Mikuš <xmikus19>
 * @author Tom Široký <xsirok10>
 * @author Michael Babušík <xbabus01>
 */
/*
* This file contains implementation of linked list modified for storing information about allocated dynamic structures.
* Dynamic structures needs to be initialized and deleted via this functions. Other operations with dynamic structures are completely free.
* dataType values:
* 1) stack
* 2) symtable
* EXAMPLE:
* Stack* s1 = CreateDynamic(&head, 1); <- stack will be initialized automatically
* DeleteDynamic(&head, s1); <- stack will be automatically freed by it's destructor
*/

// Define the structure for a node
/*struct Dynamic {
    int dataType;
    void* genericPtr;
    struct Dynamic* next;
};*/

/*
*   --HELP-- Function to create a new node with the given data.
*   If succes -> return new Node
*   If failure -> return NULL
*/
struct Dynamic* CreateNode(int dataType) {
    struct Dynamic* newNode = (struct Dynamic*)malloc(sizeof(struct Dynamic));
    if (newNode == NULL) {
        return NULL;
    }
    switch(dataType)
    {
        case 1:{
            Stack* stc = (Stack*)malloc(sizeof(Stack));
            if (stc == NULL) {
                free(newNode);
                return NULL;
            }
            initializeStack(stc);
            newNode->genericPtr = stc;
        }break;
        case 2:{
            tNode_t* root = (tNode_t*)malloc(sizeof(tNode_t));
            if (root == NULL) {
                free(newNode);
                return NULL;
            }
            newNode->genericPtr = root;
        }break;
        default: newNode->genericPtr = NULL;
    }
    if(newNode->genericPtr == NULL){
        free(newNode);
        return NULL;
    }
    newNode->dataType = dataType;
    newNode->next = NULL;
    return newNode;
}

/*
*   --USER-- Function to add a new node to the end of the list and allocate dynamic memory.
*   input -> number of dynamic structure
*   If success -> return pointer to new dynamic structure
*   If failure -> return NULL
*/
void* CreateDynamic(struct Dynamic** head, int dataType) {
    struct Dynamic* newNode = CreateNode(dataType);
    if(newNode==NULL) return NULL;
    if(*head == NULL){
        *head = newNode;
    }
    else{
        struct Dynamic* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    return newNode->genericPtr;
}

/*
*   --HELP-- Function to delete selected dynamic structure by it's own destructor.
*/
void DynamicDestructor(int dataType, void* Ptr){
    switch(dataType)
    {
        case 1:{
            freestack(Ptr);
            free(Ptr);
        }break;
        case 2:{   
            tNode_t* destructor = Ptr;
            tNode_t* destructor2 = Ptr;
            symtabInsert(destructor,"dest",1);
            destroyTree(*destructor);
            *destructor2 = NULL;
            free(destructor2);
        }break;
    }
}

/*
*   --USER-- Function to delete node somewhere in the list and free dynamic memory.
*   Input -> pointer to dynamic structure
*   If success -> true
*   If failure -> false
*/
bool DeleteDynamic(struct Dynamic** head, void* Ptr) {
    if(Ptr == NULL) return false;
    struct Dynamic* help = *head;    
    if (help->genericPtr == Ptr) {
        *head = help->next;
        DynamicDestructor(help->dataType, help->genericPtr);
        free(help);
        return true;
    }
    else{
        struct Dynamic* previous = *head;
        struct Dynamic* current = previous->next;
        while (current != NULL) {
            if(current->genericPtr == Ptr){
                previous->next = current->next;
                DynamicDestructor(current->dataType, current->genericPtr);
                free(current);
                return true;
            }
            previous = current;
            current = current->next;
        }
    }
    return false;
}

/*
*   --USER-- Function to update node somewhere in the list.
*   Input -> old pointer to dynamic structure and new pointer to dynamic structure
*   If success -> true
*   If failure -> false
*/
bool UpdateDynamic(struct Dynamic* head, void* PtrOld, void* PtrNew) {
    if(PtrOld == NULL || PtrNew == NULL) return false;
    struct Dynamic* current = head;
    while (current != NULL) {
        if(current->genericPtr == PtrOld){
            current->genericPtr = PtrNew;
            return true;
        }
        current = current->next;
    }
    return false;
}

/*
*   --USER-- Function to initialize dynamic database (pointer).
*/
struct Dynamic* InitDynamic(){
    return NULL;
}

/*
* --USER-- Function to free the memory used by the dynamic database.
*   Input -> pointer to dynamic database
*/
void DeleteDynamicStructure(struct Dynamic* head) {
    struct Dynamic* current = head;
    while (current != NULL) {
        struct Dynamic* temp = current;
        current = current->next;
        DynamicDestructor(temp->dataType, temp->genericPtr);
        free(temp);
    }
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
    DeleteDynamicStructure(head);
    printf("CODE_SUCCESS\n");
    return 0;
}*/
#endif