
/*STACK.C*/

#ifndef STRUCTS_H
#define STRUCTS_H
#define MAX_SIZE 100

struct Token {
    char ID;
    char *symbol;
    int spacesBehind;
};

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void initializeStack(Stack *stack);

int isFull(Stack *stack);

int isEmpty(Stack *stack);

void push(Stack *stack, int value);

int pop(Stack *stack);

int peek(Stack *stack);


/*SYMTABLE.C*/
typedef struct tNode {
    char *key;
    int nodeType;
    int height;
    struct tNode *lptr;
    struct tNode *rptr;
} *tNode_t;


int max(int a, int b);

int height(tNode_t node);

int getBalance(tNode_t node);

tNode_t newNode(char *key, int nodeType);

tNode_t rightRotate(tNode_t y);

tNode_t leftRotate(tNode_t x);

tNode_t insert(tNode_t node, char *key, int nodeType);

tNode_t search(tNode_t node, char *key);

void symtabInsert(tNode_t *tree, char *key, int nodeType);

void symtabInorder(tNode_t tree);

void symtabPostorder(tNode_t tree);

void symtabPreorder(tNode_t tree);

void destroyTree(tNode_t tree);

tNode_t initializeTree();

/*EXPRESSION.C*/
typedef struct expressionNode{
    struct Token token;
    struct expressionNode *left;
    struct expressionNode *right;
}eNode;

enum ItemType{
    TOKEN,
    NODE,
};

typedef struct expressionItem{
    enum ItemType type;
    union {
        eNode *e_node;
        struct Token token;
    } value;
} expressionItem;

typedef struct {
    expressionItem *data;
    int top;
    int size;
} ExpressionStack;

eNode* expression(ExpressionStack* expr_stack, ExpressionStack* node_stack, struct Token token);

int findStringInColumn(const char* a);

int findStringInRow(const char* b);

char* getStringFromCoordinates(int col, int row);

void add(ExpressionStack* expr_stack, struct Token token, expressionItem tmp, ExpressionStack* temp_stack);

void reduce(ExpressionStack* node_stack, ExpressionStack* expr_stack, struct Token token);

void equal(ExpressionStack* expr_stack, struct Token token);

eNode* expression(ExpressionStack* expr_stack, ExpressionStack* node_stack, struct Token token);

/*STRINGSTACK.C*/

void resize(ExpressionStack *stack);

void initializeExpressionStack(ExpressionStack *stack);

int isExpressionStackFull(ExpressionStack *stack);

int isExpressionStackEmpty(ExpressionStack *stack);

void pushE(ExpressionStack *stack, expressionItem item);

void popE(ExpressionStack *stack);

expressionItem peekE(ExpressionStack *stack);

void dispozeStackE(ExpressionStack *stack);

/*dynamic.c*/
// Define the structure for a node
struct Dynamic {
    int dataType;
    void* genericPtr;
    struct Dynamic* next;
};
//PARSER FUNCS
bool goSwitch(bool arg1);
void expr_Signal(ExpressionStack* expr_stack, ExpressionStack* node_stack, int expressionCounter, eNode** expressions);
bool isterm(struct Token token);
void addToExpectedIDList(int* tokenIDs, int argnum, ...);
void addToExpectedSymbolList(char*** ExpectedSymbolList, int SymbolListLen, int argnum, ...);
bool ExpectedID(int* IDs, struct Token token);
bool ExpectedSymbol(int length, char** symbols, struct Token token);
void parseConstruct(int counter, struct Token* tokenlist, int expressionCounter, eNode** expressions);
int parse(FILE* file);

//SCANNER FUNCS
char isWhiteSpace(char c);
char nextChar(int* seekcounter, char* c, struct Token* token, int* letterCounter, FILE* src, char condition, int condID);
char getChar(int* seekcounter, char* c, FILE* src, int* letterCounter);
char isValidTerm(char c);
void assignAndRealloc(int* seekcounter, char c, struct Token* token, int* letterCounter);
unsigned int hexToDec(const char* hex);
void readEmptyLine(FILE* src);
char* stringanoff(FILE* src, int condition);
struct Token getToken(FILE* src);
void ungetToken(FILE* src, int tokenLen, int tokenWspace);

#endif // STRUCTS_H
