# Compiler et flags
CC = gcc
CFLAGS = -Wall

# Fichiers
SRCS = main.c lexer.c parser.c
TARGET = newage

# Règles
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean