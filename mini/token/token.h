#ifndef TOKEN_H
#define TOKEN_H

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

    TOKEN_RETURN,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;

    char text[64];
    int value;
} Token;

char* t_display(Token t);
void t_print(Token t);

#endif // TOKEN_H
