#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.c"

int NUM_TERM;
int NUM_NONTERM;
int NUM_GRAMRULES;

int fileNumLines(FILE *fp)
{
    char ch;
    int numLines = 1;
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch=='\n')
            numLines++;
    }
    return numLines;
}

int ifNT(char *token)
{
    if (*token == '<')
        return 1;
    return 0;
}

int main()
{
    FILE *gram = fopen("grammar.txt", "r");
    char ch;
    int numLines = 1;
    while (ch != EOF)
    {
        ch = fgetc(gram);
        if (ch = '\n')
            numLines++;
    }
    printf("%d\n", numLines);
    char* tokBuf;
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
    for(int i =0; i<NUM_NONTERM; i++){
        for(int j = 0; j<NUM_TERM; j++)
            parseTable[i][j] = -1;
    }
    return 0;
}