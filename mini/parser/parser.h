#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"
#include "../ast/ast.h"

typedef struct {
    Token *tokens;
    int pos;
} Parser;

AST *p_expression(Parser *p, int min_bp);
AST *p_statement(Parser *p);
ASTProgram *p_program(char *content);

Token p_current(Parser *p);
void p_advance(Parser *p);

#endif // PARSER_H
