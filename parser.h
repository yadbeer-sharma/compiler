#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "parserDef.h"

int hash_t_support(char *key, char *T);
int hash_t(char *terminal);
int hash_nt_support(char *key, char *T);
int hash_nt(char *nonterminal);
void removeTikona(char* token);
int fileNumLines(FILE *fp);
int checkNT(char *token);

struct stack createStack();
int isEmpty(struct stack s);
struct stack push(struct stackElement e, struct stack s);
struct stack pop(struct stack s);
struct stackElement top(struct stack s);
