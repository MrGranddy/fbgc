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


//TOKENS_BEGIN
//Autogenerated by helper/token_creator.py
#define UNKNOWN 0 // Begin with unknown
#define NIL 1 // null or none
#define CONSTANT 2 //
#define LOGIC 3 // logical true or false
#define INT 4 // int class
#define DOUBLE 5 // double class
#define COMPLEX 6 // complex class
#define STRING 7 // string class
#define MATRIX 8 // matrix class
#define TUPLE 9 // tuple class
#define CSTRING 10 // raw c strings without length
#define CFUN 11 // c function
#define FUN 12 // builtin fbgc function
#define CSTRUCT 13 // 
#define IDENTIFIER 14 // identifiers
#define RANGE 15 // range obj
#define ARRAY 16 //
#define LINKED_LIST 17 //
#define CMODULE 18 //
#define GARBAGE 19 //
#define FIELD 20 //
#define END 21 // end
#define FUN_MAKE 22 //
#define ELIF 23 //
#define ELSE 24 //
#define WHILE 25 //
#define FOR 26 //
#define BREAK 27 //
#define CONT 28 //
#define IF 29 //
#define RETURN 30 //
#define NEWLINE 31 //
#define LPARA 32 // (
#define RPARA 33 // )
#define LBRACK 34 // [
#define RBRACK 35 // ]
#define LBRACE 36 // {
#define RBRACE 37 // }
#define COMMA 38 // , -- set1 start
#define DOT 39 // .
#define SEMICOLON 40 // ; 
#define COLON 41 // : set1 finish
#define RSHIFT 42 // >> assignment and binary operators start from here
#define LSHIFT 43 // <<
#define STARSTAR 44 // **
#define SLASHSLASH 45 // //
#define PLUS 46 // +
#define MINUS 47 // -
#define STAR 48 // *
#define SLASH 49 // /
#define CARET 50 // ^
#define PERCENT 51 // % assignment finish
#define LOEQ 52 // <=
#define GREQ 53 // >=
#define EQEQ 54 // ==
#define NOTEQ 55 // !=
#define LOWER 56 // <
#define GREATER 57 // >
#define PIPE 58 // |
#define AMPERSAND 59 // & binary finish
#define EXCLAMATION 60 // !
#define TILDE 61 // ~
#define UPLUS 62 // +
#define UMINUS 63 // -
#define ASSIGN 64 // = assignment ops start from here
#define RSHIFT_ASSIGN 65 // >>=
#define LSHIFT_ASSIGN 66 // <<=
#define STARSTAR_ASSIGN 67 // **=
#define SLASHSLASH_ASSIGN 68 // //=
#define PLUS_ASSIGN 69 // +=
#define MINUS_ASSIGN 70 // -=
#define STAR_ASSIGN 71 // *=
#define SLASH_ASSIGN 72 // /=
#define CARET_ASSIGN 73 // ^=
#define PERCENT_ASSIGN 74 // %=
#define ASSIGN_SUBSCRIPT 75 //
#define LEN 76 //
#define JUMP 77 //
#define FOR_BEGIN 78 //
#define FUN_CALL 79 //
#define BUILD_TUPLE 80 //
#define BUILD_MATRIX 81 //
#define POP_TOP 82 //
#define ROW 83 //
#define LOAD_SUBSCRIPT 84 //
#define TOKEN_LIST_AS_STRINGS()\
"UNKNOWN",\
"NIL",\
"CONSTANT",\
"LOGIC",\
"INT",\
"DOUBLE",\
"COMPLEX",\
"STRING",\
"MATRIX",\
"TUPLE",\
"CSTRING",\
"CFUN",\
"FUN",\
"CSTRUCT",\
"IDENTIFIER",\
"RANGE",\
"ARRAY",\
"LINKED_LIST",\
"CMODULE",\
"GARBAGE",\
"FIELD",\
"END",\
"FUN_MAKE",\
"ELIF",\
"ELSE",\
"WHILE",\
"FOR",\
"BREAK",\
"CONT",\
"IF",\
"RETURN",\
"NEWLINE",\
"LPARA",\
"RPARA",\
"LBRACK",\
"RBRACK",\
"LBRACE",\
"RBRACE",\
"COMMA",\
"DOT",\
"SEMICOLON",\
"COLON",\
"RSHIFT",\
"LSHIFT",\
"STARSTAR",\
"SLASHSLASH",\
"PLUS",\
"MINUS",\
"STAR",\
"SLASH",\
"CARET",\
"PERCENT",\
"LOEQ",\
"GREQ",\
"EQEQ",\
"NOTEQ",\
"LOWER",\
"GREATER",\
"PIPE",\
"AMPERSAND",\
"EXCLAMATION",\
"TILDE",\
"UPLUS",\
"UMINUS",\
"ASSIGN",\
"RSHIFT_ASSIGN",\
"LSHIFT_ASSIGN",\
"STARSTAR_ASSIGN",\
"SLASHSLASH_ASSIGN",\
"PLUS_ASSIGN",\
"MINUS_ASSIGN",\
"STAR_ASSIGN",\
"SLASH_ASSIGN",\
"CARET_ASSIGN",\
"PERCENT_ASSIGN",\
"ASSIGN_SUBSCRIPT",\
"LEN",\
"JUMP",\
"FOR_BEGIN",\
"FUN_CALL",\
"BUILD_TUPLE",\
"BUILD_MATRIX",\
"POP_TOP",\
"ROW",\
"LOAD_SUBSCRIPT",\
//TOKENS_END

#define GM_ERROR 0
#define GM_NEWLINE 1
#define GM_ATOM 2
#define GM_ID 3
#define GM_BINOP 4
#define GM_UNOP 5
#define GM_ASSIGNOP 6
#define GM_ASSIGNMENT_EXPRESSION 7
#define GM_EXPRESSION 8
#define GM_UNBALANCED_LIST 9
#define GM_BALANCED_LIST 10
#define GM_LPARA 11
#define GM_LBRACK 12
#define GM_PIPE 13
#define GM_FUNCTIONAL 14
#define GM_MATRIX 15
#define GRAMMAR_TOKENS_AS_STRINGS()\
"GM_ERROR",\
"GM_NEWLINE",\
"GM_ATOM",\
"GM_ID",\
"GM_BINOP",\
"GM_UNOP",\
"GM_ASSIGNOP",\
"GM_ASSIGNMENT_EXPRESSION",\
"GM_EXPRESSION",\
"GM_UNBALANCED_LIST",\
"GM_BALANCED_LIST",\
"GM_LPARA",\
"GM_LBRACK",\
"GM_PIPE",\
"GM_FUNCTIONAL",\
"GM_MATRIX"

extern const char * gm_name_array[];
extern const char * object_name_array[];
extern const token_struct operator_token_array[];
extern const token_struct reserved_words_token_array[];

fbgc_token get_operator_code(const char *str);
fbgc_token get_operator_code_from_substr(const char *str1,const char *str2);
fbgc_token get_reserved_word_code(const char *str);
fbgc_token get_reserved_word_code_from_substr(const char *str1,const char *str2);

const char * get_token_as_str(fbgc_token tok);

#define is_fbgc_OPERATOR(T)(T>=COLON && T< ASSIGN_SUBSCRIPT )
#define is_fbgc_IDENTIFIER(T)(T == IDENTIFIER)
#define is_fbgc_ATOM(T)(T>= LOGIC && T<=STRING)

#define is_fbgc_PARA(T)(T>=LPARA && T<= RBRACK)
#define is_fbgc_UNARY_OPERATOR(T)( T >= EXCLAMATION && T<= UMINUS)
#define is_fbgc_ASSIGNMENT_OPERATOR(T)( T >= ASSIGN && T< ASSIGN_SUBSCRIPT)
//solve this colon issue..
#define is_fbgc_BINARY_OPERATOR(T)( T>=COLON && T<= AMPERSAND)

#define is_fbgc_FUNCTIONABLE(x)(x == IF || x == ELIF || x == ELSE || x == WHILE || x == FUN_MAKE || x == FOR)

#define is_fbgc_EXPRESSION(x)(is_fbgc_ATOM(x) || is_fbgc_IDENTIFIER(x)|| x == EXPRESSION || x == UNARY_EXPRESSION ||x==BINARY_EXPRESSION||\
is_fbgc_TUPLE(x) || is_fbgc_MATRIX(x) || x == CFUN || x == SEMICOLON || x == LEN)

#define is_fbgc_JUMP_STATEMENT(x)(x == BREAK || x == CONT)

#define is_fbgc_ASSIGNMENT(x)(x==ASSIGNMENT_EXPRESSION)
#define is_fbgc_STATEMENT(x)(x == STATEMENT || is_fbgc_EXPRESSION(x) || is_fbgc_ASSIGNMENT(x) || is_fbgc_JUMP_STATEMENT(x))

#ifdef  __cplusplus
}
#endif

#endif
