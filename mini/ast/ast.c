#include "ast.h"

#include <stdio.h>

#include "../token/token.h"

void a_print(AST *node, int indent) {
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

            a_print(node->binary.left, indent + 1);
            a_print(node->binary.right, indent + 1);
            break;

        case AST_EXPR:
            printf("Print:\n");
            a_print(node->expr.text, indent + 1);
            break;

        default:
            printf("Unknown AST node\n");
    }
}

void a_print_program(ASTProgram *program) {
    for (int i = 0; i < program->count; i++) {
        a_print(program->statements[i], 0);
    }
}
