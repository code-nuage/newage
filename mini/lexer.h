#ifndef LEXER_H
#define LEXER_H

// --+ Lexer +--
// State
typedef struct {
    const char *input;
    int pos;
    int line;
    int column;
} Lexer;

// --+ Tokens +--
typedef enum {
    TOKEN_IDENT,
    TOKEN_NUMBER,
    TOKEN_PRINT,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCEN,

    TOKEN_EQUAL,

    TOKEN_LPAREN,
    TOKEN_RPAREN,

    TOKEN_RETURN,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;

    char text[64];
    int value;
} Token;

char lex_current(Lexer *l);
void lex_advance(Lexer *l);
void lex_skip_whitespace(Lexer *l);
Token lex_number(Lexer *l);
Token lex_ident(Lexer *l);

char* display_token(Token t);
void print_token(Token t);

Token next_token(Lexer *l);
Token* lex_tokens(char* content, int size);

#endif // lexer
