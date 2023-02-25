#include "lexerDef.h"

FILE *getStream(FILE *fp);

struct TOKEN genToken(char *lexeme, int tok,
                   unsigned int lineno,
                   union valueIfNum valueifInt);

struct TOKEN getNextToken();

void removeComments(char *testcaseFile, char *cleanFile);