CC = gcc
CFLAGS = -Wall

SRCS = main.c lexer/lexer.c token/token.c
TARGET = newage

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean