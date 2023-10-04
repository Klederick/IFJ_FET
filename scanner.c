#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    TOKEN_IDENTIFIKATOR,
    TOKEN_ZAVORKA_OTVIRACI,
    TOKEN_ZAVORKA_ZAVIRACI,
    TOKEN_OPERATOR,
    TOKEN_KONSTANTA,
    TOKEN_KLICOVE_SLOVO,
    TOKEN_ODDELOVAC,
    TOKEN_NEPOZNANY
} TokenType;

TokenType zjistiTypTokenu(const char *token) {
    const char *klicovaSlova[] = {"let", "var", "func", "class", "if", "else", "for", "while", "return"};
    for (int i = 0; i < sizeof(klicovaSlova) / sizeof(klicovaSlova[0]); i++) {
        if (strcmp(token, klicovaSlova[i]) == 0) {
            return TOKEN_KLICOVE_SLOVO;
        }
    }
    if (isalpha(token[0]) || token[0] == '_') {
        return TOKEN_IDENTIFIKATOR;
    }
    if (token[0] == '(') {
        return TOKEN_ZAVORKA_OTVIRACI;
    } else if (token[0] == ')') {
        return TOKEN_ZAVORKA_ZAVIRACI;
    }
    if (strchr("+-*/=<>!&|%", token[0]) != NULL) {
        return TOKEN_OPERATOR;
    } else if (strchr(",;:", token[0]) != NULL) {
        return TOKEN_ODDELOVAC;
    }
    if (isdigit(token[0])) {
        bool isKonstanta = true;
        for (int i = 1; i < strlen(token); i++) {
            if (!isdigit(token[i]) && token[i] != '.') {
                isKonstanta = false;
                break;
            }
        }
        return isKonstanta ? TOKEN_KONSTANTA : TOKEN_NEPOZNANY;
    }
    return TOKEN_NEPOZNANY;
}

void ulozTokenDoSouboru(FILE *outputFile, TokenType typTokenu, const char *token) {
    switch (typTokenu) {
        case TOKEN_IDENTIFIKATOR:
            fprintf(outputFile, "Identifikátor: %s\n", token);
            break;
        case TOKEN_ZAVORKA_OTVIRACI:
            fprintf(outputFile, "Otvírací závorka: %s\n", token);
            break;
        case TOKEN_ZAVORKA_ZAVIRACI:
            fprintf(outputFile, "Zavírací závorka: %s\n", token);
            break;
        case TOKEN_OPERATOR:
            fprintf(outputFile, "Operátor: %s\n", token);
            break;
        case TOKEN_KONSTANTA:
            fprintf(outputFile, "Konstanta: %s\n", token);
            break;
        case TOKEN_KLICOVE_SLOVO:
            fprintf(outputFile, "Klíčové slovo: %s\n", token);
            break;
        case TOKEN_ODDELOVAC:
            fprintf(outputFile, "Oddělovač: %s\n", token);
            break;
        default:
            fprintf(outputFile, "Nepoznaný token: %s\n", token);
            break;
    }
}

int main() {
    FILE *inputFile;
    FILE *outputFile;
    int ch, nextCh;
    bool inSingleLineComment = false;
    int inMultiLineComment = 0;
    bool inWord = false;
    char token[100] = "";
    int tokenIndex = 0;

    inputFile = fopen("vstup.txt", "r");
    if (inputFile == NULL) {
        perror("Nelze otevřít soubor vstup.txt");
        return 1;
    }

    outputFile = fopen("vystup.txt", "w");
    if (outputFile == NULL) {
        perror("Nelze vytvořit soubor vystup.txt");
        fclose(inputFile);
        return 1;
    }

    while ((ch = fgetc(inputFile)) != EOF) {
        if (inSingleLineComment) {
            if (ch == '\n') {
                inSingleLineComment = false;
            }
        } else if (inMultiLineComment > 0) {
            if (ch == '/') {
                nextCh = fgetc(inputFile);
                if (nextCh == '*') {
                    inMultiLineComment++;
                }
            } else if (ch == '*') {
                nextCh = fgetc(inputFile);
                if (nextCh == '/') {
                    inMultiLineComment--;
                }
            }
        } else {
            if (ch == '/') {
                nextCh = fgetc(inputFile);
                if (nextCh == '/') {
                    inSingleLineComment = true;
                } else if (nextCh == '*') {
                    inMultiLineComment = 1;
                } else {
                    fputc(ch, outputFile);
                    fputc(nextCh, outputFile);
                }
            } else if (isspace(ch) || strchr("+-*/=<>!&|%,;:(){}", ch) != NULL) {
                if (inWord) {
                    token[tokenIndex] = '\0';
                    TokenType typTokenu = zjistiTypTokenu(token);
                    ulozTokenDoSouboru(outputFile, typTokenu, token);
                    tokenIndex = 0;
                    inWord = false;
                }
            } else {
                token[tokenIndex++] = ch;
                inWord = true;
            }
        }
    }

    // Tato část zkontroluje a uloží do souboru poslední token, pokud ještě není ukončený
    if (inWord) {
        token[tokenIndex] = '\0';
        TokenType typTokenu = zjistiTypTokenu(token);
        ulozTokenDoSouboru(outputFile, typTokenu, token);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
