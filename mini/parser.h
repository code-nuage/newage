#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// --+ Parser +--
typedef struct {
    Token *tokens;
    int pos;
} Parser;

// --+ AST +--
typedef enum {
    AST_NUMBER,
    AST_BINARY,
    AST_PRINT
} ASTType;

typedef struct AST AST;

struct AST {
    ASTType type;
    
    union {
        int number;

        struct {
            AST* right;
            AST* left;
            TokenType operator;
        } binary;

        struct {
            AST *expr;
        } print;
    };
};

typedef struct {
    AST **statements;
    int count;
} ASTProgram;

// --+ Types +--
AST *parse_expression(Parser *p);
AST *parse_factor(Parser *p);
AST *parse_term(Parser *p);
AST *parse_statement(Parser *p);
ASTProgram *parse_program(char *content);

// --+ Manipulation +--
Token pars_current(Parser* p);
void pars_advance(Parser* p);

// --+ Processing +--
void print_ast(AST *node, int indent);
void print_program(ASTProgram *program);

#endif // PARSER_H
