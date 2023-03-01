#include "parser.c"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int option=-1;
    
    printf("Please input option and press enter\n");
    printf("Option 0: Exit\n");
    printf("Option 1: Print comment free code\n");
    printf("Option 2: Print token list\n");
    printf("Option 3: Print parse tree\n");
    printf("Option 4: Print time taken to verify the syntactic correctness\n");
    
    while(option!=0)
    {
        scanf("%d",&option);
        switch(option)
        {
            case 0:
                printf("Successfully exiting\n");
                return 0;
                break;
            case 1:  
                //TODO call function to print uncommented function
                break; 
            case 2:
                char *filename;
                if (argc <= 2){
                    printf("Too less arguments! Please provide buffer size and filename\n");
                    exit(0);
                }
                else if (argc == 3){
                    BUFSIZE = atoi(argv[1]);
                    filename = (char *)malloc(strlen(argv[2]));
                    strcpy(filename, argv[2]);
                }
                else{
                    printf("Too many arguments!\n");
                    exit(0);
                }

                fp = fopen(filename, "r");

                if (fp == NULL){
                    printf("File does not exist\n");
                    exit(0);
                }

                twinBuff[0] = (char *)malloc(sizeof(char) * BUFSIZE);
                twinBuff[1] = (char *)malloc(sizeof(char) * BUFSIZE);
                fillBuff();
                struct TOKEN test;
                for(int i = 0; i < 140; i++){
                    test = getNextToken();
                }

                break;
            case 3:
                //TODO call appropriate parse method
                break;
            case 4:

                clock_t start_time, end_time;

                double total_CPU_time, total_CPU_time_in_seconds;

                start_time = clock();

                // invoke your lexer and parser here

                end_time = clock();

                total_CPU_time = (double) (end_time - start_time);

                total_CPU_time_in_seconds = total_CPU_time /

                CLOCKS_PER_SEC;

                // Print both total_CPU_time and total_CPU_time_in_seconds 
        }
    }
    return 0;
}
 
