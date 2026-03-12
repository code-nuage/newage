#ifndef lexer 

typedef enum {
    TOKEN_IDENT,
    TOKEN_NUMBER,
    TOKEN_PRINT,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,

    TOKEN_EQUAL,

    TOKEN_LPAREN,
    TOKEN_RPAREN,

    TOKEN_EOF
} TokenType;
typedef struct {
    TokenType type;

    char text[64];
    int value;
} Token;
typedef struct {
    const char *input;
    int pos;
} Lexer;

char current(Lexer *l);
char advance(Lexer *l);
char skip_whitespace(Lexer *l);
Token lex_number(Lexer *l);
Token lex_ident(Lexer *l);
Token next_token(Lexer *l);

void print_token(Token t);

#endif // lexer