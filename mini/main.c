#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

#define BLOCK_SIZE 24
#define BLOCK_COUNT 10

char *read_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *buffer = malloc(size + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    if (fread(buffer, 1, size, file) != size) {
        fclose(file);
        free(buffer);
        return NULL;
    }
    buffer[size] = '\0';

    fclose(file);
    return buffer;
}

int main(int argc, char** argv) {
    char* content = read_file("test.na");

    Lexer l = {.input = content, .pos = 0};
    Token tokens[50];

    int i = 0;

    while (1) {
        tokens[i] = next_token(&l);
        print_token(tokens[i]);

        if (tokens[i].type == TOKEN_EOF)
            break;

        i++;
    }

    return 0;
}
