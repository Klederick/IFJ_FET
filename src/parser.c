#include "scanner.c"
//simple state machine
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

int main(int argc, char* argv[]){
    bool inExpression = false;
    int expressionType = -1;
    /*
    0 = int
    1 = string
     */
    struct Token *tokenList = malloc(sizeof);
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
    struct Token scannedToken;
    struct Token tempToken;
    int counter = 0;
    scannedToken = getToken(file);
    while(scannedToken.ID != 0){
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
                expressionType = -1;
            }
            
        }
        
        
        //end of state reset
        if(goSwitch(inExpression)){
            switch(scannedToken.ID){
                case 0: break;
                case 1: if(!inExpression){ inExpression = true; expr_Signal(); } break;
                case 2: break;
                case 3: if(!inExpression){ inExpression = true; expr_Signal(); } break;
                case 4: break;
                case 5: break;
                case 6: break;
                case 7: break;
                case 8: break;
                case 9: break;
                case 10:
                    if(scannedToken.symbol == "while" || scannedToken.symbol == "if" ){         if(!inExpression){
                            inExpression = true; expr_Signal();
                            tempToken = getToken(file);
                        if(strcmp(tempToken.symbol,"(")){
                            counter++;
                            tokenList = realloc(sizeof(struct Token)*counter);
                            tokenList[counter - 1] = tempToken;
                        }else{
                            fprintf(stderr,"No brackets after while/if statement\n");
                            fprintf(stderr,"Correct usage if/while( expression op expression    ){...\n");
                            return 0;
                        }
                    } }
                    if(scannedToken.symbol == "return"){
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
            switch(scannedToken.ID){
                case 2:
                        switch(expressionType){
                            case 0:
                                if(tokenList[counter-2].ID == 11){
                                    //is number
                                }else if(tokenList[counter-2].ID == 13){
                                 //look into indentif table and check type
                                }else{
                                    fprintf("Wrong datatype used in first operand of operation.\n");
                                    return 0;
                                }
                            case 1:
                                if(tokenList[counter-2].ID == 12){
                                    //is string
                                }else if(tokenList[counter-2].ID == 13){
                                 //look into indentif table and check type
                                }else{
                                    fprintf("Wrong datatype used in first operand of operation.\n");
                                    return 0;
                                }
                            default:
                                    fprintf(stderr,"Incorrect flow of tokens in expression\n");
                                    break;
                        }
                    break;
                case 4:
                    break;
                case 11:
                    
                    }
                    
                    
            }
            expression(scannedToken);
        }
        //add token to token list
        tokenList = realloc(sizeof(struct Token)*counter);
        tokenList[counter - 1] = scannedToken;
        
        printf("Scanning Token %d\n",counter);
        scannedToken = getToken(file);
    }
    printf("Closing parser.\n");
    fclose(file);
    return 0;
}
