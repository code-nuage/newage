#include "lexer.h"

#include <ctype.h>

typedef struct {
    const char *keyword;
    TokenType type;
} KeywordMap;

static const KeywordMap keywords[] = { // Map the TokenTypes to its strings
    {"local",     TOKEN_LOCAL},
    {"global",    TOKEN_GLOBAL},
    {"if",        TOKEN_IF},
    {"else",      TOKEN_ELSE},
    {"for",       TOKEN_FOR},
    {"while",     TOKEN_WHILE},
    {"do",        TOKEN_DO},
    {"function",  TOKEN_FUNC},
    {"return",    TOKEN_RETURN},
    {"break",     TOKEN_BREAK},
    {"continue", TOKEN_CONTINUE},
    {"bool",     TOKEN_BOOL_TYPE},
    {"int",      TOKEN_INT_TYPE},
    {"float",    TOKEN_FLOAT_TYPE},
    {"string",   TOKEN_STRING_TYPE},
    {"table",    TOKEN_TABLE_TYPE},
    {"true",     TOKEN_TRUE},
    {"false",    TOKEN_FALSE}
};

// Utils
char lexer_current(Lexer *l) {
    return l->content[l->pos];
}

void lexer_advance(Lexer *l) {
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
Token lexer_keyword(Lexer *l) {
    
}

Token lexer_next(Lexer *l) {
    lexer_skip(l);

    if (isdigit(lexer_current(l)))
        return lexer_number(l);

    if (isalpha(lexer_current(l)))
        return lexer_keyword(l);
}
