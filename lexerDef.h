enum nts
{
        N1 = 107,
        N2 = 108,
        N3 = 109,
        N4 = 110,
        N5 = 111,
        N7 = 113,
        N8 = 114,
        N9 = 115,
        N_10 = 130,
        N_11 = 131,
        U = 125,
        actual_para_list = 439,
        anyTerm = 416,
        arithmeticExpr = 352,
        arithmeticOrBooleanExpr = 320,
        arrExpr = 420,
        arrFactor = 103,
        arrTerm = 413,
        arr_N4 = 290,
        arr_N5 = 291,
        array_element_for_print = 400,
        assignmentStmt = 376,
        boolConstt = 174,
        caseStmts = 122,
        condionalStmt = 306,
        dataType = 448,
        declareStmt = 195,
        NT_default = 421,
        driverModule = 257,
        ele_idx_w_exp = 303,
        expression = 215,
        factor = 379,
        idList = 357,
        id_num_rnum = 232,
        index_arr = 127,
        index_for_loop = 366,
        input_plist = 262,
        ioStmt = 380,
        iterativeStmt = 328,
        logicalOp = 482,
        lvalueARRStmt = 233,
        lvalueIDStmt = 205,
        module = 386,
        moduleDeclaration = 463,
        moduleDeclarations = 129,
        moduleDef = 477,
        moduleReuseStmt = 397,
        new_NT = 327,
        new_index = 132,
        new_index_for_loop = 162,
        op1 = 192,
        op2 = 193,
        optional = 101,
        otherModules = 266,
        output_plist = 331,
        p1 = 141,
        program = 440,
        range_arrays = 269,
        range_for_loop = 355,
        relationalOp = 249,
        ret = 251,
        sign = 293,
        sign_for_loop = 323,
        simpleStmt = 185,
        statement = 152,
        statements = 207,
        term = 300,
        type = 310,
        unaryOp = 430,
        value = 341,
        varPrint = 474,
        var_id_num = 171,
        whichStmt = 126,
};

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
    COMMENTMARK = 57,
    ERROR = 58
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

char lt5[11][5] = {
    "of", "in", "OR", "end", 
    "use", "for", "AND", "real", 
    "with", "case", "true"
    };
char eq5[8][6] = {
    "array", "start", "print", "takes", 
    "input", "break", "while", "false"
    };
char gt5[11][11]= {"integer", "boolean", "declare", "module",
    "driver", "program", "get_value", "parameters", 
    "returns", "switch", "default"
    };