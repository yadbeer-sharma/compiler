// Importing the Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

// int isdigit(char c){
//     return (c>='0' && c<='9');
// }

// int isalpha(char c){
//     return ((c>='a' && c<='z')||(c>='A' && c<='Z'));
// }

// Global Variables Declaration
FILE *fp;
int BUFSIZE;
int buffIndex, Index, lnNum = 1; // buffIndex is index in the buffer, index is which buffer is in use
char *twinBuff[2];

int hasher(char lexeme[21])
{
    int a = strlen(lexeme);

    if (a < 5)
    {
        if (!strcmp(lexeme, "of"))
        {
            return OF;
        }
        else if (!strcmp(lexeme, "in"))
        {
            return IN;
        }
        else if (!strcmp(lexeme, "OR"))
        {
            return OR;
        }
        else if (!strcmp(lexeme, "end"))
        {
            return END;
        }
        else if (!strcmp(lexeme, "use"))
        {
            return USE;
        }
        else if (!strcmp(lexeme, "for"))
        {
            return FOR;
        }
        else if (!strcmp(lexeme, "AND"))
        {
            return AND;
        }
        else if (!strcmp(lexeme, "real"))
        {
            return REAL;
        }
        else if (!strcmp(lexeme, "with"))
        {
            return WITH;
        }
        else if (!strcmp(lexeme, "case"))
        {
            return CASE;
        }
        else if (!strcmp(lexeme, "true"))
        {
            return TRUE;
        }
        else
        {
            return ID;
        }
    }

    else if (a == 5)
    {
        if (!strcmp(lexeme, "array"))
        {
            return ARRAY;
        }
        else if (!strcmp(lexeme, "start"))
        {
            return START;
        }
        else if (!strcmp(lexeme, "print"))
        {
            return PRINT;
        }
        else if (!strcmp(lexeme, "takes"))
        {
            return TAKES;
        }
        else if (!strcmp(lexeme, "input"))
        {
            return INPUT;
        }
        else if (!strcmp(lexeme, "break"))
        {
            return BREAK;
        }
        else if (!strcmp(lexeme, "while"))
        {
            return WHILE;
        }
        else if (!strcmp(lexeme, "false"))
        {
            return FALSE;
        }
        else
        {
            return ID;
        }
    }
    else
    {
        if (!strcmp(lexeme, "integer"))
        {
            return INTEGER;
        }
        else if (!strcmp(lexeme, "declare"))
        {
            return DECLARE;
        }
        else if (!strcmp(lexeme, "boolean"))
        {
            return BOOLEAN;
        }
        else if (!strcmp(lexeme, "module"))
        {
            return MODULE;
        }
        else if (!strcmp(lexeme, "driver"))
        {
            return DRIVER;
        }
        else if (!strcmp(lexeme, "program"))
        {
            return PROGRAM;
        }
        else if (!strcmp(lexeme, "get_value"))
        {
            return GET_VALUE;
        }
        else if (!strcmp(lexeme, "parameters"))
        {
            return PARAMETERS;
        }
        else if (!strcmp(lexeme, "returns"))
        {
            return RETURNS;
        }
        else if (!strcmp(lexeme, "switch"))
        {
            return SWITCH;
        }
        else if (!strcmp(lexeme, "default"))
        {
            return DEFAULT;
        }
        else
        {
            return ID;
        }
    }
}

void fillBuff()
{
    Index = (Index == 0) ? 1 : 0;
    fread(twinBuff[Index], sizeof(char), BUFSIZE - 1, fp);
    twinBuff[Index][BUFSIZE - 1] = EOF;
    buffIndex = 0;
}

struct TOKEN genToken(char lexeme[21], int tok,
                      unsigned int lineno)
{
    struct TOKEN tk;
    strcpy(tk.lexeme, lexeme);
    tk.tok = tok;
    tk.lineno = lineno;
    if (tok == NUM)
        tk.valueifInt.i = atoi(lexeme);
    else if (tok == RNUM)
        tk.valueifInt.f = atof(lexeme);
    return tk;
}

struct TOKEN getNextToken()
{
    char lexeme[21];
    int state = 0;
    int lexIndex = 0;
    while (1)
    {
        if(lexIndex==20)
            return genToken(lexeme, ERROR4, lnNum);
        if (buffIndex == BUFSIZE - 1)
            fillBuff();
        if (twinBuff[Index][buffIndex] == EOF){
            if(state == 3 || state == 4)   
                printf("Comment didn't end!\n");    // TODO an error
            return genToken(lexeme, -1, lnNum);
        }

        char c = twinBuff[Index][buffIndex];
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
            else if (c == '*')
            {
                state = 1;
                lexeme[lexIndex++] = c;
            }
            else if (c == '!')
            {
                state = 7;
                lexeme[lexIndex++] = c;
            }

            else if (isalpha(c))
            {
                state = 301;
                lexeme[lexIndex++] = c;
            }
            else if (c == '_')
            {
                state = 302;
                lexeme[lexIndex++] = c;
            }
            else if (isdigit(c))
            {
                state = 201;
                lexeme[lexIndex++] = c;
            }
            else if (c == '=')
            {
                state = 5;
                lexeme[lexIndex++] = c;
            }
            else if (c== '.')
            {
                state = 250;
                lexeme[lexIndex++] = c;
            }
            else if (c == '>')
            {
                state = 400;
                lexeme[lexIndex++] = c;
            }
            else if (c == '<')
            {
                state = 500;
                lexeme[lexIndex++] = c;
            }
            else if (c == ':')
            {
                state=50;
                lexeme[lexIndex++] = c;
            }
            else if(c == '\n')
            {
                lnNum++;
            }

            break;
        case 7:
            if (c == '=')
                return genToken(lexeme, NE, lnNum);
            else
            {
                state=298;
                lexeme[lexIndex]='\0';
            }
         
            break;
        
        case 5:
            if (c == '=')
                return genToken(lexeme, EQ, lnNum);
            else
            {
                state=298;
                lexeme[lexIndex]='\0';
            }
         
            break;
        case 1:
            if (c == '*')
                state = 3;
            else
            {
                // if (c == '\n')
                //     lnNum++;
                state = 2;
            }
            break;
        case 2:
            buffIndex--; // RETRACTION
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, MUL, lnNum);
        case 3:
            if (c == '*')
                state = 4;
            else if (c == '\n')
                lnNum++;
            break;
        case 4:
            if (c == '*')
                state = 0;
            else
            {
                if (c == '\n')
                    lnNum++;
                state = 3;
            }
            break;
        case 50:
            if (c == '=')
            {
                lexeme[lexIndex++]= c;
                state = 51;
            }
            else
            {
                lexeme[lexIndex] = '\0';
                return genToken(lexeme, COLON, lnNum);
            }
            break;
        case 51:
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, ASSIGNOP, lnNum);
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
        case 201:
            if (isdigit(c))
                lexeme[lexIndex++] = c;
            else if (c == '.')
            {
                lexeme[lexIndex++] = c;
                state = 203;
            }
            else if (isalpha(c) || c == '_')
            {
                lexeme[lexIndex++] = c;
                state = 299; // TODO error type T1
            }
            else
            {
                state = 202;
            }
            break;
        case 202:
            buffIndex--;
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, NUM, lnNum);
            break;
        case 203:
            if (c == '.')
            {
                lexeme[lexIndex++] = c;
                state = 204;
            }
            else if (isdigit(c))
            {
                lexeme[lexIndex++] = c;
                state = 205;
            }
            else
            {
                lexeme[lexIndex++] = c;
                state = 299; // error type T1
            }
            break;
        case 204:
            buffIndex--;
            buffIndex--;
            lexeme[lexIndex] = '\0';
            lexeme[--lexIndex]='\0';
            return genToken(lexeme, NUM, lnNum);
            break;
        case 205:
            if (isdigit(c))
                lexeme[lexIndex++] = c;
            else if (c == 'e' || c == 'E')
            {
                lexeme[lexIndex++] = c;
                state = 207;
            }
            else if (isalpha(c))
            {
                lexeme[lexIndex++] = c;
                state = 299; // error type T1
            }
            else
            {
                lexeme[lexIndex++] = c;
                state = 206;
            }
            break;
        case 206:
            buffIndex--;
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, RNUM, lnNum);
            break;

        case 207:
            if (isdigit(c))
            {
                lexeme[lexIndex++] = c;
                state = 208;
            }
            else if (c == '+' || c == '-')
            {
                lexeme[lexIndex++] = c;
                state = 209;
            }
            else
            {
                lexeme[lexIndex++] = c;
                state = 299;
            }
            break;
        case 208:
            if (isdigit(c))
                lexeme[lexIndex++] = c;
            else if (isalpha(c) || c == '_')
            {
                lexeme[lexIndex++] = c;
                state = 299; // error type T1
            }
            else
            {
                lexeme[lexIndex++] = c;
                state = 206;
            }
            break;
        case 209:
            if (isdigit(c))
            {
                lexeme[lexIndex++] = c;
                state = 208;
            }
            else
            {
                lexeme[lexIndex++] = c;
                state = 299; // error type T1
            }
            break;
        case 250:
            if(c=='.')
            {
                state = 251;
                lexeme[lexIndex++] = c;
            }
            else
            {
                lexeme[lexIndex++] = c;
                state = 298; // error type T2   
            }
            break;
        case 251:
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, RANGEOP, lnNum);
            break;
        case 297: //error of type unidentified character
            lexeme[lexIndex]='\0';
            return genToken(lexeme, ERROR3, lnNum); 
            break;
        case 298:   // error of type a.b or !a or a=b
            lexeme[lexIndex]='\0';
            buffIndex--;
            return genToken(lexeme, ERROR2, lnNum);
            break;
        case 299:   // retracting error
            buffIndex--;
            lexeme[lexIndex]='\0';
            return genToken(lexeme, ERROR1, lnNum);
            break;
            

        case 301:
            if (isalpha(c))
                lexeme[lexIndex++] = c;
            else if (c == '_' || isdigit(c))
            {
                lexeme[lexIndex++] = c;
                state = 302;
            }
            else
                state = 303;
            break;
        case 302:
            if (isalpha(c) || c == '_' || isdigit(c))
                lexeme[lexIndex++] = c;
            else
                state = 304;
            break;
        case 303:
            buffIndex--;
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, hasher(lexeme), lnNum);
            break;
        case 304:
            buffIndex--;
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, ID, lnNum);
            break;
        case 400:
            if (c == '=')
            {
                lexeme[lexIndex++] = c;
                state = 401;
            }
            else if (c == '>')
            {
                lexeme[lexIndex++] = c;
                state = 402;
            }
            else
            {
                lexeme[lexIndex++] = c;
                state = 405;
            }
            break;
        case 401:
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, GE, lnNum);
            break;
        case 402:
            if (c == '>')
            {
                lexeme[lexIndex++] = c;
                state = 403;
            }
            else
            {
                lexeme[lexIndex++] = c;
                state = 404;
            }
            break;
        case 403:
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, DRIVERENDDEF, lnNum);
            break;
        case 404:
            buffIndex--; // RETRACTION
            lexeme[--lexIndex] = '\0';
            return genToken(lexeme, ENDDEF, lnNum);
            break;
        case 405:
            buffIndex--; // RETRACTION
            lexeme[--lexIndex] = '\0';
            return genToken(lexeme, GT, lnNum);
            break;
        case 500:
            if (c == '=')
            {
                lexeme[lexIndex++] = c;
                state = 501;
            }
            else if (c == '<')
            {
                lexeme[lexIndex++] = c;
                state = 502;
            }
            else
            {
                lexeme[lexIndex++] = c;
                state = 505;
            }
            break;
        case 501:
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, LE, lnNum);
            break;
        case 502:
            if (c == '<')
            {
                lexeme[lexIndex++] = c;
                state = 503;
            }
            else
            {
                lexeme[lexIndex++] = c;
                state = 504;
            }
            break;
        case 503:
            lexeme[lexIndex] = '\0';
            return genToken(lexeme, DRIVERDEF, lnNum);
            break;
        case 504:
            buffIndex--; // RETRACTION
            lexeme[--lexIndex] = '\0';
            return genToken(lexeme, DEF, lnNum);
            break;
        case 505:
            buffIndex--; // RETRACTION
            lexeme[--lexIndex] = '\0';
            return genToken(lexeme, LT, lnNum);
            break;
        default:
            lexeme[lexIndex++]=c;
            state = 297;  // TODO unidentified char error
        }
    buffIndex = buffIndex + 1;
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
}