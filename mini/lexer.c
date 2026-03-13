#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

// Structure
typedef struct {
    TokenType type;

    char text[64];
    int value;
} Token;

// --+ Utils +--
char lex_current(Lexer *l) {
    return l->input[l->pos];
}

void lex_advance(Lexer *l) {
    if (l->input[l->pos] != '\0') 
        l->pos++;
}

void lex_skip_whitespace(Lexer *l) {
    while (lex_current(l) == ' ' || lex_current(l) == '\t' || lex_current(l) == '\r')
        lex_advance(l);
}

// --+ Manipulation +--
Token lex_number(Lexer *l) {
    int value = 0;

    while (isdigit(lex_current(l))) {
        value = value * 10 + (lex_current(l) - '0');
        lex_advance(l);
    }

    Token t;
    t.type = TOKEN_NUMBER;
    t.value = value;
    return t;
}

Token lex_ident(Lexer *l) {
    char buffer[64];
    int i = 0;

    while (isalnum(lex_current(l))) {
        buffer[i++] = lex_current(l);
        lex_advance(l);
    }

    buffer[i] = 0;

    Token t = {0};

    if (strcmp(buffer, "print") == 0) {
        t.type = TOKEN_PRINT;
    } else {
        t.type = TOKEN_IDENT;
        strcpy(t.text, buffer);
    }

    return t;
}

// --+ Utils +--
char* display_token(Token t) {
    switch (t.type) {
        case TOKEN_IDENT:
            return "IDENT";
        case TOKEN_NUMBER:
            return "NUMBER";
        case TOKEN_PRINT:
            return "PRINT";
        case TOKEN_PLUS:
            return "PLUS";
        case TOKEN_MINUS:
            return "MINUS";
        case TOKEN_STAR:
            return "STAR";
        case TOKEN_SLASH:
            return "SLASH";
        case TOKEN_EQUAL:
            return "EQUAL";

        case TOKEN_LPAREN:
            return "LPAREN";
        case TOKEN_RPAREN:
            return "RPAREN";

        case TOKEN_RETURN:
            return "RETURN";
        case TOKEN_EOF:
            return "EOF";

        default:
            return "TOKEN";
    }
}

void print_token(Token t) {
    printf("%s\n", display_token(t));
}

// --+ Processing +--
Token next_token(Lexer *l) {
    lex_skip_whitespace(l);

    char c = lex_current(l);

    if (isdigit(c))
        return lex_number(l);

    if (isalpha(c))
        return lex_ident(l);

    Token t = {0};

    switch (c) {
        case('+'): lex_advance(l); t.type = TOKEN_PLUS;   return t;
        case('-'): lex_advance(l); t.type = TOKEN_MINUS;  return t;
        case('*'): lex_advance(l); t.type = TOKEN_STAR;   return t;
        case('/'): lex_advance(l); t.type = TOKEN_SLASH;  return t;
        case('%'): lex_advance(l); t.type = TOKEN_PERCEN; return t;
        case('='): lex_advance(l); t.type = TOKEN_EQUAL;  return t;

        case('('): lex_advance(l); t.type = TOKEN_LPAREN; return t;
        case(')'): lex_advance(l); t.type = TOKEN_RPAREN; return t;

        case('\n'): lex_advance(l); t.type = TOKEN_RETURN; return t;
        case('\0'): t.type = TOKEN_EOF;                return t;
    }

    printf("Unkown character: %c\n", c);
    exit(1);
}

Token* lex_tokens(char* content, int size) {
    Lexer l = {.input = content, .pos = 0};
    Token* tokens = malloc(sizeof(Token) * size);

    int i = 0;
    Token t;

    do {
        t = next_token(&l);
        print_token(t);

        tokens[i] = t;

        i++;
    } while (t.type != TOKEN_EOF);

    return tokens;
}
