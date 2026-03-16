#ifndef LEXER_H
#define LEXER_H

#include "../token/token.h"

typedef struct Lexer {
    const char *content;
    int pos;

    int line;
    int column;
} Lexer;

// Utils
char lexer_current(Lexer *l);
void lexer_advance(Lexer *l);
void lexer_skip(Lexer *l);

// Lexer
Token lexer_keyword(Lexer *l);
Token lexer_string(Lexer *l);
Token lexer_number(Lexer *l);
Token lexer_operator(Lexer *l);
Token lexer_ident(Lexer *l);
Token lexer_next(Lexer *l);

#endif
