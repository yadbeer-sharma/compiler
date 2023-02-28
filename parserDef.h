#include "lexerDef.h"

struct treeNode{
    struct treeNode * sibling;
    struct treeNode * child;
    int key;
    int lnNum;
    char lexeme[21];
    union valueIfNum v;
    int isLeafNode;
    char* symbol;
    char* parentSymbol;
};

struct stackElement{
    struct TOKEN tok;
    struct treeNode * nodeAddr;
};

struct stackNode{
    struct stackElement stEle;
    struct stackNode* next;
};

struct stack{
    struct stackNode * top;
    int size;
};