// Importing the Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

// Global Variables Declaration
FILE *fp;
int BUFSIZE;
int buffIndex, index, lnNum = 1; // buffIndex is index in the buffer, index is which buffer is in use
char *twinBuff[2];

int fillBuff(char *twinBuff)
{
    fread(twinBuff[index], sizeof(char), BUFSIZE, fp);
    return index == 0 ? 1 : 0;
}

struct TOKEN genToken(char lexeme[20], int tok,
                      unsigned int lineno)
{
    struct TOKEN tk;
    strcpy(tk.lexeme, lexeme);
    tk.tok = tok;
    tk.lineno = lineno;
    if (tok == 1)
        tk.valueifInt.i = atoi(lexeme);
    else if (tok == 2)
        tk.valueifInt.f = atof(lexeme);
    return tk;
}

struct TOKEN getNextToken()
{
    char lexeme[20];
    int state = 0;
    int lexIndex = 0;
    while (twinBuff[index][buffIndex] != EOF && buffIndex != BUFSIZ - 1)
    {
        char c = twinBuff[index][buffIndex++];
        switch (state)
        {
        case 0: // start state
            if (c == '+')
            {
                state = 101;
                lexeme[lexIndex++] = c;
            }
            else if (c == '-')
            {
                state = 102;
                lexeme[lexIndex++] = c;
            }
            else if (c == '/')
            {
                state = 103;
                lexeme[lexIndex++] = c;
            }
            else if (c == ';')
            {
                state = 104;
                lexeme[lexIndex++] = c;
            }
            else if (c == ',')
            {
                state = 105;
                lexeme[lexIndex++] = c;
            }
            else if (c == '[')
            {
                state = 106;
                lexeme[lexIndex++] = c;
            }
            else if (c == ']')
            {
                state = 107;
                lexeme[lexIndex++] = c;
            }
            else if (c == '(')
            {
                state = 108;
                lexeme[lexIndex++] = c;
            }
            else if (c == ')')
            {
                state = 109;
                lexeme[lexIndex++] = c;
            }
            if (c == '*')
            {
                state = 1;
                lexeme[lexIndex++] = c;
            }
            break;

        case 1:
            if (c == '*')
                state = 3;
            else
                state = 2;
            break;
        case 2:
            buffIndex--;        // RETRACTION
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, MUL, lnNum);
        case 3:
            if (c == '*')
                state = 4;
            break;
        case 4:
            if (c == '*')
                state = 0;
            else
                state = 3;
            break;
        case 101: // TK_PLUS
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, PLUS, lnNum);
            break;
        case 102:
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, MINUS, lnNum);
            break;
        case 103:
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, DIV, lnNum);
            break;
        case 104:
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, SEMICOL, lnNum);
            break;
        case 105:
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, COMMA, lnNum);
            break;
        case 106:
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, SQBO, lnNum);
            break;
        case 107:
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, SQBC, lnNum);
            break;
        case 108:
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, BO, lnNum);
            break;
        case 109:
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, BC, lnNum);
            break;
        default:
        }
    }
}

// Driver code
int main(int argc, char *argv[])
{

    char *filename;

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

    char *twinBuff[2];
    twinBuff[0] = (char *)malloc(sizeof(char) * BUFSIZE);
    twinBuff[1] = (char *)malloc(sizeof(char) * BUFSIZE);
}

void removeComments(char *inFile, char *cleanFile)
{
    FILE *input = fopen(inFile, "r");
    if (input == NULL)
    {
        printf("Input File does not exist\n");
        exit(0);
    }

    FILE *out = fopen(cleanFile, "w");
    if (out == NULL)
    {
        printf("Output File does not exist\n");
        exit(0);
    }

    int inCom = 0;
    char c = fgetc(input);
    while (c != EOF)
    {
        if (inCom == 0)
        {
            if (c != '*')
            {

                fputc(c, out);
                c = fgetc(input);
            }
            else
            {
                c = fgetc(input);
                if (c == '*')
                {
                    inCom = 1;
                }
                else
                    fputc('*', out);
            }
        }
        else
        {
            if (c == '\n')
            {
                fputc(c, out);
                c = fgetc(input);
            }
            else if (c == '*')
            {
                c = fgetc(input);
                if (c == '*')
                {
                    c = fgetc(input);
                    inCom = 0;
                }
            }
            else
                c = fgetc(input);
        }
    }
    fclose(input);
    fclose(out);
    return 0;
}
