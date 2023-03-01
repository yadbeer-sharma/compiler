#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

int hash_t_support(char *key, char *T);
int hash_t(char *terminal);
int hash_nt_support(char *key, char *T);
int hash_nt(char *nonterminal);
void removeTikona(char* token);
int fileNumLines(FILE *fp);
int checkNT(char *token);
struct treeNode gentreeNode(struct treeNode * sibling,
    struct treeNode * child,
    int key,
    int lnNum,
    char lexeme[21],
    union valueIfNumber v,
    int isLeafNode,
    char* symbol,
    char* parentSymbol);

struct stack createStack();
int isEmpty(struct stack s);
struct stack push(struct stackElement ele, struct stack s);
struct stack pop(struct stack s);
struct stackElement top(struct stack s);
