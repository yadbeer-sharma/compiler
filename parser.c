#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.c"

int NUM_TERM;
int NUM_NONTERM;
int NUM_GRAMRULES;

void removeTikona(char* token)
{
    int len = strlen(token);
    char tokBufM[len-2];
    for(int i = 1; i < len-1; i++){
        tokBufM[i-1] = token[i]; 
    }
    memset(token, '\0',sizeof(token));
    strncpy(token,tokBufM,len-2);   
}

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

int checkNT(char *token)
{
    if (*token == '<')
        return 1;
    return 0;
}

int main()
{
   
    FILE *gram = fopen("grammar.txt", "r");
    
    if (gram == NULL) {
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
    
    
    char ch;
    char tokBuf[80];
    int i=0;
    
    
    while(fgets(tokBuf,80,gram)!=NULL)
    {
        char* token = "init"; 
        int j=0;
        while(token!=NULL)
        {
            token = strtok(tokBuf," ");
            if(checkNT(token))
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
  
    int parseTable[NUM_NONTERM][NUM_TERM];
    for(int i =0; i<NUM_NONTERM; i++){
        for(int j = 0; j<NUM_TERM; j++)
            parseTable[i][j] = -1;
    }
    return 0;
}
