#include "lexer/lexer.h"
#include <stdio.h>

int main(int argc, char **argv) {
    Token *t = lexer_tokens("a = 1 + 1\nif (a) { print(\"test\")}\0");

    return 0;
}