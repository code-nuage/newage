#ifndef AST_H
#define AST_H

#include "../token/token.h"

typedef enum {
    AST_NUMBER,
    AST_BINARY,
    AST_EXPR
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
            AST *text;
        } expr;
    };
};

typedef struct {
    AST **statements;
    int count;
} ASTProgram;

void a_print(AST *node, int indent);
void a_print_program(ASTProgram *program);

#endif // AST_H
