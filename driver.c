#include "parser.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int option = -1;
    char *filename;
    while (option != 0)
    {
        printf("Please input option and press enter\n");
        printf("Option 0: Exit\n");
        printf("Option 1: Print comment free code\n");
        printf("Option 2: Print token list\n");
        printf("Option 3: Print parse tree\n");
        printf("Option 4: Print time taken to verify the syntactic correctness\n");
        printf("\n");
        scanf("%d", &option);
        printf("\n");
        switch (option)

        {
        case 0:
            printf("Successfully exiting\n");
            return 0;
            break;

        case 1:
            if (argc <= 2)
            {
                printf("Too less arguments! Please provide buffer size and filename\n");
                exit(0);
            }
            else if (argc == 3)
            {
                BUFSIZE = atoi(argv[1]);
                filename = (char *)malloc(strlen(argv[2]));
                strcpy(filename, argv[2]);
            }
            else
            {
                printf("Too many arguments!\n");
                exit(0);
            }
            removeComments(filename, "cleanfile.txt");

            FILE *cleanFile = fopen("cleanfile.txt", "r");
            char line[1000];
            while (fgets(line, sizeof(line), cleanFile) != NULL)
            {
                fprintf(stdout, "%s", line);
            }
            fclose(cleanFile);
            printf("\n");
            break;

        case 2:
            if (argc <= 2)
            {
                printf("Too less arguments! Please provide buffer size and filename\n");
                exit(0);
            }
            else if (argc == 3)
            {
                BUFSIZE = atoi(argv[1]);
                filename = (char *)malloc(strlen(argv[2]));
                strcpy(filename, argv[2]);
            }
            else
            {
                printf("Too many arguments!\n");
                exit(0);
            }

            fp = fopen(filename, "r");

            if (fp == NULL)
            {
                printf("File does not exist\n");
                exit(0);
            }

            twinBuff[0] = (char *)malloc(sizeof(char) * BUFSIZE);
            twinBuff[1] = (char *)malloc(sizeof(char) * BUFSIZE);
            fillBuff();
            struct TOKEN test;
            while (1)
            {
                test = getNextToken();
                if (test.tok == -1)
                    break;
                switch (test.tok)
                {
                case ERROR1:
                    printf("Error on line %d : Invalid Numeric Literal!\n", test.lineno);
                    break;
                case ERROR2:
                    printf("Error on line %d : found expression of type a.b or !a or a=b\n", test.lineno);
                    break;
                case ERROR3:
                    printf("Error on line %d : Unidentified character!\n", test.lineno);
                    break;
                case ERROR4:
                    printf("Error on line %d : Lexeme length exceeds 20 characters!\n", test.lineno);
                    break;
                default:
                    printf("%d  %s  %s\n", test.lineno, test.lexeme, invhash[test.tok]);
                    break;
                }
            }
            printf("\n");

                break;
            case 3:
                int parsed = parser();
                break;
            case 4:

            clock_t start_time, end_time;

            double total_CPU_time, total_CPU_time_in_seconds;

            start_time = clock();

            // invoke your lexer and parser here

            end_time = clock();

            total_CPU_time = (double)(end_time - start_time);

            total_CPU_time_in_seconds = total_CPU_time /

                                        CLOCKS_PER_SEC;

            // Print both total_CPU_time and total_CPU_time_in_seconds
        }
    }
    return 0;
}
