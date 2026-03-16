#include "lexer.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *keyword;
    TokenType type;
} KeywordMap;

static const KeywordMap keywords[] = { // Map the TokenTypes to its strings
    {"local",     T_LOCAL},
    {"global",    T_GLOBAL},
    {"if",        T_IF},
    {"else",      T_ELSE},
    {"for",       T_FOR},
    {"while",     T_WHILE},
    {"do",        T_DO},
    {"function",  T_FUNC},
    {"return",    T_RETURN},
    {"break",     T_BREAK},
    {"continue", T_CONTINUE},
    {"bool",     T_BOOL_TYPE},
    {"int",      T_INT_TYPE},
    {"float",    T_FLOAT_TYPE},
    {"string",   T_STRING_TYPE},
    {"table",    T_TABLE_TYPE},
    {"true",     T_TRUE},
    {"false",    T_FALSE}
};

// Utils
char lexer_current(Lexer *l) {
    return l->content[l->pos];
}

void lexer_advance(Lexer *l) {
    if (lexer_current(l) == '\n') {
        l->column = 0;
        l->line++;
    } else {
        l->column++;
    }
    if (l->content[l->pos] != '\0')
        l->pos++;
}

void lexer_skip(Lexer *l) {
    while (l->content[l->pos] == ' '
        || l->content[l->pos] == '\t'
        || l->content[l->pos] == '\r') {
        lexer_advance(l);
    }
}

// Lexer
Token lexer_number(Lexer *l) {
    int start = l->pos;
    int line = l->line;
    int column = l->column;

    while (isdigit(lexer_current(l)))
        lexer_advance(l);

    if (lexer_current(l) == '.') {
        lexer_advance(l);

        while (isdigit(lexer_current(l)))
            lexer_advance(l);
    }

    int len = l->pos - start;

    char buffer[64];
    memcpy(buffer, l->content + start, len);
    buffer[len] = '\0';

    Token t = {
        .type = T_NUMBER,
        .value.number = strtod(buffer, NULL),
        .line = line, .column = column,
    };

    return t;
}

Token lexer_ident_keyword(Lexer *l) {
    int start = l->pos;
    int line = l->line;
    int column = l->column;

    while (isalnum(lexer_current(l)) || lexer_current(l) == '_') {
        lexer_advance(l);
    }

    int len = l->pos - start;
    const char *buffer = l->content + start;

    for (size_t i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++) {
        if (strlen(keywords[i].keyword) == len &&
            strncmp(buffer, keywords[i].keyword, len) == 0) {

            Token t = {
                .type = keywords[i].type,
                .line = line, .column = column,
            };
            return t;
        }
    }

    char *text = malloc(len + 1);
    memcpy(text, buffer, len);
    text[len] = '\0';

    Token t = {
        .type = T_IDENT,
        .line = line, .column = column,
        .value.ident = text
    };

    return t;
}

Token lexer_next(Lexer *l) {
    lexer_skip(l);

    char c = lexer_current(l);

    if (isdigit(c))
        return lexer_number(l);

    if (isalpha(c) || c == '_')
        return lexer_ident_keyword(l);

    Token t = {0};

    switch (c) {
        case('+'): lexer_advance(l); t.type = T_PLUS;     return t;
        case('-'): lexer_advance(l); t.type = T_MINUS;    return t;
        case('*'): lexer_advance(l); t.type = T_MULTIPLY; return t;
        case('/'): lexer_advance(l); t.type = T_DIVIDE;   return t;
        case('='): lexer_advance(l); t.type = T_ASSIGN;   return t;

        case('('): lexer_advance(l); t.type = T_LPAREN; return t;
        case(')'): lexer_advance(l); t.type = T_RPAREN; return t;
        case('{'): lexer_advance(l); t.type = T_LBRACE; return t;
        case('}'): lexer_advance(l); t.type = T_RBRACE; return t;
        case('['): lexer_advance(l); t.type = T_LBRACK; return t;
        case(']'): lexer_advance(l); t.type = T_RBRACK; return t;

        case('\n'): lexer_advance(l); t.type = T_EOL; return t;
        case('\0'): t.type = T_EOF;                   return t;
    }

    printf("Unkown character: %c at (%d, %d)\n", c, l->line, l->column);
    exit(1);
}

Token* lexer_tokens(char* content) {
    Lexer l = {.content = content, .pos = 0};

    int tokens_capacity = 16;
    Token* tokens = malloc(sizeof(Token) * tokens_capacity);

    int i = 0;
    Token t = {0};

    do {
        t = lexer_next(&l);
        token_print(t);

        if (i >= tokens_capacity) {
            tokens_capacity *= 2;
            tokens = realloc(tokens, sizeof(Token) * tokens_capacity);
        }

        tokens[i] = t;

        i++;
    } while (t.type != T_EOF);

    return tokens;
}
