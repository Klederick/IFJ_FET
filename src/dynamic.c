#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for a node
struct Node {
    int dataType;
    void* genericPtr;
    struct Node* next;
};

/*
*   --HELP-- Function to create a new node with the given data.
*   If succes -> return new Node
*   If failure -> return NULL
*/
struct Node* CreateNode(int dataType) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
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
void* CreateDynamic(struct Node** head, int dataType) {
    struct Node* newNode = CreateNode(dataType);
    if(newNode==NULL) return NULL;
    if(*head == NULL){
        *head = newNode;
    }
    else{
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    return newNode->genericPtr;
}

/*
*   --USER-- Function to delete node somewhere in the list and free dynamic memory.
*   Input -> pointer to dynamic structure
*   If success -> true
*   If failure -> false
*/
bool DeleteDynamic(struct Node** head, void* Ptr) {
    struct Node* help = *head;
    if (help->genericPtr == Ptr) {
        *head = help->next;
        DynamicDectructor(help->dataType, help->genericPtr);
        free(help);
        return true;
    }
    else{
        struct Node* previous = *head;
        struct Node* current = previous->next;
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

void DynamicDestructor(int dataType, void* Ptr);

/*// Function to print the linked list
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}*/

void InitList();
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
    struct Node* head = NULL;

    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 30);

    printf("Linked List: ");
    printList(head);

    freeList(head);

    return 0;
}