enum nts
{
        N1 = 70,
        N2 = 71,
        N3 = 72,
        N4 = 73,
        N5 = 74,
        N7 = 75,
        N8 = 76,
        N9 = 77,
        N_10 = 78,
        N_11 = 79,
        U = 80,
        actual_para_list = 81,
        anyTerm = 82,
        arithmeticExpr = 83,
        arithmeticOrBooleanExpr = 84,
        arrExpr = 85,
        arrFactor = 86,
        arrTerm = 87,
        arr_N4 = 88,
        arr_N5 = 89,
        array_element_for_print = 90,
        assignmentStmt = 91,
        boolConstt = 92,
        caseStmts = 93,
        condionalStmt = 94,
        dataType = 95,
        declareStmt = 96,
        default = 97,
        driverModule = 98,
        ele_idx_w_exp = 99,
        expression = 100,
        factor = 101,
        idList = 102,
        id_num_rnum = 103,
        index_arr = 104,
        index_for_loop = 105,
        input_plist = 106,
        ioStmt = 107,
        iterativeStmt = 108,
        logicalOp = 109,
        lvalueARRStmt = 110,
        lvalueIDStmt = 111,
        module = 112,
        moduleDeclaration = 113,
        moduleDeclarations = 114,
        moduleDef = 115,
        moduleReuseStmt = 116,
        new_NT = 117,
        new_index = 118,
        new_index_for_loop = 119,
        op1 = 120,
        op2 = 121,
        optional = 122,
        otherModules = 123,
        output_plist = 124,
        p1 = 125,
        program = 126,
        range_arrays = 127,
        range_for_loop = 128,
        relationalOp = 129,
        ret = 130,
        sign = 131,
        sign_for_loop = 132,
        simpleStmt = 133,
        statement = 134,
        statements = 135,
        term = 136,
        type = 137,
        unaryOp = 138,
        value = 139,
        varPrint = 140,
        var_id_num = 141,
        whichStmt = 142
};

enum E_TOKEN
{
        OF = 1,
        IN = 2,
        OR = 3,
        END = 4,
        USE = 5,
        FOR = 6,
        AND = 7,
        REAL = 8,
        WITH = 9,
        CASE = 10,
        TRUE = 11,
        ARRAY = 12,
        START = 13,
        PRINT = 14,
        TAKES = 15,
        INPUT = 16,
        BREAK = 17,
        WHILE = 18,
        FALSE = 19,
        INTEGER = 20,
        BOOLEAN = 21,
        DECLARE = 22,
        MODULE = 23,
        DRIVER = 24,
        PROGRAM = 25,
        GET_VALUE = 26,
        PARAMETERS = 27,
        RETURNS = 28,
        SWITCH = 29,
        DEFAULT = 30,
        ID = 31,
        NUM = 32,
        RNUM = 33,
        PLUS = 34,
        MINUS = 35,
        MUL = 36,
        DIV = 37,
        LT = 38,
        LE = 39,
        GT = 40,
        GE = 41,
        EQ = 42,
        NE = 43,
        DEF = 44,
        ENDDEF = 45,
        DRIVERENDDEF = 46,
        DRIVERDEF = 47,
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
        ERROR1 = 58,
        ERROR2 = 59,
        ERROR3 = 60,
        ERROR4 = 61,
        e = 62
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
