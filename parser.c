#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parserDef.h"
#include "parser.h"
#include "lexer.c"

int NUM_TERM = 63;
int NUM_NONTERM = 143;
int NUM_GRAMRULES;
int *grammar[];

int isTerm(struct TOKEN tk)
{
    if (tk.tok >= 1 && tk.tok <= 61)
        return 1;
    else
        return 0;
}

struct stack createStack()
{
    struct stack s;
    s.top = NULL;
    s.size = 0;
    return s;
}

void printNode(struct treeNode *tn, FILE *fp)
{
    // lexemeCurrentNode lineno tokenName valueIfNumber
    // parentNodeSymbol isLeafNode(yes/no) nodeSymbol
    char *numVal;
    char *tokenName;
    char *lexemeCurrentNode;
    char *parentNodeSymbol = " "; // TODO inverse hash
    char *isLeafNode;
    char *nodeSymbol = " "; // TODO inverse hash

    if (tn->symbol == NUM || tn->symbol == RNUM)
        numVal = tn->lexeme;
    else
        numVal = "----";

    struct TOKEN tk;
    tk.tok = tn->symbol;
    if (isTerm(tk))
    {
        lexemeCurrentNode = tn->lexeme;
        tokenName = " ";
        isLeafNode = "Yes";
    } // TODO inverse hash here
    else
    {
        lexemeCurrentNode = "----";
        tokenName = "----";
        isLeafNode = "No";
    }

    int n = tn->lnNum;

    fprintf(fp, "%s,\t%d,\t%s,\t,%s,\t%s,\tisfLeafNode : %s,\t%s\n", lexemeCurrentNode, n, tokenName, numVal, parentNodeSymbol, isLeafNode, nodeSymbol);
}

void printParseTree(struct treeNode *tn, char *outfile)
{
    FILE *fp = fopen(outfile, "w");
    struct TOKEN tk;
    tk.tok = tn->symbol;
    if (isTerm(tk))
    { // NOTE that for printing leaf node we are checking if it's a terminal or not, and not that it's child is NULL
        printNode(tn, fp);
        return;
    }
    printParseTree(tn->child, outfile);
    printNode(tn, fp);
    struct treeNode *tmp = tn->child->sibling;
    while (tmp != NULL)
    {
        printParseTree(tmp, outfile);
        tmp = tmp->sibling;
    }
}

int isEmpty(struct stack s)
{
    return (s.top == NULL) ? 1 : 0;
}

struct stack push(struct stackElement e, struct stack s)
{
    struct stack s1;
    s1.top = (struct stackNode *)malloc(sizeof(struct stackNode));
    s1.top->ele = e;
    s1.top->next = s.top;
    s1.size = s.size + 1;
    return s1;
}

struct stackElement top(struct stack s)
{
    return s.top->ele;
}

struct stack pop(struct stack s)
{
    struct stack s1;
    struct stackNode *temp;
    temp = s.top;
    s1.top = s.top->next;
    s1.size = s.size - 1;
    free(temp);
    return s1;
}

int hash_t_support(char *key, char *T)
{
    int ret = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        ret += ((T[i % 12]) * (key[i]));
    }
    return (ret % 93);
}

int hash_t(char *terminal)
{
    int G[] = {0, 0, 0, 0, 72, 0, 70, 0, 30, 0, 0, 70, 0, 0, 70, 0, 0,
               40, 53, 0, 64, 84, 57, 50, 89, 31, 0, 46, 65, 80, 0, 0, 55, 66, 77, 20,
               41, 59, 0, 52, 49, 45, 0, 73, 46, 0, 58, 0, 83, 30, 80, 0, 0, 5, 0, 70,
               7, 0, 87, 0, 0, 10, 47, 19, 0, 49, 70, 0, 3, 56, 0, 88, 68, 90, 21, 14,
               17, 0, 37, 78, 31, 12, 61, 60, 39, 0, 56, 0, 73, 81, 51, 51, 0};

    return ((G[hash_t_support(terminal, "vcOr4EuYSHTh")] +
             G[hash_t_support(terminal, "TUiwsT1ZPoGS")]) %
            93) +
           1;
}

int hash_nt_support(char *key, char *T)
{
    int ret = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        ret += ((T[i % 23]) * (key[i]));
    }
    return (ret % 105);
}

int hash_nt(char *nonterminal)
{
    int G[] = {0, 0, 0, 0, 0, 56, 0, 49, 0, 0, 0, 9, 0, 0, 0, 96, 0,
               35, 56, 0, 0, 64, 62, 18, 0, 0, 39, 51, 0, 41, 66, 24, 0, 2, 31, 20, 0,
               76, 41, 0, 0, 35, 55, 40, 58, 0, 0, 13, 86, 61, 33, 98, 0, 96, 42, 23,
               0, 103, 12, 34, 10, 103, 9, 6, 40, 11, 79, 92, 86, 30, 0, 40, 50, 90,
               72, 44, 15, 92, 6, 17, 0, 37, 43, 0, 29, 71, 96, 26, 0, 93, 33, 2, 11,
               45, 0, 31, 16, 69, 72, 75, 32, 60, 101, 84, 0};

    return (G[hash_nt_support(nonterminal, "UlgFf2DbXzntR3XpXIkitLL")] +
            G[hash_nt_support(nonterminal, "KWW60mhuIm5hVAaAulu8ijr")]) %
               105 +
           70;
}

void removeTikona(char *token)
{
    int len = strlen(token);
    char tokBufM[len - 2];
    for (int i = 1; i < len - 1; i++)
    {
        tokBufM[i - 1] = token[i];
    }
    memset(token, '\0', strlen(token) * sizeof(char));
    strncpy(token, tokBufM, len - 2);
}

int fileNumLines(FILE *fp)
{
    char ch;
    int numLines = 1;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
            numLines++;
    }
    fseek(fp, 0, SEEK_SET);
    return numLines;
}

int checkTikona(char *token)
{
    if (*token == '<')
        return 1;
    return 0;
}

void parseInputSourceCode(char *testcaseFile, int *parseTable[])
{
    FILE *fp = fopen(testcaseFile, "r");
    struct TOKEN currTok;
    struct stack s1 = createStack();
    struct stackElement stEle;
    stEle.nodeAddr = NULL;
    struct TOKEN tk;
    tk.tok = -2;
    stEle.tok = tk;
    struct stack s2 = push(stEle, s1);
    struct stackElement stEle2;
    struct treeNode *tn = (struct treeNode *)malloc(sizeof(struct treeNode));
    stEle2.nodeAddr = tn;
    tn->parentSymbol = 11111; // TODO for root symbol
    int lineNum = 0;
    struct TOKEN tk2;
    tk2.tok = 126;
    tk2.lineno = 0;
    stEle2.tok = tk2;
    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    *s = push(stEle2, s2);
    while (1)
    {
        currTok = getNextToken();
        if (currTok.tok == -1 && (top(*s)).tok.tok != -2)
        {
            // TODO error : input is consumed but stack is not empty
        }
        else
            return; // TODO end of lexical analysis
        if (currTok.tok == ERROR1 || currTok.tok == ERROR2 || currTok.tok == ERROR3 || currTok.tok == ERROR4)
        {
            // TODO error handling
        }
        else
        {
            struct stackElement tp = top(*s);
            if (tp.tok.tok == 62)
                *s = pop(*s);
            else if (isTerm(tp.tok))
            {
                if (currTok.tok == tp.tok.tok)
                {
                    *s = pop(*s);
                    strcpy(tp.nodeAddr->lexeme, currTok.lexeme);
                    lineNum = currTok.lineno;
                    if (currTok.tok == NUM)
                        tp.nodeAddr->v.i = atoi(currTok.lexeme);
                    else if (currTok.tok == RNUM)
                        tp.nodeAddr->v.f = ator(currTok.lexeme);
                    /* struct treeNode * tn = (struct treeNode*) malloc(sizeof(struct treeNode));
                    tn->isLeafNode = 1;
                    tn->key = tp.tok.tok;
                    strcpy(tn->lexeme, tp.tok.lexeme);
                    tn->lnNum = tp.tok.lineno;
                    tn->symbol = tp.tok.tok;
                     */
                }
                else
                {
                    // TODO terminal mismatch with stack top
                }
            }
            else if (tp.tok.tok == -2)
            {
                // TODO error : stack empty but input is not yet consumed
            }
            else
            {
                if (parseTable[tp.tok.tok][currTok.tok] == -1)
                {
                    // TODO error : parseTable entry is empty
                }
                else
                {
                    int rule = parseTable[tp.tok.tok][currTok.tok];
                    *s = pop(*s);
                    struct stackElement *tmp_stele1 = (struct stackElement *)malloc(sizeof(struct stackElement));
                    // struct TOKEN *tmp_tk1 = (struct TOKEN *)malloc(sizeof(struct TOKEN));
                    tmp_stele1->tok.tok = grammar[rule][1];
                    struct treeNode *prev = (struct treeNode *)malloc(sizeof(struct treeNode));
                    prev->symbol = grammar[rule][1];
                    tp.nodeAddr->child = prev;
                    prev->lnNum = lineNum;
                    prev->parentSymbol = tp.nodeAddr->symbol;
                    tmp_stele1->nodeAddr = prev;
                    *s = push(*tmp_stele1, *s);
                    for (int i = 2; i < 15; i++)
                    {
                        if (grammar[rule][i] == -1)
                            break;
                        struct stackElement *tmp_stele = (struct stackElement *)malloc(sizeof(struct stackElement));
                        // struct TOKEN *tmp_tk = (struct TOKEN *)malloc(sizeof(struct TOKEN));
                        tmp_stele->tok.tok = grammar[rule][i];
                        struct treeNode *tmp_tn = (struct treeNode *)malloc(sizeof(struct treeNode));
                        tmp_stele->nodeAddr = tmp_tn;
                        tmp_tn->lnNum = lineNum;
                        tmp_tn->parentSymbol = tp.tok.tok;
                        tmp_tn->symbol = grammar[rule][i];
                        prev->sibling = tmp_tn;
                        prev = tmp_tn;
                        *s = push(*tmp_stele, *s);
                    }
                    prev->sibling = NULL;
                }
            }
        }
    }
}

int main()
{

    FILE *gram = fopen("grammar.txt", "r");

    if (gram == NULL)
    {
        printf("Error opening grammar file");
        return 0;
    }

    int numLines = fileNumLines(gram);
    NUM_GRAMRULES = numLines;
    int grammar[NUM_GRAMRULES][15];
    for (int i = 0; i < NUM_GRAMRULES; i++)
        for (int j = 0; j < 15; j++)
            grammar[i][j] = -1;

    int F[NUM_NONTERM][2][NUM_TERM];
    for (int i = 0; i < NUM_NONTERM; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < NUM_TERM; k++)
                F[i][j][k] = -1;
        }
    }

    int parseTable[NUM_NONTERM][NUM_TERM];
    for (int i = 0; i < NUM_NONTERM; i++)
        for (int j = 0; j < NUM_TERM; j++)
            parseTable[i][j] = -1;

    char ch;
    char tokBuf[512];
    int i = 0;

    while (fgets(tokBuf, 512, gram) != NULL)
    {
        int j = 0;
        char delim[] = " ";

        char *token = strtok(tokBuf, delim);

        if (checkTikona(token))
        {
            removeTikona(token);
            grammar[i][j] = hash_nt(token);
        }
        else
        {
            grammar[i][j] = hash_t(token);
        }
        j++;

        while ((token = strtok(NULL, " ")) != NULL)
        {
            if (token[strlen(token) - 1] == '\n')
            {
                token[strlen(token) - 1] = '\0';
            }

            if (checkTikona(token))
            {
                removeTikona(token);
                grammar[i][j] = hash_nt(token);
            }
            else
                grammar[i][j] = hash_t(token);
            j++;
        }
        i++;
    }

    for (int i = 0; i < NUM_GRAMRULES; i++)
        for (int j = 0; j < 15; j++)
            printf("%d\n", grammar[i][j]);

    fclose(gram);

    return 0;
}

void computeFirstAndFollow(int gram[NUM_GRAMRULES][15], int f[NUM_NONTERM][2][NUM_TERM])
{
    /////////////////// creating grammar index table /////////////////////////////////

    int nt_rule_count[NUM_NONTERM]; // index to calculate grammar rule index
    memset(nt_rule_count, 0, NUM_NONTERM * sizeof(int));

    int rule_index[NUM_NONTERM][10]; // grammar rule index
    memset(rule_index, -1, NUM_NONTERM * (10 * sizeof(int)));

    for (int i = 0; i < NUM_GRAMRULES; i++)
    {
        int temp_nt = gram[i][0];
        int temp_col_no = nt_rule_count[temp_nt]++;

        rule_index[temp_nt][temp_col_no] = i;
    }
    ///////////////////  First set ////////////////////////////////////////////////////

    int fcal[NUM_NONTERM]; // to store which first set have been calculated
    memset(fcal, 0, NUM_NONTERM * sizeof(int));

    for (int i = 0; i < NUM_GRAMRULES; i++)
    {
        if (fcal[gram[i][0]] == 0)
            first(f, gram, rule_index, fcal, gram[i][0]);
    }

    ////////////////// Follow Set /////////////////////////////////////////////////////

    f[gram[0][0]][1][63] = 1; /// $ in follow of start

    ///////////// creating grammar index table for follow /////////////////////////

    memset(nt_rule_count, 0, NUM_NONTERM * sizeof(int));

    int fo_rule_index[NUM_NONTERM][2][30];
    memset(fo_rule_index, -1, NUM_NONTERM * (2 * (30 * sizeof(int))));

    for (int i = 0; i < NUM_GRAMRULES; i++)
    {
        for (int j = 1; j < 15; j++)
        {
            if (gram[i][j] == -1)
                break;
            if (gram[i][j] < 70)
                break;
            fo_rule_index[gram[i][j]][0][nt_rule_count[gram[i][j]]++] = i;
            fo_rule_index[gram[i][j]][1][nt_rule_count[gram[i][j]]++] = j;
        }
    }
    ////////////////////////////////////////////////////////////////////////////

    int focal[NUM_NONTERM]; // to store which follow set have been calculated
    memset(fcal, 0, NUM_NONTERM * sizeof(int));

    for (int i = 0; i < NUM_NONTERM; i++)
    {
        if (focal[i] == 0 && fo_rule_index[i][0][0] != -1)
            follow(f, gram, fo_rule_index, focal, i);
    }
}

void follow(int f[NUM_NONTERM][2][NUM_TERM], int gram[NUM_GRAMRULES][15], int rule_index[NUM_NONTERM][2][30], int fcal[NUM_NONTERM], int inde)
{
    for (int i = 0; i < 30; i++)
    {
        if (rule_index[inde][0][i] == -1)
            break;

        int x = rule_index[inde][0][i];
        int y = rule_index[inde][1][i];

        if (gram[x][y + 1] == -1)
        {
            if (fcal[gram[x][0]] == 0)
                follow(f, gram, rule_index, fcal, gram[x][0]);
            for (int k = 0; k < NUM_TERM; k++)
            {
                if (f[gram[x][0]][1][k] == 1)
                    f[inde][1][k] = 1;
            }
        }
        else
        {
            int fl_fo = 0;
            for (int j = y + 1; j < 20; j++)
            {
                if (f[gram[x][j]][0][62] != -1)
                    fl_fo = 1;
                for (int k = 0; k < NUM_TERM; k++)
                {
                    if (f[gram[x][j]][0][k] != -1 && k != 62)
                        f[inde][1][k] = 1;
                }
            }
            if (fl_fo)
            {
                if (fcal[gram[x][0]] == 0)
                    follow(f, gram, rule_index, fcal, gram[x][0]);
                for (int k = 0; k < NUM_TERM; k++)
                {
                    if (f[gram[x][0]][1][k] == 1)
                        f[inde][1][k] = 1;
                }
            }
        }
    }
    fcal[inde] = 1;
}

void do_union(int f[NUM_NONTERM][2][NUM_TERM], int index_of_rhs, int index_of_lhs, int curr_rule)
{
    for (int i = 0; i < NUM_TERM; i++)
    {
        if (f[index_of_rhs][0][i] != -1)
            f[index_of_lhs][0][i] = curr_rule;
    }
    return;
}

void first(int f[NUM_NONTERM][2][NUM_TERM], int gram[NUM_GRAMRULES][15], int rule_index[NUM_NONTERM][10], int fcal[NUM_NONTERM], int inde)
{
    ///////////base case, when it is a terminal ////////////////

    if (inde < NUM_TERM)
    {
        f[inde][0][inde] = 999;
        fcal[inde] = 1;
        return;
    }
    ////////////////////////////////////////////////////////////
    for (int i = 0; i < 10; i++)
    {
        if (rule_index[inde][i] == -1)
            break;
        else
        {
            int curr_rule = rule_index[inde][i];
            int flag_null = 0;
            for (int j = 1; j < 15; j++)
            {
                if (gram[curr_rule][j] == -1)
                    break;

                if (fcal[gram[curr_rule][j]] == 0)
                    first(f, gram, rule_index, fcal, gram[curr_rule][j]);

                if (f[gram[curr_rule][j]][0][62] == -1)
                {
                    do_union(f, gram[curr_rule][j], inde, curr_rule);
                    flag_null = 1;
                    break;
                }
                else
                {
                    do_union(f, gram[curr_rule][j], inde, curr_rule);
                }
            }
            if (flag_null == 1)
                f[inde][0][62] = -1;
        }
    }
    fcal[inde] = 1;
    return;
}

void createParseTable(int f[NUM_NONTERM][2][NUM_TERM], int parTab[NUM_NONTERM][NUM_TERM])
{
    for (int i = 0; i < NUM_NONTERM; i++)
    {
        if (f[i][0][62] == -1)
        {
            for (int j = 0; j < NUM_TERM; j++)
                parTab[i][j] = f[i][0][j];
        }
        else
        {
            int e_rule = f[i][0][62];

            for (int j = 0; j < NUM_TERM; j++)
                if (f[i][0][j] != e_rule)
                    parTab[i][j] = f[i][0][j];

            for (int j = 0; j < NUM_TERM; j++)
                if (f[i][1][j] != -1)
                    parTab[i][j] = e_rule;
        }
    }
    return;
}
