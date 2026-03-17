#include "lexer/lexer.h"

int main(int argc, char **argv) {
    Token *t = lexer_tokens("a: float = 1 + 2.5\nif (a) { print(\"test\")}\0");

    return 0;
}