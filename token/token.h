#ifndef TOKEN_H
#define TOKEN_H

typedef enum TokenType {
    // Literals
    T_IDENT,
    T_STRING,
    T_NUMBER,

    // Delimiters
    T_LPAREN, // (
    T_RPAREN, // )
    T_LBRACE, // {
    T_RBRACE, // }
    T_LBRACK, // [
    T_RBRACK, // ]

    T_DOT,    // .
    T_COMMA,  // ,
    T_COLON,  // :

    // Operators
    T_PLUS,          // +
    T_MINUS,         // -
    T_MULTIPLY,      // *
    T_DIVIDE,        // /
    T_MOD,           // %
    T_ASSIGN,        // =
    
    T_EQUAL,         // ==
    T_NOT_EQUAL,     // !=
    T_GREATER,       // >
    T_GREATER_EQUAL, // >=
    T_LESS,          // <
    T_LESS_EQUAL,    // <=

    T_AND,           // &&
    T_OR,            // ||
    T_NOT,           // !

    // Keywords
    T_LOCAL,       // local
    T_GLOBAL,      // global

    T_IF,          // if
    T_ELSE,        // else
    T_FOR,         // for
    T_WHILE,       // while
    T_DO,          // do
    T_FUNC,        // function
    T_RETURN,      // return
    T_BREAK,       // break
    T_CONTINUE,    // continue

    T_BOOL_TYPE,   // bool
    T_INT_TYPE,    // int
    T_FLOAT_TYPE,  // float
    T_STRING_TYPE, // string
    T_TABLE_TYPE,  // table

    T_TRUE,        // true
    T_FALSE,       // false

    // Other
    T_EOF, // \0
    T_EOL, // \n
} TokenType;

typedef struct Token {
    TokenType type;

    int line;
    int column;

    union {
        char *ident;
        char *string;
        double number;
    } value;
} Token;

char *token_display(Token t);
void token_print(Token t);

#endif
