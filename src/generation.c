#ifndef GENERATION_C //definition of generation
#define GENERATION_C
//  include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

//function to print instruction to stdout
void printStrings(char* strings[]) {
    int length = 0;
    while (strings[length] != NULL) {
        printf("%s", strings[length]);
        length++;
        if (strings[length] != NULL) printf(" ");
    }
    printf("\n");
}

//function to set instruction format
void outputLogic(int flag, char* value1, char* value2, char* value3) {
    char* instruction[10];
    switch (flag)
    {   //Framework & Function call
    case 100:
    {
        instruction[0] = "MOVE";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = NULL;
    }break;
    case 101:
    {
        instruction[0] = "CREATEFRAME";
        instruction[1] = NULL;
    }break;
    case 102:
    {
        instruction[0] = "PUSHFRAME";
        instruction[1] = NULL;
    }break;
    case 103:
    {
        instruction[0] = "POPFRAME";
        instruction[1] = NULL;
    }break;
    case 104:
    {
        instruction[0] = "DEFVAR";
        instruction[1] = value1;
        instruction[2] = NULL;
    }break;
    case 105:
    {
        instruction[0] = "CALL";
        instruction[1] = value1;
        instruction[2] = NULL;
    }break;
    case 106:
    {
        instruction[0] = "RETURN";
        instruction[1] = NULL;
    }break;
    //Stack operations
    case 200:
    {
        instruction[0] = "PUSHS";
        instruction[1] = value1;
        instruction[2] = NULL;
    }break;
    case 201:
    {
        instruction[0] = "POPS";
        instruction[1] = value1;
        instruction[2] = NULL;
    }break;
    case 202:
    {
        instruction[0] = "CLEARS";
        instruction[1] = NULL;
    }break;
    //Aritmetic
    case 300:
    {
        instruction[0] = "ADD";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 301:
    {
        instruction[0] = "SUB";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 302:
    {
        instruction[0] = "MUL";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 303:
    {
        instruction[0] = "DIV";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 304:
    {
        instruction[0] = "IDIV";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 305:
    {
        instruction[0] = "ADDS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 306:
    {
        instruction[0] = "SUBS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 307:
    {
        instruction[0] = "MULS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 308:
    {
        instruction[0] = "DIVS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 309:
    {
        instruction[0] = "IDIVS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 310:
    {
        instruction[0] = "LT";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 311:
    {
        instruction[0] = "GT";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 312:
    {
        instruction[0] = "EQ";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 313:
    {
        instruction[0] = "LTS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 314:
    {
        instruction[0] = "GTS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 315:
    {
        instruction[0] = "EQS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 316:
    {
        instruction[0] = "AND";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 317:
    {
        instruction[0] = "OR";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 318:
    {
        instruction[0] = "NOT";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 319:
    {
        instruction[0] = "ANDS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 320:
    {
        instruction[0] = "ORS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 321:
    {
        instruction[0] = "NOTS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 322:
    {
        instruction[0] = "INT2FLOAT";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = NULL;
    }break;
    case 323:
    {
        instruction[0] = "FLOAT2INT";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = NULL;
    }break;
    case 324:
    {
        instruction[0] = "INT2CHAR";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = NULL;
    }break;
    case 325:
    {
        instruction[0] = "STRI2INT";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 326:
    {
        instruction[0] = "INT2FLOATS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = NULL;
    }break;
    case 327:
    {
        instruction[0] = "FLOAT2INTS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = NULL;
    }break;
    case 328:
    {
        instruction[0] = "INT2CHARS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = NULL;
    }break;
    case 329:
    {
        instruction[0] = "STRI2INTS";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    // I/O instructions
    case 400:
    {
        instruction[0] = "READ";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = NULL;
    }break;
    case 401:
    {
        instruction[0] = "WRITE";
        instruction[1] = value1;
        instruction[2] = NULL;
    }break;
    //String instructions
    case 500:
    {
        instruction[0] = "CONCAT";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 501:
    {
        instruction[0] = "STRLEN";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = NULL;
    }break;
    case 502:
    {
        instruction[0] = "GETCHAR";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 503:
    {
        instruction[0] = "SETCHAR";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    //Type instructions
    case 600:
    {
        instruction[0] = "TYPE";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = NULL;
    }break;
    //Program flow instructions
    case 700:
    {
        instruction[0] = "LABEL";
        instruction[1] = value1;
        instruction[2] = NULL;
    }break;
    case 701:
    {
        instruction[0] = "JUMP";
        instruction[1] = value1;
        instruction[2] = NULL;
    }break;
    case 702:
    {
        instruction[0] = "JUMPIFEQ";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 703:
    {
        instruction[0] = "JUMPIFNEQ";
        instruction[1] = value1;
        instruction[2] = value2;
        instruction[3] = value3;
        instruction[4] = NULL;
    }break;
    case 704:
    {
        instruction[0] = "JUMPIFEQS";
        instruction[1] = value1;
        instruction[2] = NULL;
    }break;
    case 705:
    {
        instruction[0] = "JUMPIFNEQS";
        instruction[1] = value1;
        instruction[2] = NULL;
    }break;
    case 706:
    {
        instruction[0] = "EXIT";
        instruction[1] = value1;
        instruction[2] = NULL;
    }break;
    }
    printStrings(instruction);
}

/*
*   --HELP-- Function to write IFJcode23 instructions.
*   output: 0 -> OK, -1 -> memory error
*/
int generator(int* depth, int* tmpstr, char* command[]) {
    //WORK LOGIC
    const char* keywords[] = { "var","let","func","if","else","while" };
    const char* inputs[] = { "Double","Double?","Int","Int?","String","String?","readString()","readInt()","readDouble()" };
    const char* functions[] = { "readString()","readInt()","readDouble()","write","Int2Double","Double2Int","length","call","}","call}","return","substring","ord","chr" };
    int fork = 0;
    while (fork < 3)
    {
        if (strcmp(keywords[fork], command[0]) == 0) { break; }
        fork++;
    }
    switch (fork)
    {
    case 0://var
    case 1://let
    {
        int type = 0;
        while (type < 9)//Look for correct type
        {
            if (strcmp(command[3], inputs[type]) == 0) { break; }
            type++;
        }
        switch (type)
        {
        case 0://Double
        case 1://Double?
        {
            size_t size = strlen(command[1]) + 4;
            char* str1 = malloc(size);
            if (str1 == NULL) { return -1; }
            if (strcmp(command[5], "nil") == 0) { size = strlen("nil@nil") + 1; }
            else { size = strlen("float@") + strlen(command[5]) + 1; }
            char* str2 = malloc(size);
            if (str2 == NULL) { free(str1); return -1; }
            if (*depth == 0) { strcpy(str1, "GF@"); strcat(str1, command[1]); }
            else { strcpy(str1, "LF@"); strcat(str1, command[1]); }
            if (strcmp(command[5], "nil") == 0) { strcpy(str2, "nil@nil"); }
            else { strcpy(str2, "float@"); strcat(str2, command[5]); }
            outputLogic(104, str1, "", "");//defvar
            outputLogic(100, str1, str2, "");//move
            free(str1);
            free(str2);

        }break;
        case 2://Int
        case 3://Int?
        {
            size_t size = strlen(command[1]) + 4;
            char* str1 = malloc(size);
            if (str1 == NULL) { return -1; }
            if (strcmp(command[5], "nil") == 0) { size = strlen("nil@nil") + 1; }
            else { size = strlen("int@") + strlen(command[5]) + 1; }
            char* str2 = malloc(size);
            if (str2 == NULL) { free(str1); return -1; }
            if (*depth == 0) { strcpy(str1, "GF@"); strcat(str1, command[1]); }
            else { strcpy(str1, "LF@"); strcat(str1, command[1]); }
            if (strcmp(command[5], "nil") == 0) { strcpy(str2, "nil@nil"); }
            else { strcpy(str2, "int@"); strcat(str2, command[5]); }
            outputLogic(104, str1, "", "");//defvar
            outputLogic(100, str1, str2, "");//move
            free(str1);
            free(str2);
        }break;
        case 4://String
        case 5://String?
        {
            size_t size = strlen(command[1]) + 4;
            char* str1 = malloc(size);
            if (str1 == NULL) { return -1; }
            if (strcmp(command[5], "nil") == 0) { size = strlen("nil@nil") + 1; }
            else { size = strlen("string@") + strlen(command[5]) + 1; }
            char* str2 = malloc(size);
            if (str2 == NULL) { free(str1); return -1; }
            if (*depth == 0) { strcpy(str1, "GF@"); strcat(str1, command[1]); }
            else { strcpy(str1, "LF@"); strcat(str1, command[1]); }
            if (strcmp(command[5], "nil") == 0) { strcpy(str2, "nil@nil"); }
            else { strcpy(str2, "string@"); strcat(str2, command[5]); }
            outputLogic(104, str1, "", "");//defvar
            outputLogic(100, str1, str2, "");//move
            free(str1);
            free(str2);
        }break;
        case 6://read string & insert to var/let
        {
            size_t size = strlen(command[1]) + 4;
            char* str1 = malloc(size);
            if (str1 == NULL) { return -1; }
            if (*depth == 0) { strcpy(str1, "GF@"); strcat(str1, command[1]); }
            else { strcpy(str1, "LF@"); strcat(str1, command[1]); }
            outputLogic(104, str1, "", "");//defvar
            outputLogic(400, str1, "string", "");//read
            free(str1);
        }break;
        case 7://read int & insert to var/let
        {
            size_t size = strlen(command[1]) + 4;
            char* str1 = malloc(size);
            if (str1 == NULL) { return -1; }
            if (*depth == 0) { strcpy(str1, "GF@"); strcat(str1, command[1]); }
            else { strcpy(str1, "LF@"); strcat(str1, command[1]); }
            outputLogic(104, str1, "", "");//defvar
            outputLogic(400, str1, "int", "");//read
            free(str1);
        }break;
        case 8://read double & insert to var/let
        {
            size_t size = strlen(command[1]) + 4;
            char* str1 = malloc(size);
            if (str1 == NULL) { return -1; }
            if (*depth == 0) { strcpy(str1, "GF@"); strcat(str1, command[1]); }
            else { strcpy(str1, "LF@"); strcat(str1, command[1]); }
            outputLogic(104, str1, "", "");//defvar
            outputLogic(400, str1, "float", "");//read
            free(str1);
        }break;
        }
    }break;
    case 2://func
    {
        int type = 0;
        while (type < 11)//Look for correct type
        {
            if (strcmp(command[1], functions[type]) == 0) { break; }
            type++;
        }
        switch (type)
        {
        case 0://readString
        {
            char strnumber[100];
            sprintf(strnumber, "%d", *tmpstr); // Convert integer to string
            size_t size = strlen("GF@_tmpstr_") + strlen(strnumber);
            char* str1 = malloc(size);
            if (str1 == NULL) { return -1; }
            if (*depth == 0) { strcpy(str1, "GF@_tmpstr_"); strcat(str1, strnumber); }
            else { strcpy(str1, "LF@_tmpstr_"); strcat(str1, strnumber); }
            outputLogic(104, str1, "", "");//defvar
            outputLogic(400, str1, "string", "");//read
            free(str1);
        }break;
        case 1://readInt
        {
            char strnumber[100];
            sprintf(strnumber, "%d", *tmpstr); // Convert integer to string
            size_t size = strlen("GF@_tmpstr_") + strlen(strnumber);
            char* str1 = malloc(size);
            if (str1 == NULL) { return -1; }
            if (*depth == 0) { strcpy(str1, "GF@_tmpstr_"); strcat(str1, strnumber); }
            else { strcpy(str1, "LF@_tmpstr_"); strcat(str1, strnumber); }
            outputLogic(104, str1, "", "");//defvar
            outputLogic(400, str1, "int", "");//read
            free(str1);
        }break;
        case 2://readDouble
        {
            char strnumber[100];
            sprintf(strnumber, "%d", *tmpstr); // Convert integer to string
            size_t size = strlen("GF@_tmpstr_") + strlen(strnumber);
            char* str1 = malloc(size);
            if (str1 == NULL) { return -1; }
            if (*depth == 0) { strcpy(str1, "GF@_tmpstr_"); strcat(str1, strnumber); }
            else { strcpy(str1, "LF@_tmpstr_"); strcat(str1, strnumber); }
            outputLogic(104, str1, "", "");//defvar
            outputLogic(400, str1, "float", "");//read
            free(str1);
        }break;
        case 3://write
        {
            int counter = 3;
            while (strcmp(command[counter], ")") != 0)
            {
                if (strcmp(command[counter], ",") != 0) {
                    outputLogic(401, command[counter], "", "");//write
                }
                counter++;
            }
        }break;
        case 4://Int2Double
        {
            size_t size = strlen("GF@") + strlen(command[4]);
            char* str1 = malloc(size);
            if (str1 == NULL) { return -1; }
            if (*depth == 0) { strcpy(str1, "GF@"); strcat(str1, command[4]); }
            else { strcpy(str1, "LF@"); strcat(str1, command[4]); }
            char strnumber[100];
            sprintf(strnumber, "%d", *tmpstr); // Convert integer to string
            size = strlen("GF@_tmpstr_") + strlen(strnumber);
            char* str2 = malloc(size);
            if (str2 == NULL) { free(str1); return -1; }
            if (*depth == 0) { strcpy(str2, "GF@_tmpstr_"); strcat(str2, strnumber); }
            else { strcpy(str2, "LF@_tmpstr_"); strcat(str2, strnumber); }
            outputLogic(322, str2, str1, "");//int2float
            free(str1);
            free(str2);
        }break;
        case 5://Double2Int
        {
            size_t size = strlen("GF@") + strlen(command[4]);
            char* str1 = malloc(size);
            if (str1 == NULL) { return -1; }
            if (*depth == 0) { strcpy(str1, "GF@"); strcat(str1, command[4]); }
            else { strcpy(str1, "LF@"); strcat(str1, command[4]); }
            char strnumber[100];
            sprintf(strnumber, "%d", *tmpstr); // Convert integer to string
            size = strlen("GF@_tmpstr_") + strlen(strnumber);
            char* str2 = malloc(size);
            if (str2 == NULL) { free(str1); return -1; }
            if (*depth == 0) { strcpy(str2, "GF@_tmpstr_"); strcat(str2, strnumber); }
            else { strcpy(str2, "LF@_tmpstr_"); strcat(str2, strnumber); }
            outputLogic(323, str2, str1, "");//float2int
            free(str1);
            free(str2);
        }break;
        case 6://length
        {
            size_t size = strlen("GF@") + strlen(command[4]);
            char* str1 = malloc(size);
            if (str1 == NULL) { return -1; }
            if (*depth == 0) { strcpy(str1, "GF@"); strcat(str1, command[4]); }
            else { strcpy(str1, "LF@"); strcat(str1, command[4]); }
            char strnumber[100];
            sprintf(strnumber, "%d", *tmpstr); // Convert integer to string
            size = strlen("GF@_tmpstr_") + strlen(strnumber);
            char* str2 = malloc(size);
            if (str2 == NULL) { free(str1); return -1; }
            if (*depth == 0) { strcpy(str2, "GF@_tmpstr_"); strcat(str2, strnumber); }
            else { strcpy(str2, "LF@_tmpstr_"); strcat(str2, strnumber); }
            outputLogic(501, str2, str1, "");//strlen
            free(str1);
            free(str2);
        }break;
        case 7://call
        {
            outputLogic(101, "", "", "");//createframe
            int counter = 4;
            int counter2 = 1;
            while (strcmp(command[counter], ")") != 0)
            {
                char strnumber[100];
                sprintf(strnumber, "%d", counter2); // Convert integer to string
                size_t size = strlen("TF@TF") + strlen(strnumber);
                char* str1 = malloc(size);
                if (str1 == NULL) { return -1; }
                strcpy(str1, "TF@TF");
                strcat(str1, strnumber);
                outputLogic(104, str1, "", "");//defvar
                counter++;
                if (strcmp("Int", command[counter]) == 0) {
                    counter++;
                    outputLogic(100, str1, command[counter], "");
                }
                if (strcmp("Double", command[counter]) == 0) {
                    counter++;
                    outputLogic(100, str1, command[counter], "");
                }
                if (strcmp("String", command[counter]) == 0) {
                    counter++;
                    outputLogic(100, str1, command[counter], "");
                }
                counter++;
                counter2++;
                free(str1);
            }
            outputLogic(105, command[2], "", "");//call

        }break;
        case 8://}
        {
            outputLogic(103, "", "", "");//popframe
            outputLogic(106, "", "", "");//return
        }break;
        case 9://call}
        {
            size_t size = strlen("GF@") + strlen(command[2]);
            char* str1 = malloc(size);
            if (str1 == NULL) { return -1; }
            if (*depth == 0) { strcpy(str1, "GF@"); strcat(str1, command[2]); }
            else { strcpy(str1, "LF@"); strcat(str1, command[2]); }
            outputLogic(100, str1, "TF@RETVAL", "");//move
        }break;
        case 10://return
        {
            if (strcmp(command[2], "nil") != 0) {
                outputLogic(104, "LF@RETVAL", "", "");//defvar
                outputLogic(100, "TF@RETVAL", command[3], "");//move
            }

        }break;
        default://function call
        {
            size_t size = strlen("GF@") + strlen(command[1]);
            char* str1 = malloc(size);
            if (str1 == NULL) { return -1; }
            if (*depth == 0) { strcpy(str1, "GF@"); strcat(str1, command[1]); }
            else { strcpy(str1, "LF@"); strcat(str1, command[1]); }
            outputLogic(700, str1, "", "");//label
            outputLogic(102, "", "", "");//pushframe

        }break;
        }
    }break;
    }
    return 0;
}

void restoreCommandStructure(tNode_t root) {
    if (root) {
        restoreCommandStructure(root->lptr);
        printf("Command: %s, NodeType: %d, Height: %d\n", root->key, root->nodeType, root->height);
        restoreCommandStructure(root->rptr);
    }
}



//int gen(tNode_t command, int ExpressionCounter, eNode** expressions){
int gen() {
    //restoreCommandStructure(command);
    int depth = 1;
    int tmpstr = 20;
    char* command[1000];
    command[0] = "var";
    command[1] = "w";
    command[2] = ":";
    command[3] = "Int";
    command[4] = "=";
    command[5] = "100";
    command[6] = "";
    command[7] = "";
    command[8] = "";
    int ret = generator(&depth, &tmpstr, command);
    printf("FINAL STATE:\ndepth:%i\ntmpstr:%i\nreturn:%i\n", depth, tmpstr, ret);
    return 0;
}

/*int main(){
    gen();
}*/
#endif
/* EXPRESSION FOR INT
#include <stdio.h>
#include <stdlib.h>

struct AVLNode {
    char data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

// Function to create a new node
struct AVLNode* newNode(char data) {
    struct AVLNode* node = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to evaluate an expression tree
int evaluateExpression(struct AVLNode* root) {
    if (root == NULL) {
        return 0; // Return 0 for empty tree or leaf node containing operators
    }

    // If leaf node (operand), return its numeric value
    if (root->left == NULL && root->right == NULL) {
        return root->data - '0'; // Assuming the data is a single digit number
    }

    // Evaluate left and right subtrees
    int leftValue = evaluateExpression(root->left);
    int rightValue = evaluateExpression(root->right);

    // Perform operation based on the operator at the current node
    switch (root->data) {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            return leftValue / rightValue; // Assuming rightValue is not 0
        default:
            return 0; // Handle other operators if needed
    }
}

int main() {
    // Example of constructing an expression tree
    struct AVLNode* root = newNode('+');
    root->left = newNode('*');
    root->right = newNode('-');
    root->left->left = newNode('5');
    root->left->right = newNode('2');
    root->right->left = newNode('8');
    root->right->right = newNode('3');

    // Evaluate the expression tree
    int result = evaluateExpression(root);
    printf("Result: %d\n", result);

    return 0;
}
*/
/* EXPRESSION FOR DOUBLE
#include <stdio.h>
#include <stdlib.h>

struct AVLNode {
    char data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

// Function to create a new node
struct AVLNode* newNode(char data) {
    struct AVLNode* node = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to evaluate an expression tree
double evaluateExpression(struct AVLNode* root) {
    if (root == NULL) {
        return 0.0; // Return 0 for empty tree or leaf node containing operators
    }

    // If leaf node (operand), return its numeric value
    if (root->left == NULL && root->right == NULL) {
        return root->data - '0'; // Assuming the data is a single digit number
    }

    // Evaluate left and right subtrees
    double leftValue = evaluateExpression(root->left);
    double rightValue = evaluateExpression(root->right);

    // Perform operation based on the operator at the current node
    switch (root->data) {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            return leftValue / rightValue; // Assuming rightValue is not 0
        default:
            return 0.0; // Handle other operators if needed
    }
}

int main() {
    // Example of constructing an expression tree with doubles
    struct AVLNode* root = newNode('+');
    root->left = newNode('*');
    root->right = newNode('-');
    root->left->left = newNode('5');
    root->left->right = newNode('2');
    root->right->left = newNode('8');
    root->right->right = newNode('3');

    // Evaluate the expression tree
    double result = evaluateExpression(root);
    printf("Result: %.2f\n", result);

    return 0;
}
*/
/* EXPRESSION FOR STRING
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AVLNode {
    char* data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

// Function to create a new node
struct AVLNode* newNode(const char* data) {
    struct AVLNode* node = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    node->data = strdup(data);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to evaluate an expression tree
char* evaluateExpression(struct AVLNode* root) {
    if (root == NULL) {
        return NULL; // Return NULL for empty tree or leaf node containing operators
    }

    // If leaf node (operand), return its value
    if (root->left == NULL && root->right == NULL) {
        return strdup(root->data);
    }

    // Evaluate left and right subtrees
    char* leftValue = evaluateExpression(root->left);
    char* rightValue = evaluateExpression(root->right);

    // Perform operation based on the operator at the current node (assuming concatenation)
    char* result = NULL;
    if (strcmp(root->data, "+") == 0) {
        size_t len = strlen(leftValue) + strlen(rightValue) + 1;
        result = (char*)malloc(len);
        strcpy(result, leftValue);
        strcat(result, rightValue);
    } else {
        // Handle other operations if needed
        // For example: string comparison, substring operations, etc.
        // You can add cases for other operators as required.
        // Here, if the operator is not '+', it returns an empty string.
        result = strdup("");
    }

    free(leftValue);
    free(rightValue);
    return result;
}

int main() {
    // Example of constructing an expression tree with strings
    struct AVLNode* root = newNode("+");
    root->left = newNode("Hello, ");
    root->right = newNode("world!");

    // Evaluate the expression tree
    char* result = evaluateExpression(root);
    printf("Result: %s\n", result);

    free(result);
    return 0;
}

*/