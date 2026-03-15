#ifndef LEXER_H
#define LEXER_H

typedef struct Lexer {
    char *content;
    int pos;

    int line;
    int column;
} Lexer;

char lexer_current(Lexer *l);
void lexer_advance(Lexer *l);
void lexer_skip(Lexer *l);

#endif
