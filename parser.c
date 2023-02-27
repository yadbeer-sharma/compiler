#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    return (ret % 105);
}

int hash_nt(char *nonterminal){
    int G[] = {0, 0, 0, 0, 0, 56, 0, 49, 0, 0, 0, 9, 0, 0, 0, 96, 0,
    35, 56, 0, 0, 64, 62, 18, 0, 0, 39, 51, 0, 41, 66, 24, 0, 2, 31, 20, 0,
    76, 41, 0, 0, 35, 55, 40, 58, 0, 0, 13, 86, 61, 33, 98, 0, 96, 42, 23,
    0, 103, 12, 34, 10, 103, 9, 6, 40, 11, 79, 92, 86, 30, 0, 40, 50, 90,
    72, 44, 15, 92, 6, 17, 0, 37, 43, 0, 29, 71, 96, 26, 0, 93, 33, 2, 11,
    45, 0, 31, 16, 69, 72, 75, 32, 60, 101, 84, 0};

    return (G[hash_nt_support(nonterminal, "UlgFf2DbXzntR3XpXIkitLL")] +
            G[hash_nt_support(nonterminal, "KWW60mhuIm5hVAaAulu8ijr")]) % 105 + 70;
}


void removeTikona(char* token)
{
    int len = strlen(token);
    char tokBufM[len-2];
    for(int i = 1; i < len-1; i++){
        tokBufM[i-1] = token[i]; 
    }
    memset(token, '\0', strlen(token) * sizeof(char));
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
    fseek(fp, 0, SEEK_SET);
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

    for (int i = 0; i < NUM_GRAMRULES; i++)
        for (int j = 0; j < 15; j++)
            printf("%d\n",grammar[i][j]);
        
    fclose(gram);
  
    int parseTable[NUM_NONTERM][NUM_TERM];
    for(int i =0; i<NUM_NONTERM; i++){
        for(int j = 0; j<NUM_TERM; j++)
            parseTable[i][j] = -1;
    }
    return 0;
}
