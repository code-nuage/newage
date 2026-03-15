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

int infix_binding_power(TokenType type, int *left, int *right) {
    switch (type) {
        case TOKEN_PLUS:
        case TOKEN_MINUS:
            *left = 10;
            *right = 11;
            return 1;
        case TOKEN_STAR:
        case TOKEN_SLASH:
            *left = 20;
            *right = 21;
            return 1;
        
        default:
            return 0;
    }
}

AST *nud(Parser *p, Token t) {
    if (t.type == TOKEN_NUMBER) {
        AST *node = malloc(sizeof(AST));
        node->type = AST_NUMBER;
        node->number = t.value;
        return node;
    }

    if (t.type == TOKEN_LPAREN) {

        AST *expr = p_expression(p, 0);

        if (p_current(p).type != TOKEN_RPAREN) {
            printf("Expected )\n");
            exit(1);
        }

        p_advance(p);
        return expr;
    }

    printf("Unexpected token\n");
    exit(1);
}

AST *p_expression(Parser *p, int min_bp) {
    Token t = p_current(p);
    p_advance(p);

    AST *left = nud(p, t);

    while (1) {
        Token op = p_current(p);

        int left_bp, right_bp;

        if (!infix_binding_power(op.type, &left_bp, &right_bp))
            break;

        if (left_bp < min_bp)
            break;

        p_advance(p);

        AST *right = p_expression(p, right_bp);

        AST *node = malloc(sizeof(AST));
        node->type = AST_BINARY;

        node->binary.left = left;
        node->binary.right = right;
        node->binary.operator = op.type;

        left = node;
    }

    return left;
}

AST *p_statement(Parser *p) {
    Token t = p_current(p);

    if (t.type == TOKEN_IDENT) {
        p_advance(p);

        AST *expr = p_expression(p, 0);

        if (p_current(p).type != TOKEN_RETURN) {
            printf("Expected newline\n");
            exit(1);
        }

        p_advance(p);

        AST *node = malloc(sizeof(AST));
        node->type = AST_EXPR;
        node->expr.text = expr;

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
