#ifndef TOKENS_H
#define TOKENS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t fbgc_token;

typedef struct {
	fbgc_token tokencode;
	const char * name;
}token_struct;

#define UNKNOWN 0
#define ATOM 1
#define INT 2
#define INT16 3
#define INT2 4
#define DOUBLE 5
#define COMPLEX 6
#define STRING 7
#define IDENTIFIER 8
#define WORD 9
#define VAR 10
#define CFUN 11
#define FUN 12
#define SUBSCRIPT 13
#define REFERENCE 14
#define LIST 15
#define RAW_MATRIX 16
#define MATRIX 17
#define NUPLE 18
#define MONUPLE 19
#define RAW_TUPLE 20
#define TUPLE 21
#define LINKED_LIST 22
#define LINKED_LIST_TAIL 23
#define STACK 24
#define CMODULE 25
#define OP 26
#define PLUS 27
#define MINUS 28
#define STAR 29
#define SLASH 30
#define MOD 31
#define STARSTAR 32
#define CARET 33
#define OR_OP 34
#define AND_OP 35
#define GREATER 36
#define LOWER 37
#define LO_EQ 38
#define GR_EQ 39
#define EQ_EQ 40
#define NOT_EQ 41
#define IS_EQ 42
#define IF_THEN 43
#define R_ARROW 44
#define L_ARROW 45
#define COL_LO 46
#define RW_ARROW 47
#define LW_ARROW 48
#define COLSTAR 49
#define COLSLASH 50
#define SLASHSLASH 51
#define COLON 52
#define RSHIFT 53
#define LSHIFT 54
#define ASSIGN 55
#define PLUS_ASSIGN 56
#define MINUS_ASSIGN 57
#define STAR_ASSIGN 58
#define SLASH_ASSIGN 59
#define CONST_ASSIGN 60
#define INC 61
#define DECR 62
#define UPLUS 63
#define UMINUS 64
#define NOT_OP 65
#define SEMICOLON 66
#define TWO_DOT 67
#define THREE_DOT 68
#define TWO_COLON 69
#define TILDE 70
#define COMMA 71
#define DOT 72
#define QUESTION_MARK 73
#define DOLLAR 74
#define PARA 75
#define LPARA 76
#define RPARA 77
#define LBRACE 78
#define RBRACE 79
#define LBRACK 80
#define RBRACK 81
#define FOR 82
#define WHILE 83
#define UNTIL 84
#define JUMP 85
#define BREAK 86
#define CONT 87
#define IF 88
#define ELSE 89
#define ELIF 90
#define IF_BEGIN 91
#define ELSE_BEGIN 92
#define BEGIN 93
#define END 94
#define START 95
#define FINISH 96
#define LOAD 97
#define AND 98
#define OR 99
#define NOT 100
#define SPACE 101
#define TAB 102
#define NEWLINE 103
#define RETURN 104
#define ROW 105
#define EXPRESSION 106
#define ASSIGNMENT 107
#define STATEMENT 108
#define ASSIGNMENT_EXPRESSION 109
#define UNARY_EXPRESSION 110
#define BINARY_EXPRESSION 111
#define BALANCED_EXPRESSION_LIST 112
#define UNBALANCED_EXPRESSION_LIST 113
#define TOKEN_LIST_AS_STRINGS()\
"UNKNOWN",\
"ATOM",\
"INT",\
"INT16",\
"INT2",\
"DOUBLE",\
"COMPLEX",\
"STRING",\
"IDENTIFIER",\
"WORD",\
"VAR",\
"CFUN",\
"FUN",\
"SUBSCRIPT",\
"REFERENCE",\
"LIST",\
"RAW_MATRIX",\
"MATRIX",\
"NUPLE",\
"MONUPLE",\
"RAW_TUPLE",\
"TUPLE",\
"LINKED_LIST",\
"LINKED_LIST_TAIL",\
"STACK",\
"CMODULE",\
"OP",\
"PLUS",\
"MINUS",\
"STAR",\
"SLASH",\
"MOD",\
"STARSTAR",\
"CARET",\
"OR_OP",\
"AND_OP",\
"GREATER",\
"LOWER",\
"LO_EQ",\
"GR_EQ",\
"EQ_EQ",\
"NOT_EQ",\
"IS_EQ",\
"IF_THEN",\
"R_ARROW",\
"L_ARROW",\
"COL_LO",\
"RW_ARROW",\
"LW_ARROW",\
"COLSTAR",\
"COLSLASH",\
"SLASHSLASH",\
"COLON",\
"RSHIFT",\
"LSHIFT",\
"ASSIGN",\
"PLUS_ASSIGN",\
"MINUS_ASSIGN",\
"STAR_ASSIGN",\
"SLASH_ASSIGN",\
"CONST_ASSIGN",\
"INC",\
"DECR",\
"UPLUS",\
"UMINUS",\
"NOT_OP",\
"SEMICOLON",\
"TWO_DOT",\
"THREE_DOT",\
"TWO_COLON",\
"TILDE",\
"COMMA",\
"DOT",\
"QUESTION_MARK",\
"DOLLAR",\
"PARA",\
"LPARA",\
"RPARA",\
"LBRACE",\
"RBRACE",\
"LBRACK",\
"RBRACK",\
"FOR",\
"WHILE",\
"UNTIL",\
"JUMP",\
"BREAK",\
"CONT",\
"IF",\
"ELSE",\
"ELIF",\
"IF_BEGIN",\
"ELSE_BEGIN",\
"BEGIN",\
"END",\
"START",\
"FINISH",\
"LOAD",\
"AND",\
"OR",\
"NOT",\
"SPACE",\
"TAB",\
"NEWLINE",\
"RETURN",\
"ROW",\
"EXPRESSION",\
"ASSIGNMENT",\
"STATEMENT",\
"ASSIGNMENT_EXPRESSION",\
"UNARY_EXPRESSION",\
"BINARY_EXPRESSION",\
"BALANCED_EXPRESSION_LIST",\
"UNBALANCED_EXPRESSION_LIST",\

extern const char * object_name_array[];
extern const token_struct operator_token_array[];
extern const token_struct reserved_words_token_array[];


fbgc_token get_operator_code(const char *str);
fbgc_token get_operator_code_from_substr(const char *str1,const char *str2);
fbgc_token get_reserved_word_code(const char *str);
fbgc_token get_reserved_word_code_from_substr(const char *str1,const char *str2);


const char * get_token_as_str(fbgc_token tok);


#define is_fbgc_OPERATOR(T)(T>=OP && T<= RBRACK)
#define is_fbgc_IDENTIFIER(T)(T>=IDENTIFIER && T<=REFERENCE)
#define is_fbgc_ATOM(T)(T>= ATOM && T<=STRING)
#define is_fbgc_INT(T) (T == INT)
#define is_fbgc_DOUBLE(T) (T == DOUBLE)
#define is_fbgc_STRING(T) (T == STRING)
#define is_fbgc_PARA(T)(T>=PARA && T<= RBRACK)
#define is_fbgc_BINARY_OPERATOR(T)(T>=PLUS && T<= LSHIFT)
#define is_fbgc_UNARY_OPERATOR(T)((T>=INC && T<=NOT_OP) )
#define is_fbgc_ASSIGNMENT_OPERATOR(T)(T>= ASSIGN && T<= CONST_ASSIGN)
#define is_fbgc_VAR(T)(T == VAR )
#define is_fbgc_FUN(T)(T == FUN)
#define is_fbgc_WORD(T)(T == WORD)

#define is_fbgc_MATRIX(x)(x == MATRIX || x == RAW_MATRIX)
#define is_fbgc_TUPLE(x)(x == NUPLE || x == MONUPLE  || x == RAW_TUPLE ||x == TUPLE)

#define is_fbgc_FUNCTIONABLE(x)(x == IF || x == ELIF || x == ELSE || x == WHILE)

#define is_fbgc_START(x)(x == START || x == BEGIN || x == IF_BEGIN)
#define is_fbgc_LIST(x) (x == LIST)
#define is_fbgc_EXPRESSION(x)(is_fbgc_ATOM(x) || is_fbgc_IDENTIFIER(x)|| x == EXPRESSION || x == UNARY_EXPRESSION ||x==BINARY_EXPRESSION||\
is_fbgc_TUPLE(x) || is_fbgc_MATRIX(x) || is_fbgc_LIST(x) || x == CFUN)

#define is_fbgc_ASSIGNMENT(x)(x==ASSIGNMENT_EXPRESSION)
#define is_fbgc_STATEMENT(x)(x == STATEMENT || is_fbgc_EXPRESSION(x) || is_fbgc_ASSIGNMENT(x))



#ifdef  __cplusplus
}
#endif








#endif

