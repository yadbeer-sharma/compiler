#include "lexerDef.h"

FILE *getStream(FILE *fp);

struct TOKEN genToken(char *lexeme, int tok,
                   unsigned int lineno);

struct TOKEN getNextToken();

void removeComments(char *testcaseFile, char *cleanFile);