
union valueIfNum
{ /* usage : valueIfNum v = 25; then use V.i */
    int i;
    float f;
};


struct treeNode{
    struct treeNode * sibling;
    struct treeNode * child;
    int lnNum;
    char lexeme[21];
    union valueIfNum v;
    int symbol;
    int parentSymbol;
};

struct stackElement{
    struct TOKEN tok;
    struct treeNode * nodeAddr;
};

struct stackNode{
    struct stackElement ele;
    struct stackNode* next;
};

struct stack{
    struct stackNode * top;
    int size;
};