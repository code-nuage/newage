#ifndef LEXER_H
#define LEXER_H

#include "../token/token.h"

typedef struct {
    const char *input;
    int pos;
    int line;
    int column;
} Lexer;

char l_current(Lexer *l);
void l_advance(Lexer *l);
void l_skip_whitespace(Lexer *l);
Token l_number(Lexer *l);
Token l_ident(Lexer *l);

Token l_next_token(Lexer *l);
Token* l_tokens(char* content, int size);

#endif // LEXER_H
