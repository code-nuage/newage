#include "token.h"

#include <stdio.h>

char* t_display(Token t) {
    switch (t.type) {
        case TOKEN_IDENT:
            return "IDENT";
        case TOKEN_NUMBER:
            return "NUMBER";
        case TOKEN_PRINT:
            return "PRINT";
        case TOKEN_PLUS:
            return "PLUS";
        case TOKEN_MINUS:
            return "MINUS";
        case TOKEN_STAR:
            return "STAR";
        case TOKEN_SLASH:
            return "SLASH";

        case TOKEN_EQUAL:
            return "EQUAL";

        case TOKEN_LPAREN:
            return "LPAREN";
        case TOKEN_RPAREN:
            return "RPAREN";

        case TOKEN_RETURN:
            return "RETURN";
        case TOKEN_EOF:
            return "EOF";

        default:
            return "TOKEN";
    }
}

void t_print(Token t) {
    printf("%s\n", t_display(t));
}
