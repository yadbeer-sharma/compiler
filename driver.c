#include "parser.c"
#include "lexer.c"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
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
                //TODO call function to print tokens
                break;
            case 3:
                //TODO call appropriate parse method
                break;
            case 4:
                #include <time.h>

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
 
