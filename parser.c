#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.c"

int NUM_TERM;
int NUM_NONTERM;
int NUM_GRAMRULES;

int hash_t_support(char *key, char *T){
    int ret = 0;
    for(int i = 0; i < strlen(key); i++){
		ret += ((T[i % 12]) * (key[i]));
    }
    return (ret % 93);
}

int hash_t(char *terminal){
    int G[] = {0, 0, 0, 0, 72, 0, 70, 0, 30, 0, 0, 70, 0, 0, 70, 0, 0,
    40, 53, 0, 64, 84, 57, 50, 89, 31, 0, 46, 65, 80, 0, 0, 55, 66, 77, 20,
    41, 59, 0, 52, 49, 45, 0, 73, 46, 0, 58, 0, 83, 30, 80, 0, 0, 5, 0, 70,
    7, 0, 87, 0, 0, 10, 47, 19, 0, 49, 70, 0, 3, 56, 0, 88, 68, 90, 21, 14,
    17, 0, 37, 78, 31, 12, 61, 60, 39, 0, 56, 0, 73, 81, 51, 51, 0};

    return ((G[hash_t_support(terminal, "vcOr4EuYSHTh")] +
            G[hash_t_support(terminal, "TUiwsT1ZPoGS")]) % 93) + 1;
}

int hash_nt_support(char *key, char *T){
    int ret = 0;
    for(int i = 0; i < strlen(key); i++){
		ret += ((T[i % 23]) * (key[i]));
    }
    return (ret % 110);
}

int hash_nt(char *nonterminal){
    int G[] = {0, 0, 0, 0, 64, 6, 57, 0, 81, 0, 103, 0, 27, 74, 0, 64,
    0, 0, 73, 0, 0, 25, 0, 88, 50, 2, 96, 0, 35, 61, 73, 0, 96, 0, 67, 56,
    31, 34, 101, 0, 0, 0, 93, 0, 8, 45, 108, 55, 0, 0, 90, 0, 74, 104, 87,
    103, 19, 0, 50, 73, 22, 84, 27, 31, 45, 21, 91, 80, 22, 28, 89, 25, 0,
    0, 81, 23, 40, 97, 20, 0, 69, 10, 0, 100, 47, 92, 0, 23, 39, 68, 54, 0,
    107, 0, 59, 2, 59, 0, 92, 8, 61, 0, 88, 82, 0, 51, 0, 0, 0, 35};

    return (G[hash_nt_support(nonterminal, "yOzNiJRcultDp3eXsJ54dXv")] +
            G[hash_nt_support(nonterminal, "cv6IVed9rCV8WdjSNjXVBPv")]) % 110 + 70;
}



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
