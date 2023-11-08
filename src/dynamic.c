#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for a node
struct Dynamic {
    int dataType;
    void* genericPtr;
    struct Dynamic* next;
};

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

        }break;
        case 2:{

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

        }break;
        case 2:{

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

/*// Function to print the linked list
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}*/

/*
*   --USER-- Function to initialize dynamic structure (pointer).
*/
struct Dynamic* InitDynamic(){
    return NULL;
}
// Function to free the memory used by the linked list
/*void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}*/

int main() {
    struct Dynamic* head = InitDynamic();
    

    return 0;
}