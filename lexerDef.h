enum E_TOKEN
{
    INTEGER = 1,
    REAL = 2,
    BOOLEAN = 3,
    OF = 4,
    ARRAY = 5,
    START = 6,
    END = 7,
    DECLARE = 8,
    MODULE = 9,
    DRIVER = 10,
    PROGRAM = 11,
    GET_VALUE = 12,
    PRINT = 13,
    USE = 14,
    WITH = 15,
    PARAMETERS = 16,
    TAKES = 17,
    INPUT = 18,
    RETURNS = 19,
    FOR = 20,
    IN = 21,
    SWITCH = 22,
    CASE = 23,
    BREAK = 24,
    DEFAULT = 25,
    WHILE = 26,
    ID = 27,
    NUM = 28,
    RNUM = 29,
    AND = 30,
    OR = 31,
    TRUE = 32,
    FALSE = 33,
    PLUS = 34,
    MINUS = 35,
    MUL = 36,
    DIV = 37,
    LT = 38,
    LE = 39,
    GE = 40,
    GT = 41,
    EQ = 42,
    NE = 43,
    DEF = 44,
    ENDDEF = 45,
    DRIVERDEF = 46,
    DRIVERENDDEF = 47,
    COLON = 48,
    RANGEOP = 49,
    SEMICOL = 50,
    COMMA = 51,
    ASSIGNOP = 52,
    SQBO = 53,
    SQBC = 54,
    BO = 55,
    BC = 56,
    COMMENTMARK = 57
};

union valueIfNum
{ /* usage : valueIfNum v = 25; then use V.i */
    int i;
    float f;
};

struct TOKEN
{
    int tok;
    char lexeme[20];
    unsigned int lineno;
    union valueIfNum valueifInt;
};

struct token_list{
    struct TOKEN token;
    struct token_list *next;
};