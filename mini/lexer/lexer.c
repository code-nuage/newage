#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../token/token.h"

char l_current(Lexer *l) {
    return l->input[l->pos];
}

void l_advance(Lexer *l) {
    if (l->input[l->pos] != '\0') 
        l->pos++;
}

void l_skip_whitespace(Lexer *l) {
    while (l_current(l) == ' ' || l_current(l) == '\t' || l_current(l) == '\r')
        l_advance(l);
}

Token l_number(Lexer *l) {
    int value = 0;

    while (isdigit(l_current(l))) {
        value = value * 10 + (l_current(l) - '0');
        l_advance(l);
    }

    Token t;
    t.type = TOKEN_NUMBER;
    t.value = value;
    return t;
}

Token l_ident(Lexer *l) {
    char buffer[64];
    int i = 0;

    while (isalnum(l_current(l))) {
        buffer[i++] = l_current(l);
        l_advance(l);
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

Token l_next_token(Lexer *l) {
    l_skip_whitespace(l);

    char c = l_current(l);

    if (isdigit(c))
        return l_number(l);

    if (isalpha(c))
        return l_ident(l);

    Token t = {0};

    switch (c) {
        case('+'): l_advance(l); t.type = TOKEN_PLUS;   return t;
        case('-'): l_advance(l); t.type = TOKEN_MINUS;  return t;
        case('*'): l_advance(l); t.type = TOKEN_STAR;   return t;
        case('/'): l_advance(l); t.type = TOKEN_SLASH;  return t;
        case('='): l_advance(l); t.type = TOKEN_EQUAL;  return t;

        case('('): l_advance(l); t.type = TOKEN_LPAREN; return t;
        case(')'): l_advance(l); t.type = TOKEN_RPAREN; return t;

        case('\n'): l_advance(l); t.type = TOKEN_RETURN; return t;
        case('\0'): t.type = TOKEN_EOF;                  return t;
    }

    printf("Unkown character: %c\n", c);
    exit(1);
}

Token* l_tokens(char* content, int size) {
    Lexer l = {.input = content, .pos = 0};
    Token* tokens = malloc(sizeof(Token) * size);

    int i = 0;
    Token t;

    do {
        t = l_next_token(&l);
        t_print(t);

        tokens[i] = t;

        i++;
    } while (t.type != TOKEN_EOF);

    return tokens;
}
