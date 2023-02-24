//Importing the Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Global Variables Declaration
FILE *fp;
int BUFSIZE = 128;


//Driver code
int main(int argc, char *argv[]){

    char *filename;                                                 

    if(argc <= 2){
        printf("Too less arguments! Please provide buffer size and filename\n");
        exit(0);
    }
    else if(argc == 3){
        BUFSIZE = atoi(argv[1]);
        filename = (char *) malloc(strlen(argv[2]));
        strcpy(filename, argv[2]);
    }
    else{
        printf("Too many arguments!\n");
        exit(0);
    }

    fp = fopen(filename, "r");
    
    if(fp == NULL){
        printf("File does not exist\n");
        exit(0);
    }

}
void removeComments(char *inFile,char *cleanFile)
{
    FILE* input=fopen(inFile,"r");
    if(input == NULL)
    {
        printf("Input File does not exist\n");
        exit(0);
    }

    FILE* out=fopen(cleanFile,"w");
    if(out == NULL)
    {
        printf("Output File does not exist\n");
        exit(0);
    }

    
    int inCom=0;  
    char c=fgetc(input);  
    while(c != EOF)
    {        
        if(inCom==0)
        {            
            if(c!='*')
            {
                
                fputc(c,out);
                c=fgetc(input);
            }
            else
            {
                c=fgetc(input);
                if(c=='*')
                {
                    inCom=1;
                }
                else
                fputc('*',out);
            }
        }
        else
        {
            if(c=='\n')
            {
                fputc(c,out);
                c=fgetc(input);
            }
            else if(c=='*')
            {
                c=fgetc(input);
                if(c=='*')
                {
                    c=fgetc(input);
                    inCom=0;
                }
            }
            else
            c=fgetc(input);
        }
    }
    fclose(input);
    fclose(out);
    return 0;
}
    



