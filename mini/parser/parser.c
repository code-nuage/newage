#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

#include "../lexer/lexer.h"

Token p_current(Parser* p) {
    return p->tokens[p->pos];
}

void p_advance(Parser* p) {
    if (p->tokens[p->pos].type != TOKEN_EOF)
        p->pos++;
}

AST *p_factor(Parser *p) {
    Token t = p_current(p);

    if (t.type == TOKEN_NUMBER) {
        p_advance(p);

        AST *node = malloc(sizeof(AST));
        node->type = AST_NUMBER;
        node->number = t.value;

        return node;
    };

    if (t.type == TOKEN_LPAREN) {
        p_advance(p);

        AST *expr = p_expression(p);
        
        if (p_current(p).type != TOKEN_RPAREN) {
            printf("Expected )\n");
            exit(1);
        }

        p_advance(p);
        return expr;
    };

    printf("Unexpected token\n");
    exit(1);
}

AST *p_term(Parser *p) {
    AST *left = p_factor(p);
    
    while(p_current(p).type == TOKEN_STAR || p_current(p).type == TOKEN_SLASH) {
        TokenType operator = p_current(p).type;
        p_advance(p);

        AST *right = p_factor(p);
        AST *node = malloc(sizeof(AST));
        node->type = AST_BINARY;
        node->binary.left = left;
        node->binary.right = right;
        node->binary.operator = operator;

        left = node;
    }

    return left;
}

AST *p_expression(Parser *p) {
    AST *left = p_term(p);

    while (p_current(p).type == TOKEN_PLUS ||
           p_current(p).type == TOKEN_MINUS) {

        TokenType operator = p_current(p).type;
        p_advance(p);

        AST *right = p_term(p);

        AST *node = malloc(sizeof(AST));
        node->type = AST_BINARY;
        node->binary.left = left;
        node->binary.right = right;
        node->binary.operator = operator;

        left = node;
    }

    return left;
}

AST *p_statement(Parser *p) {
    Token t = p_current(p);

    if (t.type == TOKEN_PRINT) {
        p_advance(p);

        AST *expr = p_expression(p);

        if (p_current(p).type != TOKEN_RETURN) {
            printf("Expected newline\n");
            exit(1);
        }

        p_advance(p);

        AST *node = malloc(sizeof *node);
        node->type = AST_PRINT;
        node->print.expr = expr;

        return node;
    }

    printf("Unknown statement\n");
    exit(1);
}

ASTProgram *p_program(char *content) {
    Token *tokens = l_tokens(content, 100);

    Parser p = {
        .pos = 0,
        .tokens = tokens
    };

    ASTProgram *program = malloc(sizeof(ASTProgram));
    program->statements = malloc(sizeof(AST*) * 100);
    program->count = 0;

    while (p_current(&p).type != TOKEN_EOF) {
        AST *stmt = p_statement(&p);
        program->statements[program->count++] = stmt;
    }

    return program;
}
