#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lexer.c"

int NUM_TERM = 64;
int NUM_NONTERM = 145;
int NUM_GRAMRULES;
// int *grammar[];

void first(int f[NUM_NONTERM][2][NUM_TERM], int gram[NUM_GRAMRULES][15], int rule_index[NUM_NONTERM][10], int fcal[NUM_NONTERM], int inde);
void follow(int f[NUM_NONTERM][2][NUM_TERM], int gram[NUM_GRAMRULES][15], int rule_index[NUM_NONTERM][2][30], int fcal[NUM_NONTERM], int inde);
void computeFirstAndFollow(int gram[NUM_GRAMRULES][15], int f[NUM_NONTERM][2][NUM_TERM]);
void createParseTable(int f[NUM_NONTERM][2][NUM_TERM], int parTab[NUM_NONTERM][NUM_TERM], int grammar[NUM_GRAMRULES][15]);

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

void printNode(struct treeNode *tn, FILE *fp2)
{
    // lexemeCurrentNode lineno tokenName valueIfNumber
    // parentNodeSymbol isLeafNode(yes/no) nodeSymbol
    char *numVal;
    char *tokenName;
    char *lexemeCurrentNode;
    char *parentNodeSymbol = invhash[tn->parentSymbol];
    char *isLeafNode;
    char *nodeSymbol = invhash[tn->symbol];
    printf("printNode is called\n");
    if (tn->symbol == NUM || tn->symbol == RNUM)
        // strcpy(numVal, tn->lexeme);
        numVal = tn->lexeme;

    else
        numVal = "----";

    struct TOKEN tk;
    tk.tok = tn->symbol;
    if (isTerm(tk))
    {
        // strcpy(&lexemeCurrentNode, tn->lexeme);
        lexemeCurrentNode = tn->lexeme;
        // strcpy(&tokenName, invhash[tn->symbol]);
        tokenName = invhash[tn->symbol];
        // strcpy(&isLeafNode, "Yes");
        isLeafNode = "Yes";
    }
    else
    {
        // printf("here\n");
        // strcpy(&lexemeCurrentNode, "----");
        lexemeCurrentNode = "----";
        // strcpy(&tokenName, "----");
        tokenName = "----";
        // strcpy(&isLeafNode, "No");
        isLeafNode = "No";
    }

    int n = tn->lnNum;

    FILE* fp1=fopen("outFile.txt","a+");
    printf("%s,\t%d,\t%s,\t,%s,\t%s,\tisfLeafNode : %s,\t%s\n", 
    &lexemeCurrentNode, n, &tokenName, &numVal, parentNodeSymbol, &isLeafNode, nodeSymbol);

    fprintf(fp1, "%s,\t%d,\t%s,\t,%s,\t%s,\tisfLeafNode : %s,\t%s\n", lexemeCurrentNode, n, tokenName, numVal, parentNodeSymbol, isLeafNode, nodeSymbol);
    // printf("printNode is ended\n");
    fclose(fp1);

}

void printParseTree(struct treeNode *tn, FILE *fp1)
{
    struct TOKEN tk;
    tk.tok = tn->symbol;
    if (isTerm(tk))
    { // NOTE that for printing leaf node we are checking if it's a terminal or not, and not that it's child is NULL
        printNode(tn, fp1);
        // printf("%d\n", tk.tok);

    printf("inside printing!\n");
        return;
    }
    printParseTree(tn->child, fp1);
    printNode(tn, fp1);
    // printf("%d\n", tn->symbol);
    struct treeNode *tmp = tn->child->sibling;
    while (tmp != NULL)
    {
        printParseTree(tmp, fp1);
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
    return (ret % 128);
}

int hash_nt(char *nonterminal)
{
    int G[] = {0, 0, 15, 0, 18, 0, 0, 0, 0, 0, 18, 97, 122, 0, 0, 23,
               0, 98, 27, 22, 72, 0, 49, 0, 84, 22, 114, 65, 0, 79, 0, 0, 0, 0, 13, 0,
               63, 12, 57, 0, 0, 87, 0, 41, 47, 14, 55, 0, 47, 0, 0, 0, 18, 14, 121,
               17, 14, 42, 18, 118, 69, 0, 119, 0, 9, 0, 3, 19, 10, 0, 4, 0, 0, 102,
               51, 44, 0, 92, 0, 0, 54, 9, 0, 0, 64, 105, 59, 38, 18, 0, 27, 28, 105,
               106, 0, 94, 5, 0, 36, 30, 0, 0, 0, 47, 72, 95, 0, 49, 0, 124, 39, 45,
               20, 0, 0, 31, 0, 0, 25, 0, 0, 41, 0, 0, 62, 100, 123, 10};

    return (G[hash_nt_support(nonterminal, "4NSNCi1PklHjc9KfCnPeEQ8")] +
            G[hash_nt_support(nonterminal, "n9pIjFAR7hLfLOWd47plOlk")]) %
               128 +
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

void parseInputSourceCode(char *testcaseFile, int parseTable[NUM_NONTERM][NUM_TERM], int grammar[NUM_GRAMRULES][15])
{

    /*     for(int i = 0; i < NUM_NONTERM; i++){
            for(int j = 0; j < NUM_TERM; j++){
                printf("%d ", parseTable[i][j]);
            }
            printf("\n");
        } */

    // printf("testcase file is %s\n", testcaseFile);

    /* for(int i = 0; i < NUM_GRAMRULES; i++){
        for(int j = 0; j < 15; j++){
            printf("%d ", grammar[i][j]);
        }
        printf("\n");
    } */

    FILE *fp = fopen(testcaseFile, "r");
    struct TOKEN currTok = getNextToken();
    int lineNum = currTok.lineno;
    struct stack s = createStack();

    struct stackElement btOfStack;
    btOfStack.tok.tok = -2;
    s = push(btOfStack, s);

    struct stackElement programNT;
    programNT.tok.tok = program;
    programNT.tok.lineno = currTok.lineno;
    struct treeNode *rootNode = (struct treeNode *)malloc(sizeof(struct treeNode));
    rootNode->sibling = NULL;
    rootNode->parentSymbol = 145;
    strcpy(rootNode->lexeme, "----");
    // printf("rootnode lexeme = %s \n", rootNode->lexeme);
    programNT.nodeAddr = rootNode;
    s = push(programNT, s);

    while (1)
    // for(int i = 0; i<70; i++)
    {
        if (isEmpty(s))
            printf("stack is empty!\n");
        if (currTok.tok == -1 && (top(s)).tok.tok != -2)
        {
            break;
            // TODO error : input is consumed but stack is not empty
        }
        else if (currTok.tok == -1)
            break; // TODO end of lexical analysis
        if (currTok.tok == ERROR1 || currTok.tok == ERROR2 || currTok.tok == ERROR3 || currTok.tok == ERROR4)
        {
            switch (currTok.tok)
            {
            case ERROR1:
                printf("Error on line %d : Invalid Numeric Literal!\n", currTok.lineno);
                break;
            case ERROR2:
                printf("Error on line %d : found expression of type a.b or !a or a=b\n", currTok.lineno);
                break;
            case ERROR3:
                printf("Error on line %d : Unidentified character!\n", currTok.lineno);
                break;
            case ERROR4:
                printf("Error on line %d : Lexeme length exceeds 20 characters!\n", currTok.lineno);
                break;
            }
        }
        else
        {
            struct stackElement tp = top(s);
            printf("stack top is : %s\n", invhash[tp.tok.tok]);
            printf("stack size is ; %d\n", s.size);
            if (tp.tok.tok == e)
                s = pop(s);
            else if (isTerm(tp.tok))
            {
                // printf("Termina comp: %d %d\n", currTok.tok, tp.tok.tok);
                if (currTok.tok == tp.tok.tok)
                {
                    // printf("current token is %s\n", invhash[currTok.tok]);
                    s = pop(s);
                    printf("%s is popped\n", invhash[tp.tok.tok]);
                    printf("%s is on top now\n", invhash[top(s).tok.tok]);

                    strcpy(tp.nodeAddr->lexeme, currTok.lexeme);
                    // tp.nodeAddr->lexeme = currTok.lexeme;

                    // int j = 0;
                    // while(currTok.lexeme[j]!='\0'){
                    //     tp.nodeAddr->lexeme[j] = currTok.lexeme[j];
                    //     j++;
                    // }

                    printf("lexeme succ copied!\n");
                    lineNum = currTok.lineno;
                    tp.nodeAddr->child = NULL;
                    tp.nodeAddr->lnNum = lineNum;
                    tp.nodeAddr->sibling = NULL;
                    tp.nodeAddr->symbol = currTok.tok;
                    printf("here!\n");

                    // if (currTok.tok == NUM)
                    //     tp.nodeAddr->v.i = atoi(currTok.lexeme);
                    // else if (currTok.tok == RNUM)
                    //     tp.nodeAddr->v.f = atof(currTok.lexeme);
                    currTok = getNextToken();
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
                    break;
                }
            }
            else if (tp.tok.tok == -2)
            {

                break;
                // TODO error : stack empty but input is not yet consumed
            }
            else
            {
                // printf("tp.tok.tok= %d, currTok.tok= %d\n", tp.tok.tok, currTok.tok);
                // printf("parseTable entry is : %d\n", parseTable[tp.tok.tok][currTok.tok]);
                if (parseTable[tp.tok.tok][currTok.tok] == -1)
                {
                    printf("%d %d", tp.tok.tok, currTok.tok);
                    printf("error : parseTable entry is empty\n");
                    break;
                    // TODO error : parseTable entry is empty
                }
                else
                {

                    int rule = parseTable[tp.tok.tok][currTok.tok];
                    // printf("top token is :  %s\n", invhash[tp.tok.tok]);
                    printf("rule no is %d, for token %s\n", rule, invhash[currTok.tok]);
                    s = pop(s);
                    printf("%s is popped\n", invhash[tp.tok.tok]);

                    int i = 14;
                    while (i > 0)
                    {
                        if (grammar[rule][i] != -1)
                            break;
                        i--;
                    }
                    // printf("TO BE PUSHED : %d\n", i);

                    struct treeNode *prev = (struct treeNode *)malloc(sizeof(struct treeNode));
                    prev->lnNum = lineNum;
                    prev->parentSymbol = tp.tok.tok;
                    prev->symbol = grammar[rule][i];
                    prev->sibling = NULL;
                    struct stackElement *tmp_stele = (struct stackElement *)malloc(sizeof(struct stackElement));
                    tmp_stele->tok.tok = grammar[rule][i];
                    tmp_stele->nodeAddr = prev;
                    s = push(*tmp_stele, s);
                    i--;
                    while (i > 0)
                    {
                        struct stackElement *tmp_stele1 = (struct stackElement *)malloc(sizeof(struct stackElement));
                        tmp_stele1->tok.tok = grammar[rule][i];
                        struct treeNode *nwtn = (struct treeNode *)malloc(sizeof(struct treeNode));
                        nwtn->lnNum = lineNum;
                        nwtn->parentSymbol = tp.tok.tok;
                        nwtn->sibling = prev;
                        nwtn->symbol = grammar[rule][i];
                        tmp_stele1->nodeAddr = nwtn;
                        s = push(*tmp_stele1, s);

                        prev = nwtn;
                        i--;
                    }

                    /* struct stackElement *tmp_stele1 = (struct stackElement *)malloc(sizeof(struct stackElement));

                    int j = 14;
                    for(; j>0; j--){
                        if(grammar[rule][j]!=-1)
                        break;
                    }

                    tmp_stele1->tok.tok = grammar[rule][j];
                    struct treeNode *prev = (struct treeNode *)malloc(sizeof(struct treeNode));
                    prev->symbol = grammar[rule][j];
                    tp.nodeAddr->child = prev;
                    prev->lnNum = lineNum;
                    prev->parentSymbol = tp.nodeAddr->symbol;
                    tmp_stele1->nodeAddr = prev;
                    s = push(*tmp_stele1, s);
                    j--;
                    for (; j > 0; j--)
                    {
                        if (grammar[rule][i] == -1)
                            continue;
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
                        s = push(*tmp_stele, s);
                    }
                    prev->sibling = NULL; */
                }
            }
        }
    }
    printf("while broke!\n");
    // FILE *fp1 = fopen("outFile.txt", "w");
    // printParseTree(tn, fp1);

    struct treeNode *tn1 = malloc(sizeof(struct treeNode));
    struct treeNode *tn2 = malloc(sizeof(struct treeNode));
    struct treeNode *tn3 = malloc(sizeof(struct treeNode));
    struct treeNode *tn4 = malloc(sizeof(struct treeNode));
    struct treeNode *tn5 = malloc(sizeof(struct treeNode));

    tn1->child = tn2;
    tn2->child = tn3;
    tn4->child = tn5;
    tn2->sibling = tn4;
    tn1->parentSymbol = 145;
    tn1->symbol = 71;
    tn2->symbol = 72;
    tn4->symbol = 74;
    tn3->symbol = 1;
    tn5->symbol = 2;
    tn2->parentSymbol = tn1->symbol;
    tn4->parentSymbol = tn1->symbol;
    tn3->parentSymbol = tn2->symbol;
    tn5->parentSymbol = tn4->symbol;
    tn3->sibling = NULL;
    tn5->sibling = NULL;
    tn1->sibling = NULL;

    // printf("lexemeCurrentNode lineno tokenName valueIfNumber parentNodeSymbol isLeafNode(yes/no) nodeSymbol\n");
    FILE *fp1 = fopen("outFile.txt", "w");
    printParseTree(rootNode, fp1);
    fclose(fp1);
}

int parser(char *testcasefile)
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

    int sync[NUM_NONTERM][NUM_TERM];
    for (int i = 0; i < NUM_NONTERM; i++)
        for (int j = 0; j < NUM_TERM; j++)
            sync[i][j] = -1;

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

    fclose(gram);

    computeFirstAndFollow(grammar, F);

    createParseTable(F, parseTable, grammar);

    // printf(" checking %d", parseTable[statement][GET_VALUE]);
    parseInputSourceCode(testcasefile, parseTable, grammar);
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

    for (int i = 0; i < NUM_TERM; i++)
        f[i][0][i] = 999;
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

            fo_rule_index[gram[i][j]][0][nt_rule_count[gram[i][j]]] = i;
            fo_rule_index[gram[i][j]][1][nt_rule_count[gram[i][j]]++] = j;
        }
    }

    ////////////////////////////////////////////////////////////////////////////

    int focal[NUM_NONTERM]; // to store which follow set have been calculated
    memset(focal, 0, NUM_NONTERM * sizeof(int));
    // printf("%d \n",fo_rule_index[102][0][0]);
    for (int i = 0; i < NUM_NONTERM; i++)
    {
        if (focal[i] == 0 && fo_rule_index[i][0][0] != -1)
            follow(f, gram, fo_rule_index, focal, i);
    }
}

void follow(int f[NUM_NONTERM][2][NUM_TERM], int gram[NUM_GRAMRULES][15], int rule_index[NUM_NONTERM][2][30], int fcal[NUM_NONTERM], int inde)
{

    if (inde >= 0 && inde < NUM_TERM)
    {
        f[inde][1][inde] = 1;
        fcal[inde] = 1;
        return;
    }
    for (int i = 0; i < 30; i++)
    {

        if (rule_index[inde][0][i] == -1)
            break;

        int x = rule_index[inde][0][i];
        int y = rule_index[inde][1][i];

        if (gram[x][y + 1] == -1)
        {
            if (gram[x][0] == inde)
            {
                continue;
            }
            if (fcal[gram[x][0]] == 0)
                follow(f, gram, rule_index, fcal, gram[x][0]);
            for (int k = 0; k < NUM_TERM; k++)
            {
                if (f[gram[x][0]][1][k] != -1)
                    f[inde][1][k] = x;
            }
        }
        else
        {
            int fl_fo = 1;
            for (int j = y + 1; j < 20; j++)
            {

                if (fl_fo == 0)
                    break;

                if (gram[x][j] == -1)
                    break;
                if (f[gram[x][j]][0][62] == -1)
                    fl_fo = 0;
                for (int k = 0; k < NUM_TERM; k++)
                {

                    if (f[gram[x][j]][0][k] != -1 && k != 62)
                    {
                        f[inde][1][k] = x;
                    }
                }
            }
            if (fl_fo)
            {

                if (fcal[gram[x][0]] == 0)
                    follow(f, gram, rule_index, fcal, gram[x][0]);
                for (int k = 0; k < NUM_TERM; k++)
                {
                    if (f[gram[x][0]][1][k] != -1)
                        f[inde][1][k] = x;
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
        // printf("%d\n",curr_rule);
    }
    return;
}

void first(int f[NUM_NONTERM][2][NUM_TERM], int gram[NUM_GRAMRULES][15], int rule_index[NUM_NONTERM][10], int fcal[NUM_NONTERM], int inde)
{
    ///////////base case, when it is a terminal ////////////////

    if (inde < NUM_TERM && inde >= 0)
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

void createParseTable(int f[NUM_NONTERM][2][NUM_TERM], int parTab[NUM_NONTERM][NUM_TERM], int grammar[NUM_GRAMRULES][15])
{
    // printf("%d \n\n",f[72][1][48]);
    for (int i = 0; i < NUM_GRAMRULES; i++)
    {
        int j = 1;
        int flag = 1;
        while (grammar[i][j] != -1)
        {
            for (int k = 0; k < NUM_TERM; k++)
            {
                if (f[grammar[i][j]][0][k] != -1)
                    parTab[grammar[i][0]][k] = i;
            }
            if (f[grammar[i][j]][0][62] != -1)
            {
                j++;
            }
            else
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {

            for (int k = 0; k < NUM_TERM; k++)
            {
                if (f[grammar[i][0]][1][k] != -1)
                    parTab[grammar[i][0]][k] = i;
            }
        }
    }
    //     for (int i = 0; i < NUM_NONTERM; i++)
    //     {
    //         if (f[i][0][62] == -1)
    //         {
    //             for (int j = 0; j < NUM_TERM; j++)
    //                 parTab[i][j] = f[i][0][j];
    //         }
    //         else
    //         {
    //             int e_rule = f[i][0][62];

    //             for (int j = 0; j < NUM_TERM; j++)
    //                 if (f[i][0][j] != e_rule)
    //                     parTab[i][j] = f[i][0][j];

    //             for (int j = 0; j < NUM_TERM; j++)
    //                     parTab[i][j] = f[i][1][j];
    //         }
    //     }
    //     return;
}

void populateSyncSets(int sync[NUM_NONTERM][NUM_TERM], int f[NUM_NONTERM][2][NUM_TERM])
{
    for (int i = 0; i < NUM_NONTERM; i++)
    {
        for (int j = 0; j < NUM_TERM; j++)
        {
            sync[i][j] = f[i][1][j];
        }
        sync[i][49]++; // makes the semicol index non-negative (semicol part of sync set for all non terminals)
        sync[i][12]++; // adding START to sync set of all non-terms
    }
}
