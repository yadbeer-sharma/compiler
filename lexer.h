#include "lexerDef.h"

FILE *getStream(FILE *fp);

struct TOKEN *getNextToken();

void removeComments(char *testcaseFile, char *cleanFile);