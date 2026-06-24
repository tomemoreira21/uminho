.PHONY: all clean

# Compilador
CC = gcc

# Flags de compilação e includes necessários
CFLAGS = -Wall -Wextra -g -Icommand_parser -I../../guiao1/deque 

# Objetivo principal
all: main 

# Passo de linkagem
main: main.o command_parser/command_parser.o ../../guiao1/deque/deque.o ../../guiao1/deque/node.o
	$(CC) $^ $(LDFLAGS) -o $@

# Passos de compilação (cada .c → .o)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

command_parser/command_parser.o: command_parser/command_parser.c command_parser/command_parser.h
	$(CC) $(CFLAGS) -c command_parser/command_parser.c -o command_parser/command_parser.o

../../guiao1/deque/deque.o: ../../guiao1/deque/deque.c ../../guiao1/deque/deque.h
	$(CC) $(CFLAGS) -c ../../guiao1/deque/deque.c -o ../../guiao1/deque/deque.o

../../guiao1/deque/node.o: ../../guiao1/deque/node.c ../../guiao1/deque/node.h
	$(CC) $(CFLAGS) -c ../../guiao1/deque/node.c -o ../../guiao1/deque/node.o

clean:
	rm -f main main.o command_parser/command_parser.o ../../guiao1/deque/deque.o ../../guiao1/deque/node.o
