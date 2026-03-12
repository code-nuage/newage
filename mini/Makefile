# Compiler et flags
CC = gcc
CFLAGS = -Wall

# Fichiers
SRCS = main.c lexer.c
TARGET = main

# Règles
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean