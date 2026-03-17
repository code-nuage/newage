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
char lexer_next(Lexer *l);
void lexer_advance(Lexer *l);
void lexer_skip(Lexer *l);

// Lexer
Token lexer_number(Lexer *l);
Token lexer_string(Lexer *l);
Token lexer_operator(Lexer *l, char first);
Token lexer_ident_keyword(Lexer *l);

Token lexer_next_token(Lexer *l);
Token *lexer_tokens(char *content);

#endif
