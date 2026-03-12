#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// --+ Tokens +--
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

// Structure
typedef struct {
    TokenType type;

    char text[64];
    int value;
} Token;

// --+ Lexer +--
// State
typedef struct {
    const char *input;
    int pos;
} Lexer;

char current(Lexer *l) {
    return l->input[l->pos];
}

void advance(Lexer *l) {
    l->pos++;
}

void skip_whitespace(Lexer *l) {
    while (isspace(current(l)))
        advance(l);
}

Token lex_number(Lexer *l) {
    int value = 0;

    while (isdigit(current(l))) {
        value = value * 10 + (current(l) - '0');
        advance(l);
    }

    Token t;
    t.type = TOKEN_NUMBER;
    t.value = value;
    return t;
}

Token lex_ident(Lexer *l) {
    char buffer[64];
    int i = 0;

    while (isalnum(current(l))) {
        buffer[i++] = current(l);
        advance(l);
    }

    buffer[i] = 0;

    Token t;

    if (strcmp(buffer, "print") == 0) {
        t.type = TOKEN_PRINT;
    } else {
        t.type = TOKEN_IDENT;
        strcpy(t.text, buffer);
    }

    return t;
}

Token next_token(Lexer *l) {
    skip_whitespace(l);

    char c = current(l);

    if (isdigit(c))
        return lex_number(l);

    if (isalpha(c))
        return lex_ident(l);

    Token t;

    switch (c) {
        case('+'): advance(l); t.type = TOKEN_PLUS;  return t;
        case('-'): advance(l); t.type = TOKEN_MINUS; return t;
        case('*'): advance(l); t.type = TOKEN_STAR;  return t;
        case('/'): advance(l); t.type = TOKEN_SLASH; return t;
        case('='): advance(l); t.type = TOKEN_EQUAL; return t;

        case('('): advance(l); t.type = TOKEN_LPAREN; return t;
        case(')'): advance(l); t.type = TOKEN_RPAREN; return t;

        case('\0'): t.type = TOKEN_EOF; return t;
    }

    printf("Unkown character: %c\n", c);
    exit(1);
}

void print_token(Token t) {
    switch (t.type) {
        case TOKEN_IDENT:
            printf("IDENT(%s)\n", t.text);
            break;
        case TOKEN_NUMBER:
            printf("NUMBER(%d)\n", t.value);
            break;
        case TOKEN_PRINT:
            printf("PRINT\n");
            break;
        case TOKEN_PLUS:
            printf("PLUS\n");
            break;
        case TOKEN_MINUS:
            printf("MINUS\n");
            break;
        case TOKEN_STAR:
            printf("STAR\n");
            break;
        case TOKEN_SLASH:
            printf("SLASH\n");
            break;
        case TOKEN_EQUAL:
            printf("EQUAL\n");
            break;

        case TOKEN_LPAREN:
            printf("LPAREN\n");
            break;
        case TOKEN_RPAREN:
            printf("RPAREN\n");
            break;

        case TOKEN_EOF:
            printf("EOF\n");
            break;

        default:
            printf("TOKEN\n");
    }
}
