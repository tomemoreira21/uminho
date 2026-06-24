.PHONY: all clean

CC = gcc
CFLAGS = -Wall -Wextra -g -Imodules -Isrc -I../../../guiao1/deque

TARGET = main

SRCS = main.c \
       src/balcao.c \
       src/cliente.c \
       src/servico.c \
       src/sistema_gestao.c \
       src/interface.c \
       ../../../guiao1/deque/deque.c \
       ../../../guiao1/deque/node.c

OBJS = build/main.o \
       build/balcao.o \
       build/cliente.o \
       build/servico.o \
       build/sistema_gestao.o \
       build/interface.o \
       build/deque.o \
       build/node.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Regras para src
build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para main
build/main.o: main.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para deque
build/deque.o: ../../guiao1/deque/deque.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/node.o: ../../guiao1/deque/node.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)
