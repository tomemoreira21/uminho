# Makefile para compilar interpretador + main

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -g

# Arquivos
SRC = main.c interpretador.c
HEADERS = interpretador.h

# Executável
TARGET = interpretador

# Regra padrão
all: $(TARGET)

# Compila e gera o executável
$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Limpeza de arquivos object e executável
clean:
	rm -f $(TARGET) *.o

# Atalho para compilar e limpar depois
rebuild: clean all

.PHONY: all clean rebuild