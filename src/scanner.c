// 
//	Dear maintainer: 
//  
// Once you are done trying to 'optimize' this routine, 
// and have realized what a terrible mistake that was, 
// please increment the following counter as a warning 
// to the next guy: 
//  
// total_hours_wasted_here = 42 

#include <string.h>
#include "stack.c"
#define NUM_OF_KEYWORDS 11
const char* keywords[][11] = {{"Double\0","else\0","func\0","if\0","Int\0","let\0","nil\0","return\0","String\0","var\0","while\0"}};


//Checks for all whitespaces based on the swift manual
char isWhiteSpace(char c){
    if(c == 32 || c == 9 || c == 10 || c == 13 || c == 11 || c == 12 || c == 0){
        return 1;
    }else{
        return 0;
    }
}
//adds a next char to a token if it meets a certain condition, then assigns
char nextChar(int* seekcounter, char* c,struct Token *token, int *letterCounter, FILE *src, char condition, int condID) {
    if((*c) != EOF){
    (*c) = fgetc(src);
    (*letterCounter)++;
    (*seekcounter)++;
    if (*c == condition) {
        token->symbol = (char *)realloc(token->symbol, (*letterCounter) + 1);
        token->symbol[(*letterCounter) - 1] = (*c);
        token->symbol[(*letterCounter)] = '\0';
        (*seekcounter)--;
        token->ID = condID;
        return 1;
    }
    }else{
        return -1;
    }
    return 0;
}
//get char with helping flags, seek is for looking ahead for operators that require multiple symbols
char getChar(int* seekcounter,char *c, FILE *src, int *letterCounter){
    if((*c) != EOF){
        (*c) = fgetc(src); (*letterCounter)++; (*seekcounter)++;
    }else{
        return -1;
    }
    return 0;
}
//is number || is letter || is '_'
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
//used in /u{} cases
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
//is the line after multiline string empty?
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
//parse through string, resolve special cases 
char* stringanoff(FILE* src, int condition){
    int numbers = 0;
    int seekOffset = 0;
    char* text = (char*)malloc(2); text[0] = '\0';
    char c;
    int whileCondition = 1;
    if(condition == 0){
        if((c = fgetc(src)) != '\"'){
            whileCondition = 1;
        }else{
            whileCondition = 0;
        }
    }else{
        if((c = fgetc(src)) == '\"'){
                seekOffset++;
            if((c = fgetc(src)) == '\"'){
                    seekOffset++;
                if((c = fgetc(src)) == '\"'){
                    seekOffset++;
                    //whileCondition = 0;
                }}}
        if(seekOffset < 3)
        {
            fseek(src,-seekOffset,SEEK_CUR);
            whileCondition = 1;
        }else{
            whileCondition = 0;
        }
    }
    while(whileCondition){
        seekOffset = 0;
        printf("Character c before big switch: %c\n",c);
        seekOffset++;
        if(c == -1 || c == EOF){ break; }
        if(c == '\\' && condition == 0){
            char temp = '\\';
            c = fgetc(src);
            seekOffset++;
            switch(c){
                case '\"': text = (char*)realloc(text,strlen(text)+3); strncat(text, "\"", 2); break;
                case 'n': text = (char*)realloc(text,strlen(text)+3); strncat(text, "\n", 2); break;
                case 'r': text = (char*)realloc(text,strlen(text)+3); strncat(text, "\r", 2); break;
                case 't': text = (char*)realloc(text,strlen(text)+3); strncat(text, "\t", 2); break;
                case '\\': text = (char*)realloc(text,strlen(text)+3); strncat(text, "\\", 2); break;
                case 'u': 
                    if( (c = fgetc(src)) == '{'){
                        char hex[8];
                        for(int i = 0; i < 8; i++){
                            //Get all numbers
                            c = fgetc(src);
                            if((c < '0') || (c > '9' && c < 'A') || (c > 'F' && c < 'a') || (c > 'f')){ ungetc(c,src); hex[i] = -1; break; }
                            hex[i] = c; numbers++;

                        }
                        c = fgetc(src);
                        printf("GOT HERE %c, HEX = ",c);
                        for(int i = 0; i < numbers+1; i++){
                            printf("%d, ",hex[i]);
                        }
                        printf("\n");
                        if(c == '}'){
                            //sprav cislo
                            char decnumber = hexToDec(hex);
                            text = (char*)realloc(text,strlen(text)+2); strncat(text, &decnumber, 1);
                        }else{
                            text = (char*)realloc(text,strlen(text)+numbers+5);
                            strncat(text, "\\u{",4); strncat(text,hex,numbers); 
                        }
                    }
                
                break;
                default: printf("Adding a character to the string (temp and c): %c, %c\n",temp,c); text = (char*)realloc(text,strlen(text)+2); strncat(text, &temp, 1); strncat(text, &c, 1); break;
            }
        }else{
            //if everything is okay do this:
            printf("Adding a character to the string (c): %c\n",c);
            if((c > 31 && c != 127) || condition == 1){
                text = (char*)realloc(text,strlen(text)+2); strncat(text, &c, 1);
            }else{
                fprintf(stderr,"STRING ERROR: Invalid character used %c",c);
                        exit(1);
                ///////////////////////////////////////////STRING ERRROR
            }
            printf("RETURNING TEXT: %s , %lu - its length\n",text, strlen(text));
        }
        //reset condition
        seekOffset = 0;
            if(condition == 0){
        if((c = fgetc(src)) != '\"'){
            whileCondition = 1;
        }else{
            whileCondition = 0;
        }
    }else{
        if((c = fgetc(src)) == '\"'){
                seekOffset++;
            if((c = fgetc(src)) == '\"'){
                    seekOffset++;
                if((c = fgetc(src)) == '\"'){
                    seekOffset++;
                    //whileCondition = 0;
                }}}
        if(seekOffset < 3)
        {
            fseek(src,-seekOffset,SEEK_CUR);
            whileCondition = 1;
        }else{
            if(text[strlen(text)-1] == '\n'){
                text[strlen(text)-1] = '\0';
            }
            whileCondition = 0;
        }
        }
    }
    text[strlen(text)] = '\0';
    printf("RETURNING TEXT: %s\n",text);
    fseek(src, 0, SEEK_CUR);
    return text;
}


/*
ID:
:,=			                                    1
+,-,*,/,??		                                2
==,!=,<,>,<=,>=		                            3
(,)			                                    4
{,}			                                    5
?,!			                                    6
_,->,			                                7
String, Int, Double	                            8
nil			                                    9
else, func, if, let, return, var, while	        10
termnumber				                        11
termstring				                        12
identif                                         13
*/

struct Token getToken(FILE* src){
    //Vars for special cases
    //GOTO FROM COMMENTS HERE 
    int letterCounter = 0;
    int seekCounter = 0;
    int seek = 1;
    int term = 0;

    char c = fgetc(src);
    printf("First char of token: %c\n",c);
    if(c == EOF || c == -1){
        seek = 0;
    }
    
    struct Token token;
    token.ID = 0;
    token.symbol = (char *)malloc(letterCounter+1);
    token.symbol[letterCounter-1] = c; token.symbol[letterCounter] = '\0';
    token.spacesBehind = 0;

    if(c == EOF || c == -1){
        seek = 0;
        return token;
    }

    while(isWhiteSpace(c) == 1){ c = fgetc(src); token.spacesBehind++; }
    letterCounter++;

    //get operands, if no operands -> go default for a term
    char opening[3]; 
    switch(c){
        case '\"':
                opening[0] = '\"';
                c = fgetc(src); if(c != '\"'){ fseek(src,-1,SEEK_CUR); token.symbol = stringanoff(src, 0); token.ID = 12; return token;  }else{ opening[1] = '\"'; }
                c = fgetc(src); if(c != '\"'){ fseek(src,-2,SEEK_CUR); /*vrat prazdny string*/ token.ID = 12; return token; }else{ opening[2] = '\"'; }
                if(strcmp(opening,"\"\"\"\0")){
                    readEmptyLine(src); token.symbol = stringanoff(src, 1); token.ID = 12;
                }else{
                    fprintf(stderr,"Wrong string declaration, use \"string\" or \"\"\"\nstring\n\"\"\"\n");
                }
                break;
        //'='
        case '=':
                //== case
                if(nextChar(&seekCounter,&c,&token,&letterCounter,src,'=',3) == 1){
                    //token je ==
                }else{
                    token.ID = 1;
                    token.symbol = "=";
                };
                
                break;
        case ':':
                token.ID = 1;
                token.symbol = ":";
                break;
        case '*':
                break;
        case '+':
                token.ID = 2;
                token.symbol = "+";
                break;
        case '-':
            //-> case
            if(nextChar(&seekCounter,&c,&token,&letterCounter,src,'>',7) == 1){
                //is -> token
            }else{
                token.ID = 2;
                token.symbol = "-";
            };
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
            }else{
                token.ID = 2;
                token.symbol = "/";
            }
            break;
        case '(':
                token.ID = 4;
                token.symbol = "("; 
           break;
        case ')':
                token.ID = 4;
                token.symbol = ")"; 
           break;
        case '{':
                token.ID = 5;
                token.symbol = "{"; 
           break;
        case '}':
                token.ID = 5;
                token.symbol = "}"; 
           break;
        case '<':
            if(nextChar(&seekCounter,&c,&token,&letterCounter,src,'=',3) == 1){
                token.symbol = "<=";
            }else{
                token.ID = 3;
                token.symbol = "<";
            }
            break;
        case '>':
            if(nextChar(&seekCounter,&c,&token,&letterCounter,src,'=',3) == 1){
                token.symbol = ">=";
            }else{
                token.ID = 3;
                token.symbol = ">";
            }
            break;
        case '_':

        case '!':
            //!= case
            if(nextChar(&seekCounter,&c,&token,&letterCounter,src,'=',3) == 1){
                //token is !=
            }else{
                token.ID = 6;
                token.symbol = "!";
            }
               break;
        case '?':
            //?? CASE
            if(nextChar(&seekCounter,&c,&token,&letterCounter,src,'?',2) == 1){
                //token is ??
            }else{
                token.ID = 6;
                token.symbol = "?";
            }
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
                token.ID = 11;
                }else if(c == '_')
                    getChar(&seekCounter,&c,src,&letterCounter);
                    if(isWhiteSpace(c)){
                    //_ used in functions to skip argument name 
                        token.ID = 7;
                        token.symbol = "_";
                    break;
                    }else{
                        token.ID = 12;
                        assignAndRealloc(&seekCounter,c,&token,&letterCounter);    // toto by sa malo dat spravit mudrejsie
                        term = 1;
                    }
                
                if(isValidTerm(c)){
                        term = 1;
                        getChar(&seekCounter,&c,src,&letterCounter);
                        token.ID = 13;
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
    
    if(seek == 1){
    fseek(src,-seekCounter,SEEK_CUR);
    }
    if(term == 1){
        for(int i = 0; i < NUM_OF_KEYWORDS; i++){
            if(strcmp(token.symbol,keywords[0][i]) == 0){
                //printf("KEYWORD!!");
                //Is a Keyword
                //printf("Compared %s to %s",token.symbol,keywords[0][i]);
                if(i == 6){
                    //is nil
                    token.ID = 9;
                    strcpy(token.symbol,keywords[0][i]);
                }else if(i == 0 || i == 4 || i == 8){
                    //is datatype
                    token.ID = 8;
                    strcpy(token.symbol,keywords[0][i]);
                }else{
                    //is keyword
                    token.ID = 10;
                    strcpy(token.symbol,keywords[0][i]);
                }
            }
        }
    }
    if(token.ID < 0){
        token.symbol = "";
    }
    return token;
    free(token.symbol);
}
/*
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
        printf("end: %s\n",temp.symbol);
    }
    fclose(file);
    return 0;
}*/ //OLD MAIN
