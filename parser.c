#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NUM_TERM=63;
int NUM_NONTERM=143;
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
    for(int i=0;i<NUM_NONTERM;i++)
    for(int j=0;j<NUM_TERM;j++)
    parseTable[i][j]=-1;

    FILE *gram = fopen("grammar.txt", "r");
    char ch;
    int numLines = 1;
    while (ch != EOF)
    {
        ch = fegtc(gram);
        if (ch = '\n')
            numLines++;
    }
    printf("%d\n", numLines);
    char* tokBuf;
    return 0;
}

void computeFirstAndFollow(int gram[NUM_GRAMRULES][15], int f[NUM_NONTERM][2][NUM_TERM])
{
    /////////////////// creating grammar index table /////////////////////////////////

    int nt_rule_count[NUM_NONTERM];    //index to calculate grammar rule index
    memset(nt_rule_count,0,NUM_NONTERM*sizeof(int));

    int rule_index[NUM_NONTERM][10];   // grammar rule index
    memset(rule_index,-1,NUM_NONTERM*(10*sizeof(int)));

    for(int i=0;i<NUM_GRAMRULES;i++)
    {
        int temp_nt=gram[i][0];
        int temp_col_no=nt_rule_count[temp_nt]++;

        rule_index[temp_nt][temp_col_no]=i;
    }
    ///////////////////  First set ////////////////////////////////////////////////////
    
    int fcal[NUM_NONTERM];    //to store which first set have been calculated
    memset(fcal,0,NUM_NONTERM*sizeof(int));
    
    for(int i=0;i < NUM_GRAMRULES; i++)
    {
        if(fcal[gram[i][0]]==0)
        first(f,gram,rule_index,fcal,gram[i][0]);
    }

    ////////////////// Follow Set /////////////////////////////////////////////////////

    f[gram[0][0]][1][63]=1;  /// $ in follow of start  

    ///////////// creating grammar index table for follow /////////////////////////

    
    memset(nt_rule_count,0,NUM_NONTERM*sizeof(int));

    int fo_rule_index[NUM_NONTERM][2][30];
    memset(fo_rule_index,-1,NUM_NONTERM*(2*(30*sizeof(int))));

    for(int i=0;i<NUM_GRAMRULES;i++)
    {
        for(int j=1;j<15;j++)
        {
            if(gram[i][j]==-1)
            break;
            if(gram[i][j]<70)
            break;
            fo_rule_index[gram[i][j]][0][nt_rule_count[gram[i][j]]++]=i;
            fo_rule_index[gram[i][j]][1][nt_rule_count[gram[i][j]]++]=j;
        }
    }
    ////////////////////////////////////////////////////////////////////////////   

    int focal[NUM_NONTERM];    //to store which follow set have been calculated
    memset(fcal,0,NUM_NONTERM*sizeof(int));
    
    for(int i=0;i<NUM_NONTERM;i++)
    {
        if(focal[i]==0 && fo_rule_index[i][0][0]!=-1)
        follow(f,gram,fo_rule_index,focal,i);
    }
    
}

void follow(int f[NUM_NONTERM][2][NUM_TERM], int gram[NUM_GRAMRULES][15], int rule_index[NUM_NONTERM][2][30], int fcal[NUM_NONTERM], int inde)
{
    for(int i=0;i<30;i++)
    {
        if(rule_index[inde][0][i]==-1)
        break;

        int x=rule_index[inde][0][i];
        int y=rule_index[inde][1][i];

        if(gram[x][y+1]==-1)
        {
            is_equal(f,gram[rule_index[inde][0][i]][0],inde);
        }
        else
        {
            int fl_fo=0;
            for(int j=y+1;j<20;j++)
            {
                if(f[gram[x][j]][0][62]!=-1)
                fl_fo=1;
                for(int k=0;k<NUM_TERM;k++)
                {
                    if(f[gram[x][j]][0][k]!=-1 && k!=62)
                    f[inde][1][k]=1;
                }
            }
            if(fl_fo)
            {
                if(fcal[gram[x][0]]==0)
                follow(f,gram,rule_index,fcal,gram[x][0]);
                for(int k=0;k<NUM_TERM;k++)
                {
                    if(f[gram[x][0]][1][k]==1)
                    f[inde][1][k]=1;
                }
            }
        }
    }
    fcal[inde]=1;
}

void do_union(int f[NUM_NONTERM][2][NUM_TERM],int index_of_rhs,int index_of_lhs,int curr_rule)
{
    for(int i=0;i<NUM_TERM;i++)
    {
        if(f[index_of_rhs][0][i]!=-1)
        f[index_of_lhs][0][i]=curr_rule;
    }
    return;
}

void first(int f[NUM_NONTERM][2][NUM_TERM], int gram[NUM_GRAMRULES][15], int rule_index[NUM_NONTERM][10], int fcal[NUM_NONTERM], int inde)
{
    ///////////base case, when it is a terminal ////////////////

    if(inde<NUM_TERM)
    {
        f[inde][0][inde]=999;
        fcal[inde]=1;
        return;                                                                                                                                                                                                                                                                                                                                                                                                                                                                 v                                                  vvvvvvvvvvvv vv                                                        b vv                               v                                                                                                                                                                                                                                                      b                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     b
    }
    ////////////////////////////////////////////////////////////
    for(int i=0;i<10;i++)
    {
        if(rule_index[inde][i] == -1)
        break;
        else
        {
            int curr_rule=rule_index[inde][i];
            int flag_null=0;
            for(int j=1;j<15;j++)
            {
                if(gram[curr_rule][j]==-1)
                break;

                if(fcal[gram[curr_rule][j]]==-1)
                first(f,gram,rule_index,fcal,gram[curr_rule][j]);

                if(f[gram[curr_rule][j]][0][62]==-1)
                {
                    do_union(f,gram[curr_rule][j],inde,curr_rule);
                    flag_null=1;
                    break;
                }
                else
                {
                    do_union(f,gram[curr_rule][j],inde,curr_rule);
                }
            }
            if(flag_null==1)
            f[inde][0][62]=-1;
        }
    }
    fcal[inde]=1;
    return;
}


void createParseTable(int f[NUM_NONTERM][2][NUM_TERM], int parTab[NUM_NONTERM][NUM_TERM])
{
    for(int i=0;i<NUM_NONTERM;i++)
    {
        if(f[i][0][62]==-1)
        {
            for(int j=0;j<NUM_TERM;j++)
            parTab[i][j]=f[i][0][j];
        }
        else
        {
            int e_rule=f[i][0][62];

            for(int j=0;j<NUM_TERM;j++)
            if(f[i][0][j]!=e_rule)
            parTab[i][j]=f[i][0][j];
            
            for(int j=0;j<NUM_TERM;j++)
            if(f[i][1][j]!=-1)
            parTab[i][j]=e_rule;
        }
    }
    return;
}
