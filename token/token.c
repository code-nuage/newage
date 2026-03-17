#include "token.h"
#include <stdio.h>
#include <stdlib.h>

char *token_display(Token t) {
    char *buffer = malloc(64);
    switch (t.type) {
        // Literals
        case(T_IDENT): sprintf(buffer, "IDENT(%s)", t.value.ident); return buffer;
        case(T_STRING): sprintf(buffer, "STRING(%s)", t.value.string); return buffer;
        case(T_NUMBER): sprintf(buffer, "NUMBER(%f)", t.value.number); return buffer;

        // Delimiters
        case(T_LPAREN): return "("; // (
        case(T_RPAREN): return ")"; // )
        case(T_LBRACE): return "{"; // {
        case(T_RBRACE): return "}"; // }
        case(T_LBRACK): return "["; // [
        case(T_RBRACK): return "]"; // ]

        case(T_DOT): return ".";    // .
        case(T_COMMA): return ",";  // ,
        case(T_COLON): return ":";  // :

        // Operators
        case(T_PLUS): return "+";     // +
        case(T_MINUS): return "-";    // -
        case(T_MULTIPLY): return "*"; // *
        case(T_DIVIDE): return "/";   // /
        case(T_MOD): return "%";      // %
        case(T_ASSIGN): return "=";   // =
        
        case(T_EQUAL): return "==";         // ==
        case(T_NOT_EQUAL): return "!=";     // !=
        case(T_GREATER): return ">";        // >
        case(T_GREATER_EQUAL): return ">="; // >=
        case(T_LESS): return "<";           // <
        case(T_LESS_EQUAL): return "<=";    // <=

        case(T_AND): return "&&"; // &&
        case(T_OR): return "||";  // ||
        case(T_NOT): return "!";  // !

        // Keywords
        case(T_LOCAL): return "local";   // local
        case(T_GLOBAL): return "global"; // global

        case(T_IF): return "if";             // if
        case(T_ELSE): return "else";         // else
        case(T_FOR): return "for";           // for
        case(T_WHILE): return "while";       // while
        case(T_DO): return "do";             // do
        case(T_FUNC): return "function";     // function
        case(T_RETURN): return "return";     // return
        case(T_BREAK): return "break";       // break
        case(T_CONTINUE): return "continue"; // continue

        case(T_BOOL_TYPE): return "bool";     // bool
        case(T_INT_TYPE): return "int";       // int
        case(T_FLOAT_TYPE): return "float";   // float
        case(T_STRING_TYPE): return "string"; // string
        case(T_TABLE_TYPE): return "table";   // table

        case(T_TRUE): return "true";   // true
        case(T_FALSE): return "false"; // false

        // Other
        case(T_EOF): return "EOF"; // \0
        case(T_EOL): return "EOL"; // \n

        default: return "Unknown token";
    }
}

void token_print(Token t) {
    printf("%s\n", token_display(t));
}
