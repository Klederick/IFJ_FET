// 
//	Dear maintainer: 
//  
// Once you are done trying to 'optimize' this routine, 
// and have realized what a terrible mistake that was, 
// please increment the following counter as a warning 
// to the next guy: 
//  
// total_hours_wasted_here = 42 



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.c"
#define NUM_OF_KEYWORDS 11

struct Token {
    char ID;
    char *symbol;
};
//Checks for all whitespaces based on the swift manual
char isWhiteSpace(char c){
    if(c == 32 || c == 9 || c == 10 || c == 13 || c == 11 || c == 12 || c == 0){
        return 1;
    }else{
        return 0;
    }
}
//adds a next char to a token if it meets a certain condition
char nextChar(int* seekcounter, char* c,struct Token *token, int *letterCounter, FILE *src, char condition) {
    if((*c) != EOF){
    (*c) = fgetc(src);
    (*letterCounter)++;
    (*seekcounter)++;
    if (*c == condition) {
        token->symbol = (char *)realloc(token->symbol, (*letterCounter) + 1);
        token->symbol[(*letterCounter) - 1] = (*c);
        token->symbol[(*letterCounter)] = '\0';
        (*seekcounter)--;
        return 1;
    }
    }else{
        return -1;
    }
    return 0;
}
char getChar(int* seekcounter,char *c, FILE *src, int *letterCounter){
    if((*c) != EOF){
        (*c) = fgetc(src); (*letterCounter)++; (*seekcounter)++;
    }else{
        return -1;
    }
    return 0;
}
char isValidTerm(char c){
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_') || (c >= '0' && c <= '9')){
        return 1;
    }else{
        return 0;
    }
}
void assignAndRealloc(int* seekcounter,char c, struct Token *token, int* letterCounter){
    token->symbol = (char *)realloc(token->symbol, (*letterCounter) + 1);
    token->symbol[(*letterCounter) - 1] = c;
    token->symbol[(*letterCounter)] = '\0';
    (*seekcounter)--;
}
unsigned int hexToDec(const char *hex) {
    int dec = 0;

    for (int i = 0; i < 8; i++) {
        char c = hex[i];
        int hexInt;

        if (c >= '0' && c <= '9') {
            hexInt = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            hexInt = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            hexInt = c - 'A' + 10;
        } else {
            fprintf(stderr, "Invalid hex character '%c'\n", c);
                    exit(1);
            return 0;
        }

        dec = (dec << 4) | hexInt;
    }

    return dec;
}

void readEmptyLine(FILE* src){
    char c = fgetc(src);
    if(c == '\n'){

    }else if(isWhiteSpace(c)){
        readEmptyLine(src);
    }else{
        fprintf(stderr,"Invalid character used after \"\"\", The line should be empty because we are waiting for a String!");
        exit(1);
    }
}
char* stringanoff(FILE* src, int condition){
    int numbers = 0;
    int seekOffset = 0;
    char* text = (char*)malloc(2); text[0] = '\0';
    char c;
    while((c = getc(src)) != '\"'){
        printf("Character c before big switch: %c\n",c);
        seekOffset++;
        printf("Character c before big switch: %c\n",c);
        if(c == -1 || c == EOF){ break; }
        if(c == '\\'){
            char temp = '\\';
            c = getc(src);
            seekOffset++;
            switch(c){
                case '\"': text = (char*)realloc(text,strlen(text)+2); strncat(text, "\"", 1); break;
                case 'n': text = (char*)realloc(text,strlen(text)+2); strncat(text, "\n", 1); break;
                case 'r': text = (char*)realloc(text,strlen(text)+2); strncat(text, "\r", 1); break;
                case 't': text = (char*)realloc(text,strlen(text)+2); strncat(text, "\t", 1); break;
                case '\\': text = (char*)realloc(text,strlen(text)+2); strncat(text, "\\", 1); break;
                case 'u': 
                    if( (c = getc(src)) == '{'){
                        char hex[8];
                        for(int i = 0; i < 8; i++){
                            //Get all numbers
                            c = getc(src);
                            if((c < '0') || (c > '9' && c < 'A') || (c > 'F' && c < 'a') || (c > 'f')){ ungetc(c,src); hex[i] = -1; break; }
                            hex[i] = c; numbers++;

                        }
                        c = getc(src);
                        printf("GOT HERE %c, HEX = ",c);
                        for(int i = 0; i < numbers+1; i++){
                            printf("%d, ",hex[i]);
                        }
                        printf("\n");
                        if(c == '}'){
                            //sprav cislo
                            char decnumber = hexToDec(hex);
                            (char*)realloc(text,strlen(text)+2); strncat(text, &decnumber, 1);
                        }else{
                            text = (char*)realloc(text,strlen(text)+numbers+3);
                            strncat(text, "\\",1); strncat(text,"u",1); strncat(text,"{",1); strncat(text,hex,numbers); 
                        }
                    }
                
                break;
                default: printf("Adding a character to the string (temp and c): %c, %c\n",temp,c); text = (char*)realloc(text,strlen(text)+2); strncat(text, &temp, 1); strncat(text, &c, 1); break;
            }
        }else{
            //if everything is okay do this:
            printf("Adding a character to the string (c): %c\n",c); 
            printf("RETURNING TEXT: %s , %d - its length\n",text, strlen(text));
            if((c > 31 && c < 256) || condition == 0){
                printf("RETURNING TEXT: %s , %d - its length\n",text, strlen(text));
                (char*)realloc(text,strlen(text)+2); strncat(text, &c, 1);
            }else{
                fprintf(stderr,"STRING ERROR: Invalid character used %c",c);
                        exit(1);
                ///////////////////////////////////////////STRING ERRROR
            }
        }
    }
    printf("RETURNING TEXT: %s\n",text);
    return text;
}

struct Token getToken(FILE* src){
    //Vars for special cases
    //GOTO FROM COMMENTS HERE 
    int letterCounter = 0;
    int seekCounter = 0;
    int seek = 1;
    int term = 0;
    const char* keywords[][11] = {"Double\0","else\0","func\0","if\0","Int\0","let\0","nil\0","return\0","String\0","var\0","while\0"};

    char c = fgetc(src);
    if(c == EOF){
        seek = 0;
    }
    while(isWhiteSpace(c) == 1){ c = fgetc(src); }
    letterCounter++;

    struct Token token;
    token.ID = 0;
    token.symbol = (char *)malloc(letterCounter+1);
    token.symbol[letterCounter-1] = c; token.symbol[letterCounter] = '\0';
    //get operands, if no operands -> go default for a term
    switch(c){
        case '\"':
                c = fgetc(src); if(c != '\"'){ fseek(src,-1,SEEK_CUR); token.symbol = stringanoff(src, 0);  }
                c = fgetc(src); if(c != '\"'){ fseek(src,-2,SEEK_CUR); /*vrat prazdny string*/ return token; }else{ readEmptyLine(src); token.symbol = stringanoff(src, 1); }
                break;
        //'='
        case '=':
                //== case
                nextChar(&seekCounter,&c,&token,&letterCounter,src,'=');
                break;
        case ':':
                break;
        case '*':
                break;
        case '+':
                break;
        case '-':
            //-> case
            nextChar(&seekCounter,&c,&token,&letterCounter,src,'>');
                break;
        case '/':
            if ((c = fgetc(src)) == '/') {
                while ((c = fgetc(src) ) != '\n' && c != -1) {
                    //fprintf(stdout, "%c\n", c);
                        ;
                    }
                token.ID = -1;
                break;
                
                //free(token.symbol); /*WARNING FREE*/
            //}
            }
            else if (c == '*') {
               // Stack* commentStack = (Stack *) malloc (sizeof(Stack));
                Stack commentStack;
                initializeStack(&commentStack);

                int openingComment = 1;
                push(&commentStack, openingComment);
                while(!isEmpty(&commentStack)) {
                    if ((c = fgetc(src)) != EOF) {
                        if (c == '/') {
                            if ((c = fgetc(src)) == '*') {
                                push(&commentStack, openingComment);
                            }
                        }
                        else if (c == '*') {
                            if ((c = fgetc(src)) == '/') {
                                pop(&commentStack);
                                
                                                        
                            }
                        }
                    }
                    else {
                        fprintf(stderr, "Unterminated multi-line comment\n");
                        exit(1);
                    }
                }
                token.ID = -2;        
            }
            break;
        case '(':
           break;
        case ')':
           break;
        case '{':
           break;
        case '}':
           break;
        case '!':
            //!= case
            nextChar(&seekCounter,&c,&token,&letterCounter,src,'=');
               break;
        case '?':
            //?? CASE
            nextChar(&seekCounter,&c,&token,&letterCounter,src,'?');
               break;
        default: 
                if(c >= '0' && c <= '9'){
                    //int / double
                    assignAndRealloc(&seekCounter,c,&token, &letterCounter);
                    getChar(&seekCounter,&c, src, &letterCounter);
                    while(c >= '0' && c <= '9'){
                            assignAndRealloc(&seekCounter,c,&token, &letterCounter);
                            getChar(&seekCounter,&c, src, &letterCounter);
                    }
                    if(c == '.'){
                            assignAndRealloc(&seekCounter,c, &token, &letterCounter);
                            getChar(&seekCounter,&c, src, &letterCounter);
                            while(c >= '0' && c <= '9'){
                                assignAndRealloc(&seekCounter,c,&token, &letterCounter);
                                getChar(&seekCounter,&c, src, &letterCounter);
                            }
                    }
                    if(c == 'e' || c == 'E'){
                            assignAndRealloc(&seekCounter,c,&token, &letterCounter);
                            getChar(&seekCounter,&c, src, &letterCounter);
                            if(c == '+' || c == '-'){
                                assignAndRealloc(&seekCounter,c, &token, &letterCounter);
                                getChar(&seekCounter,&c, src, &letterCounter);
                            }
                            while(c >= '0' && c <= '9'){
                            assignAndRealloc(&seekCounter,c,&token, &letterCounter);
                            getChar(&seekCounter,&c, src, &letterCounter);
                            }
                    }

                }else if(c == '_')
                    getChar(&seekCounter,&c,src,&letterCounter);
                    if(isWhiteSpace(c)){
                    //_ used in functions to skip argument name 
                    break;
                    }else{
                        assignAndRealloc(&seekCounter,c,&token,&letterCounter);    // toto by sa malo dat spravit mudrejsie
                        term = 1;
                    }
                
                if(isValidTerm(c)){
                        term = 1;
                        getChar(&seekCounter,&c,src,&letterCounter);
                        while(isValidTerm(c)){
                            assignAndRealloc(&seekCounter,c,&token,&letterCounter);
                            getChar(&seekCounter,&c,src,&letterCounter);
                        }
                }else{
                    if(c == EOF || c == -1){
                        token.ID = 0;
                        token.symbol = NULL;
                    }
                }
                break;
    }
    if(seek = 1){
    fseek(src,-seekCounter,SEEK_CUR);
    }
    if(term == 1){
        for(int i = 0; i < NUM_OF_KEYWORDS; i++){
            if(strcmp(token.symbol,keywords[0][i]) == 0){
                //printf("KEYWORD!!");
                //Is a Keyword
                //printf("Compared %s to %s",token.symbol,keywords[0][i]);
            }
        }
    }
    return token;
    free(token.symbol);
}

int main(int argc, char* argv[]){
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
    struct Token temp = getToken(file);
    printf("%s\n",temp.symbol);
    while(fgetc(file) != -1){
        fseek(file,-1,SEEK_CUR);
        temp = getToken(file);
        printf("%s\n",temp.symbol);
    }
    fclose(file);
    return 0;
}
