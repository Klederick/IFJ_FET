#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "structs.h"
#include "stack.c"
#include "scanner.c"
#include "expression.c"
#include "symtable.c"
#include "error.c"
#include "stringstack.c"
#define SYMBOL_LIMIT 100
#define ID_NUM 18
//simple state machine



/*
Special cases or groups in parsing:
function declaration

*/
//make 2 trees for expressions, access from parseConstruct

bool goSwitch(bool arg1){
    if(arg1){
        return false;
    }else{
        return true;
    }
}
//starts and ends an expression
void expr_Signal(ExpressionStack* expr_stack, ExpressionStack* node_stack, int expressionCounter, eNode** expressions){
    struct Token scannedToken;
    scannedToken.ID = 14; scannedToken.symbol = "$";
    printf("Ending expression with $\n");
    //add to tree
    
    expressions[expressionCounter - 1] = expression(expr_stack, node_stack, scannedToken);
}
//check if it is term
bool isterm(struct Token token){
    if(token.ID == 12 || token.ID == 13 || token.ID == 11){
        return true;
    }else{
        if(strcmp(token.symbol,"(") == 0 || strcmp(token.symbol,")") == 0){
            return true;
        }else{
            return false;
        }
        }
}


//check if expected
void addToExpectedIDList(int* tokenIDs, int argnum,...) {
    va_list valist;
    va_start(valist, argnum);
    //RESET LIST
    for(int i = 0; i < ID_NUM; i++){
        tokenIDs[i] = 0;
    }
    //SET NEW COMMENTS
    for (int i = 0; i < argnum; i++) {
        tokenIDs[va_arg(valist, int)] = 1;
    }
    va_end(valist);
}


void addToExpectedSymbolList(char*** ExpectedSymbolList, int SymbolListLen, int argnum,...) {
    va_list valist;
    va_start(valist, argnum);
    //RESET LIST

    *ExpectedSymbolList = realloc(*ExpectedSymbolList,sizeof(char*) * argnum);
    
    for(int i = 0; i < argnum; i++){
        printf("FUNCLOG\n");
        (*ExpectedSymbolList)[i] = realloc((*ExpectedSymbolList)[i],SYMBOL_LIMIT);
        printf("FUNCLOG\n");
        (*ExpectedSymbolList)[i] = va_arg(valist, char*);
        printf("FUNCLOG\n");
    }

    va_end(valist);
}
//check if expected
bool ExpectedID(int* IDs, struct Token token){
    for(int i = 0; i < ID_NUM; i++){
        if(IDs[i] == 1){
            if(token.ID == i){
                return true;
            }
        }
    }
    return false;
}
bool ExpectedSymbol(int length,char** symbols, struct Token token){
    for(int i = 0; i < length; i++){
        if(strcmp(symbols[i],token.symbol) == 0){
            return true;
        }
    }
    return false;
}
//END OF HELPING FUNCS

void parseConstruct(int counter,struct Token* tokenlist, int expressionCounter, eNode** expressions){
    tNode_t command = newNode(tokenlist[0].symbol,tokenlist[0].ID);
    for(int i = 0; i < counter; i++){
        //Semantic controls
        printf("FOR LOOP %d out of %d: ",i,counter-1);
        switch(tokenlist[i].ID){
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 6: break;
            case 7: break;
            case 8: break;
            case 9: break;
            case 10: break;
            case 11: break;
            case 12: break;
            case 13: break;
            default: break;
        }
        printf("ADDING (%d) - %s to tree\n",tokenlist[i].ID,tokenlist[i].symbol);
        insert(command, tokenlist[i].symbol,tokenlist[i].ID );
    }
    //zavolat generaciu
    //construct a tree from a list of tokens, send avh to generace.c

}
//parse function (tokens -> tokens List to form AVH)
int parse(FILE* file){
    //Stacks
    //Expression stack
    ExpressionStack expr_stack;
    initializeExpressionStack(&expr_stack);
    //node stack
    ExpressionStack node_stack;
    initializeExpressionStack(&node_stack);
    bool inExpression = false;
    struct Token *tokenList = malloc(sizeof(struct Token));
    struct Token *exprList = malloc(sizeof(struct Token));
    //parsing
    //tokens
    struct Token scannedToken;
    struct Token tempToken;
    //counters
    int counter = 0;
    int exprcounter = 0;
    //expression bracket counters
    int exprbracket = 0;
    //bools for different states
    bool operator = false;
    bool finish = false;
    int expressionReset = 0;
    //expected tables
    int symbolListLen = 0;
    char** ExpectedSymbolList = malloc(sizeof(char*));
    ExpectedSymbolList[0] = malloc(SYMBOL_LIMIT);
    ExpectedSymbolList[0] = "Hello";
    int* ExpectedIDsList = malloc(sizeof(int)*ID_NUM);
    for(int i = 0; i < ID_NUM; i++){
        ExpectedIDsList[i] = 1;
    }
    //Tree for n expressions and a statement
    tNode_t statement = newNode("EMPTY",0);
    int* expressionCounter = malloc(sizeof(int));

    *(expressionCounter) = 0;
    eNode** expressions = malloc(sizeof(eNode*));
    //start parsing
    scannedToken = getToken(file);
    while(scannedToken.ID != 0 && finish == false){
        if(expressionReset == 1){
            inExpression = true;
            expressionReset = 0;
            initializeExpressionStack(&expr_stack);
            initializeExpressionStack(&node_stack);
        }
        printf("Token %d: (%d) %s (spaces behind: %d)\n",counter,scannedToken.ID,scannedToken.symbol,scannedToken.spacesBehind);
       
        //reset states if wrong ID
        if(inExpression){
            if((scannedToken.ID == 2 || scannedToken.ID == 11 || scannedToken.ID == 13 || scannedToken.ID == 12) && (ExpectedID(ExpectedIDsList, scannedToken) || ExpectedSymbol(symbolListLen, ExpectedSymbolList, scannedToken))){
                
                
            }else if((scannedToken.ID == 4 && (exprbracket != 0 || strcmp(scannedToken.symbol,"(") == 0)) && (ExpectedID(ExpectedIDsList, scannedToken) || ExpectedSymbol(symbolListLen, ExpectedSymbolList, scannedToken))){
                if(strcmp(scannedToken.symbol,"(") == 0){
                    exprbracket++;
                }else{
                    exprbracket--;
                }

            }else{
                //turn off expression
                addToExpectedIDList(ExpectedIDsList, 2, 3,4); 
                addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,0); symbolListLen = 0;
                (*expressionCounter)++;
                expressions = realloc(expressions,sizeof(eNode*)*(*expressionCounter));
                if(expressions == NULL){
                    printf("REALLOC FAIL\n");
                    ThrowError(99);
                }
                exprbracket = 0;
                expr_Signal(&expr_stack, &node_stack, *expressionCounter, expressions);
                counter++;
                struct Token exprToken; 
                exprToken.ID = 16; exprToken.symbol = "E";
                tokenList = realloc(tokenList, sizeof(struct Token)*counter);
                tokenList[counter - 1] = exprToken;
                inExpression = false;
                //expressionType = -1;
                exprcounter = 0;
                exprList = malloc(sizeof(struct Token));
            }
            
        }
        

        //Reset expected list, both symbol and id list 
        //SET EXPECTED VALUES WHEN TURNING OFF EXPRESSION!!!!!!!!!!!!!!!
        //end of state reset
        if(goSwitch(inExpression)){
            
             counter++;
            //check if token is in expected
        if((ExpectedID(ExpectedIDsList, scannedToken) || ExpectedSymbol(symbolListLen, ExpectedSymbolList, scannedToken))){
            //all good token is expected
            //add token to list
            printf("Token %d: (%d) %s (spaces behind: %d), ADDING TO LIST ON POSITION %d\n",counter,scannedToken.ID,scannedToken.symbol,scannedToken.spacesBehind,counter-1);
            tokenList = realloc(tokenList, sizeof(struct Token)*counter);
            tokenList[counter - 1] = scannedToken;
        }else{
            //UNEXPECTED TOKEN
            //finish = true;
            //send to next function to construct tree (if possible)
            //RESET EXPRESSION TREES, RESET EVERY LIST, RESET EVERYTHING
            printf("----SENDING TO CONSTRUCT-----\n");
            parseConstruct(counter-1,tokenList,*expressionCounter,expressions);
            //RESET
            tokenList = realloc(tokenList,sizeof(struct Token));
            printf("%s is first token in new statement.\n",scannedToken.symbol);
            tokenList[0] = scannedToken;
            exprList = realloc(exprList,0);
            //counters
            counter = 1;
            exprcounter = 0;
            //expression bracket counters
            exprbracket = 0;
            //bools for different states
            operator = false;
            inExpression = false;
            finish = false;
            expressionReset = 0;
            //expected tables
            
            ExpectedSymbolList = realloc(ExpectedSymbolList,sizeof(char*));
            for (int i = 0; i < symbolListLen; i++) {
                free(ExpectedSymbolList[i]);
            }
            free(ExpectedSymbolList);
            for(int i = 0; i < ID_NUM; i++){
                ExpectedIDsList[i] = 1;
            }
            symbolListLen = 0;
            //Tree for n expressions and a statement
            statement = newNode("EMPTY",0);
            *(expressionCounter) = 0;
            expressions = realloc(expressions,0);

        }
            switch(scannedToken.ID){
                case 0: 
                        break;
                case 1: if(!inExpression){ if(strcmp(scannedToken.symbol,"=") == 0) {expressionReset = 1;} } 
                            if(strcmp(scannedToken.symbol,"=") == 0){
                                addToExpectedIDList(ExpectedIDsList, 4, 13,8,11,12);
                            }else{
                                addToExpectedIDList(ExpectedIDsList, 5, 13,8,11,12,9);
                            }
                            addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,0); symbolListLen = 0;
                        break;
                case 2: 
                        if(strcmp(scannedToken.symbol,"+") == 0 || strcmp(scannedToken.symbol,"??") == 0){
                            addToExpectedIDList(ExpectedIDsList, 3, 13,11,12);
                        }else{
                            addToExpectedIDList(ExpectedIDsList, 2, 13,11); 
                        }
                        addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,1,"("); symbolListLen = 1;
                        break;
                case 3: if(!inExpression){expressionReset = 1;}
                        addToExpectedIDList(ExpectedIDsList, 3, 13,11,12); 
                        addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,1,"(");  symbolListLen = 1;
                        break;
                case 4: 
                        if(strcmp(scannedToken.symbol,"(") == 0){
                            addToExpectedIDList(ExpectedIDsList, 4, 13,4,11,12);
                            addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,1,"_");  symbolListLen = 1;
                        }else{
                            addToExpectedIDList(ExpectedIDsList, 1,2);
                            addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,2,",","->");  symbolListLen = 2;
                        }
                        break;
                case 5: 
                        addToExpectedIDList(ExpectedIDsList, 0);
                        addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,0);  symbolListLen = 0;
                        break;
                case 6: 
                        addToExpectedIDList(ExpectedIDsList, 0);
                        addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,1,"="); symbolListLen = 1;
                        break;
                case 7: 
                        if(strcmp(scannedToken.symbol,"->") == 0){
                            addToExpectedIDList(ExpectedIDsList, 1, 8);
                            addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,0);  symbolListLen = 0;
                        }else{
                            addToExpectedIDList(ExpectedIDsList, 1, 13);
                            addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,0);  symbolListLen = 0;
                        }
                        break;
                case 8: 
                        addToExpectedIDList(ExpectedIDsList, 1, 6);
                        addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,2,")","=");  symbolListLen = 2;
                        break;
                case 9: 
                        addToExpectedIDList(ExpectedIDsList, 0);
                        addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,0);  symbolListLen = 0;
                        break;
                case 10:
                    //expression set
                    if(strcmp(scannedToken.symbol,"while") == 0 || strcmp(scannedToken.symbol,"if") == 0 ){   
                        printf("IN WHILE/IF\n");    
                        tempToken = getToken(file);
                        if(strcmp(tempToken.symbol,"(") == 0){
                            counter++;
                            tokenList = realloc(tokenList, sizeof(struct Token)*counter);
                            tokenList[counter - 1] = scannedToken;
                            printf("Token %d: (%d) %s (spaces behind: %d), ADDING TO LIST ON POSITION %d\n",counter,scannedToken.ID,scannedToken.symbol,scannedToken.spacesBehind,counter);
                            if(!inExpression){
                                expressionReset = 1;
                            } 
                        }else if(strcmp(tempToken.symbol,"let") == 0){
                            ungetToken(file, strlen(tempToken.symbol), tempToken.spacesBehind);
                        }else{ 
                        if(!inExpression){
                            expressionReset = 1;
                        }
                        }
                    }else if(strcmp(scannedToken.symbol,"return") == 0){
                        printf("IN RETURN\n");
                        if(!inExpression){
                            expressionReset = 1;
                        }
                    }
                    //else, func, if, let, return, var, while expected
                    if(strcmp(scannedToken.symbol,"else")==0){
                        addToExpectedIDList(ExpectedIDsList, 0);
                        addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,0);  symbolListLen = 0;
                    }else if(strcmp(scannedToken.symbol,"func")==0){
                        addToExpectedIDList(ExpectedIDsList, 1, 13);
                        addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,0);  symbolListLen = 0;
                    }else if(strcmp(scannedToken.symbol,"if")==0){
                        addToExpectedIDList(ExpectedIDsList, 3, 13,12,11);
                        addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,1, "let");  symbolListLen = 1;
                    }else if(strcmp(scannedToken.symbol,"let")==0){
                        addToExpectedIDList(ExpectedIDsList, 3, 13,12,11);
                        addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,0); symbolListLen = 0;
                    }else if(strcmp(scannedToken.symbol,"return")==0){
                        addToExpectedIDList(ExpectedIDsList, 3, 13,12,11);
                        addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,0);  symbolListLen = 0;
                    }else if(strcmp(scannedToken.symbol,"var")==0){
                        addToExpectedIDList(ExpectedIDsList, 1, 13);
                        addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,0);  symbolListLen = 0;
                    }else if(strcmp(scannedToken.symbol,"while")==0){
                        addToExpectedIDList(ExpectedIDsList, 3, 13,12,11);
                        addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,1,"let");  symbolListLen = 1;
                    }else{
                        printf("UNEXPECTED KEYWORD %s\n",scannedToken.symbol);
                        ThrowError(1);
                    }
                    break;
                case 11: 
                    addToExpectedIDList(ExpectedIDsList, 3, 2,3,17);
                    addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,0);  symbolListLen = 0;
                    break;
                case 12: 
                    addToExpectedIDList(ExpectedIDsList, 2, 3, 17);
                    addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,3,"+","??",")");  symbolListLen = 3;
                    break;
                case 13: 
                    addToExpectedIDList(ExpectedIDsList, 4, 1,2,4,17);
                    addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,0);  symbolListLen = 0;
                    break;
                case 17:
                    printf("LOG1");
                    addToExpectedIDList(ExpectedIDsList, 3, 13,12,11);
                    printf("LOG2");
                    addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,1,"(");  symbolListLen = 1;
                    printf("LOG3");
                    break;
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
                    addToExpectedIDList(ExpectedIDsList, 3, 13,12,11);
                    addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,1,"(");  symbolListLen = 1;
                    if(exprcounter >= 2 && !isterm(exprList[exprcounter-2])){
                        //TODO ERROR.C
                        fprintf(stderr,"Operand before operator is not a term\n");
                        //while pre nekonecno zatvoriek
                    }else{
                        bracket = 0;
                        while(strcmp(exprList[exprcounter - 2 - bracket].symbol,")") == 0){
                            bracket++;
                        }
                        if(exprList[exprcounter - 2 - bracket].ID != 11 && exprList[exprcounter - 2 - bracket].ID != 12 && exprList[exprcounter - 2 - bracket].ID != 13){
                            printf("exprlist-2: %d, %s",exprList[exprcounter-2-bracket].ID,exprList[exprcounter-2-bracket].symbol);
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
                    printf("LOG %s\n",scannedToken.symbol);
                    addToExpectedIDList(ExpectedIDsList, 1, 2);
                    printf("LOG1\n");
                    addToExpectedSymbolList(&ExpectedSymbolList,symbolListLen,1,")");  symbolListLen = 1;
                    printf("LOG\n");
                    if(operator == true){
                        if(exprcounter >= 2){
                            
                            if(exprList[exprcounter - 2].ID == 2){
                                //all good operator and then term
                                operator = false;
                            }else{
                                bracket = 0;
                                while(strcmp(exprList[exprcounter - 2 - bracket].symbol,"(") == 0){
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
            printf("Sending %s %d to expression.\n",scannedToken.symbol,scannedToken.ID);
            expression(&expr_stack, &node_stack, scannedToken);
        }
        
        printf("Scanning Token %d\n",counter);
        scannedToken = getToken(file);
    }
    //expression end
    if(inExpression){
        if(scannedToken.ID == 2 || scannedToken.ID == 4 || scannedToken.ID == 11 || scannedToken.ID == 13 || scannedToken.ID == 12){
                //all good
        }else{
                //turn off expression
                (*expressionCounter)++;
                expressions = realloc(expressions,sizeof(eNode*)*(*expressionCounter));
                if(expressions == NULL){
                    printf("REALLOC FAIL\n");
                    ThrowError(99);
                }
                expr_Signal(&expr_stack, &node_stack, *expressionCounter, expressions);
                counter++;
                struct Token exprToken; 
                exprToken.ID = 16; exprToken.symbol = "E";
                tokenList = realloc(tokenList, sizeof(struct Token)*counter);
                tokenList[counter - 1] = exprToken;
                printf("after expression: counter - %d, top - %s\n",*expressionCounter,expressions[*expressionCounter-1]->token.symbol);
                inExpression = false;
                //expressionType = -1;
                exprcounter = 0;
                exprList = malloc(sizeof(struct Token));
            }
            
    }
    //last statement
    if(counter != 0){
            printf("--------SENDING TO CONSTRUCT----------\n");
            parseConstruct(counter,tokenList,*expressionCounter,expressions);
    }
    printf("Closing parser.\n");
    fclose(file);
    return 0;
}

