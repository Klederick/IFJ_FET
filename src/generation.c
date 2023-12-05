#ifndef GENERATION_C
#define GENERATION_C
//  include
#include <stdio.h>

void printStrings(char *strings[]) {
    int length = 0;
    while (strings[length] != NULL) {
        printf("%s", strings[length]);
        length++;
        if(strings[length] != NULL) printf(" ");
    }
    printf("\n");
}

void outputLogic(int flag, char* value1, char* value2, char* value3){
    char *instruction[10];
    switch(flag)
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

struct AVLNode {
    char* key;                // The value or key held by the node
    struct AVLNode *left;   // Pointer to the left child node
    struct AVLNode *right;  // Pointer to the right child node
    int height;             // Height of the node in the tree
};

int generator() {
    //INPUT LOGIC


    //WORK LOGIC
    int flag;

    //TEST
    char* value1 = "AHOJ";
    char* value2 = "HELLO";
    outputLogic(11,"","","");
    outputLogic(10, value1, value2,"");
    outputLogic(11,"","","");
       
    return 0;
}
int main(){
    generator();
    return 0;
}
#endif