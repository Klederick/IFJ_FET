#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "stack.c"
#include "scanner.c"
#include "expression.c"
#include "symtable.c"
#include "error.c"
//simple state machine
/*
//Expression stack
ExpressionStack* expr_stack;
initializeExpressionStack(expr_stack);
//node stack
ExpressionStack* node_stack;
initializeExpressionStack(node_stack);
//temp stack
ExpressionStack* temp_stack;
initializeExpressionStack(temp_stack);
*/
/*
Special cases or groups in parsing:
function declaration

*/
bool goSwitch(bool arg1){
    if(arg1){
        return false;
    }else{
        return true;
    }
}
//starts and ends an expression
void expr_Signal(){
    struct Token scannedToken;
    scannedToken.ID = 14; scannedToken.symbol = "$";
    expression(scannedToken);
}
//check if it is term
bool isterm(struct Token token){
    if(token.ID == 12 || token.ID == 13 || token.ID == 14){
        return true;
    }else{
        if(strcmp(token.symbol,")")){
            return true;
        }else{
            return false;
        }
        }
}

//consume until, returns a stack of tokens -> build bt
Stack* consumeUntil(FILE* file, int ID, char* symbol){
	struct Token token = getToken(file);
	Stack* stack;
    initializeStack(stack);
    while(token.ID != ID && !strcmp(token.symbol,symbol)){
        push(stack, token.ID);
		token = getToken(file);
	}
	return stack; 
}
//check if expected
bool ExpectedID(int IDs[12], struct Token token){
    for(int i = 0; i < 12; i++){
        if(IDs[i] == 1){
            if(token.ID == i){
                return true;
            }
        }
    }
    return false;
}
bool ExpectedSymbol(int length,char* symbols[length], struct Token token){
    for(int i = 0; i < length; i++){
        if(strcmp(symbols[i],token.symbol)){
            return true;
        }
    }
    return false;
}

//parse function (tokens -> tokens List to form AVH)
int main(int argc, char* argv[]){
    
    bool inExpression = false;
    struct Token *tokenList = NULL;
    struct Token *exprList = NULL;
    //move to main.c, rename function to parse
    //Check arguments
    if (argc != 2) {
        fprintf(stderr,"Pouzitie: %s <filename>\n", argv[0]);
        return -1;
    }
    FILE *file = fopen(argv[1], "r");
    // check if file exists
    if (file == NULL) {
        fprintf(stderr,"Error \n");
        return -1;
    }
    //parsing
    //tokens
    struct Token scannedToken;
    struct Token tempToken;
    //counters
    int counter = 0;
    int exprcounter = 0;
    //bools for different states
    bool operator = false;

    //expected tables
    int symbolListLen = 0;
    char* ExpectedSymbolList[symbolListLen];
    int ExpectedIDsList[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    bool finish = false;

    scannedToken = getToken(file);
    while(scannedToken.ID != 0 && finish == false){
        printf("Token %d: (%d) %s (spaces behind: %d)\n",counter,scannedToken.ID,scannedToken.symbol,scannedToken.spacesBehind);
        counter++;
        //reset states if wrong ID
        if(inExpression){
            if(scannedToken.ID == 2 || scannedToken.ID == 4 || scannedToken.ID == 11 || scannedToken.ID == 13){
                //all good
            }else{
                //turn off expression
                expr_Signal();
                inExpression = false;
                //expressionType = -1;
                exprcounter = 0;
                free(exprList);
            }
            
        }
        //check if token is in expected
        if(ExpectedID(ExpectedIDsList, scannedToken) || ExpectedSymbol(symbolListLen, ExpectedSymbolList, scannedToken)){
            //all good token is expected
            //add token to list
            tokenList = realloc(tokenList, sizeof(struct Token)*counter);
            tokenList[counter - 1] = scannedToken;
        }else{
            //UNEXPECTED TOKEN
            finish = true;
            //send to next function to construct tree (if possible)
            parseConstruct(tokenList);
        }
        //Reset expected list, both symbol and id list 
        
        //end of state reset
        if(goSwitch(inExpression)){
            switch(scannedToken.ID){
                case 0: if(strcmp(scannedToken.symbol,":")){
                            
                        }else if(strcmp(scannedToken.symbol,"=")){

                        }else{
                            printf("Toto by sa nemalo nikdy stat ak je toto na vypise tak opakujem IFJ!\n");
                            ThrowError(99);
                        };
                        break;
                case 1: if(!inExpression){ inExpression = true; expr_Signal(); } break;
                case 2: break;
                case 3: if(!inExpression){ inExpression = true; expr_Signal(); } break;
                case 4: break;
                case 5: break;
                case 6: 
                case 7: break;
                case 8: break;
                case 9: break;
                case 10:
                    if(strcmp(scannedToken.symbol,"while") || strcmp(scannedToken.symbol,"if") ){         if(!inExpression){
                            inExpression = true; expr_Signal();
                            tempToken = getToken(file);
                        if(strcmp(tempToken.symbol,"(")){
                            counter++;
                            tokenList = realloc(tokenList ,sizeof(struct Token)*counter);
                            tokenList[counter - 1] = tempToken;
                        }else{
                            //TODO ERROR TO ERROR.C
                            fprintf(stderr,"No brackets after while/if statement\n");
                            fprintf(stderr,"Correct usage if/while( expression op expression ){...\n");
                            ThrowError(1); //lexical analysis error
                            return 0;
                        }
                    } }
                    if(strcmp(scannedToken.symbol,"return")){
                        if(!inExpression){
                            inExpression = true; expr_Signal();
                        }
                    }
                    break;
                case 11: break;
                case 12: break;
                case 13: break;
                default: break;
                    if(scannedToken.ID < 0){
                        //komentar, runni while again
                        break;
                    }
            }
        }
        if(inExpression){
            //check if the flow of tokens is correct
            exprcounter++;
            //helping var for counting brackets
            int bracket = 0;
            switch(scannedToken.ID){
                case 2:
                    if(exprcounter >= 2 && !isterm(exprList[exprcounter-2])){
                        //TODO ERROR.C
                        fprintf(stderr,"Operand before operator is not a term\n");
                        //while pre nekonecno zatvoriek
                    }else{
                        bracket = 0;
                        while(strcmp(exprList[exprcounter - 2 - bracket].symbol,")")){
                            bracket++;
                        }
                        if(exprList[exprcounter - 2 - bracket].ID != 11 || exprList[exprcounter - 2 - bracket].ID != 12 || exprList[exprcounter - 2 - bracket].ID != 13){
                            fprintf(stderr,"pred binarnym operatorom nie je cislo\n");
                            ThrowError(1);
                            //TODO: GO INTO SYMTABLE AND CHECK IF USING STRING OPERATOR WHEN USING STRING
                        }
                    }
                    operator = true;
                    break;
                case 11:
                case 12:
                case 13:
                    if(operator == true){
                        if(exprcounter >= 2){
                            
                            if(exprList[exprcounter - 2].ID == 2){
                                //all good operator and then term
                                operator = false;
                            }else{
                                bracket = 0;
                                while(strcmp(exprList[exprcounter - 2 - bracket].symbol,"(")){
                                    bracket++;
                                }
                                if(exprList[exprcounter - 2 - bracket].ID != 2){
                                    //TODO ERROR.C
                                    fprintf(stderr,"binarny operator nie je pred cislom\n");
                                    return 0;
                                }
                                //TODO check ci operator pred stringom (ak tam je string) je pouzitelny na string
                                operator = false;
                            }
                        }
                    }
                    break;
                    
            }
            //TODO EXPRESSION END, ADD IT TO TREE
            exprList = realloc(exprList, sizeof(struct Token)*exprcounter);
            exprList[exprcounter-1] = scannedToken;
            expression(scannedToken);
            
        }
        
        printf("Scanning Token %d\n",counter);
        scannedToken = getToken(file);
    }
    printf("Closing parser.\n");
    fclose(file);
    return 0;
}

void parseConstruct(struct Token* tokenlist){
    //construct a tree from a list of tokens, send avh to generace.c

}
