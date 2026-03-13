#include <stdio.h>
#include <stdlib.h>

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
            AST* left;
            AST* right;
            TokenType operator;
        } binary;

        struct {
            struct AST *expr;
        } print;
    };
};

typedef struct {
    AST **statements;
    int count;
} ASTProgram;

// --+ Types +--
AST *parse_expression(Parser *p);

// --+ Manipulation +--
Token pars_current(Parser* p) {
    return p->tokens[p->pos];
}

void pars_advance(Parser* p) {
    if (p->tokens[p->pos].type != TOKEN_EOF)
        p->pos++;
}

// --+ Parsers +--
AST *parse_factor(Parser *p) {
    Token t = pars_current(p);

    if (t.type == TOKEN_NUMBER) {
        pars_advance(p);

        AST *node = malloc(sizeof(AST));
        node->type = AST_NUMBER;
        node->number = t.value;

        return node;
    };

    if (t.type == TOKEN_LPAREN) {
        pars_advance(p);

        AST *expr = parse_expression(p);
        
        if (pars_current(p).type != TOKEN_RPAREN) {
            printf("Expected )\n");
            exit(1);
        }

        pars_advance(p);
        return expr;
    };

    printf("Unexpected token\n");
    exit(1);
}

AST *parse_term(Parser *p) {
    AST *left = parse_factor(p);
    
    while(pars_current(p).type == TOKEN_STAR || pars_current(p).type == TOKEN_SLASH) {
        TokenType operator = pars_current(p).type;
        pars_advance(p);

        AST *right = parse_factor(p);
        AST *node = malloc(sizeof(AST));
        node->type = AST_BINARY;
        node->binary.left = left;
        node->binary.right = right;
        node->binary.operator = operator;

        left = node;
    }

    return left;
}

AST *parse_expression(Parser *p) {
    AST *left = parse_term(p);

    while (pars_current(p).type == TOKEN_PLUS ||
           pars_current(p).type == TOKEN_MINUS) {

        TokenType operator = pars_current(p).type;
        pars_advance(p);

        AST *right = parse_term(p);

        AST *node = malloc(sizeof(AST));
        node->type = AST_BINARY;
        node->binary.left = left;
        node->binary.right = right;
        node->binary.operator = operator;

        left = node;
    }

    return left;
}

AST *parse_statement(Parser *p) {
    Token t = pars_current(p);

    if (t.type == TOKEN_PRINT) {
        pars_advance(p);

        AST *expr = parse_expression(p);

        if (pars_current(p).type != TOKEN_RETURN) {
            printf("Expected newline\n");
            exit(1);
        }

        pars_advance(p);

        AST *node = malloc(sizeof *node);
        node->type = AST_PRINT;
        node->print.expr = expr;

        return node;
    }

    printf("Unknown statement\n");
    exit(1);
}


// --+ Processing +--
ASTProgram *parse_program(char *content) {
    Token *tokens = lex_tokens(content, 100);

    Parser p = {
        .pos = 0,
        .tokens = tokens
    };

    ASTProgram *program = malloc(sizeof(ASTProgram));
    program->statements = malloc(sizeof(AST*) * 100);
    program->count = 0;

    while (pars_current(&p).type != TOKEN_EOF) {
        AST *stmt = parse_statement(&p);
        program->statements[program->count++] = stmt;
    }

    return program;
}

void print_ast(AST *node, int indent) {
    for (int i = 0; i < indent; i++) printf("  "); // indentation

    if (!node) return;

    switch (node->type) {
        case AST_NUMBER:
            printf("Number: %d\n", node->number);
            break;

        case AST_BINARY:
            printf("Binary: %s\n", 
                node->binary.operator == TOKEN_PLUS ? "+" :
                node->binary.operator == TOKEN_MINUS ? "-" :
                node->binary.operator == TOKEN_STAR ? "*" :
                node->binary.operator == TOKEN_SLASH ? "/" : "?");

            print_ast(node->binary.left, indent + 1);
            print_ast(node->binary.right, indent + 1);
            break;

        case AST_PRINT:
            printf("Print:\n");
            print_ast(node->print.expr, indent + 1);
            break;

        default:
            printf("Unknown AST node\n");
    }
}

void print_program(ASTProgram *program) {
    for (int i = 0; i < program->count; i++) {
        print_ast(program->statements[i], 0);
    }
}
