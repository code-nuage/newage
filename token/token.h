#ifndef TOKEN_H
#define TOKEN_H

typedef enum TokenType {
    // Literals
    TOKEN_IDENT,
    TOKEN_STRING,
    TOKEN_NUMBER,

    // Delimiters
    TOKEN_LPAREN, // (
    TOKEN_RPAREN, // )
    TOKEN_LBRACE, // {
    TOKEN_RBRACE, // }
    TOKEN_LBRACK, // [
    TOKEN_RBRACK, // ]

    TOKEN_DOT,    // .
    TOKEN_COMMA,  // ,
    TOKEN_COLON,  // :

    // Operators
    TOKEN_PLUS,          // +
    TOKEN_MINUS,         // -
    TOKEN_MULTIPLY,      // *
    TOKEN_DIVIDE,        // /
    TOKEN_MOD,           // %
    TOKEN_ASSIGN,        // =
    
    TOKEN_EQUAL,         // ==
    TOKEN_NOT_EQUAL,     // !=
    TOKEN_GREATER,       // >
    TOKEN_GREATER_EQUAL, // >=
    TOKEN_LESS,          // <
    TOKEN_LESS_EQUAL,    // <=

    TOKEN_AND,           // &&
    TOKEN_OR,            // ||
    TOKEN_NOT,           // !

    // Keywords
    TOKEN_LOCAL,       // local
    TOKEN_GLOBAL,      // global

    TOKEN_IF,          // if
    TOKEN_ELSE,        // else
    TOKEN_FOR,         // for
    TOKEN_WHILE,       // while
    TOKEN_DO,          // do
    TOKEN_FUNC,        // function
    TOKEN_RETURN,      // return
    TOKEN_BREAK,       // break
    TOKEN_CONTINUE,    // continue

    TOKEN_BOOL_TYPE,   // bool
    TOKEN_INT_TYPE,    // int
    TOKEN_FLOAT_TYPE,  // float
    TOKEN_STRING_TYPE, // string
    TOKEN_TABLE_TYPE,  // table

    // Other
    TOKEN_D_EOF, // \0
    TOKEN_D_EOL, // \n
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

#endif
