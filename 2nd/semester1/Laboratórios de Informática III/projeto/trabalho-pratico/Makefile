.PHONY: all clean run_valgrind

CC = gcc 
CFLAGS = -Wall -Wextra -O3 -flto -march=native -Iinclude `pkg-config --cflags glib-2.0` 
LDFLAGS = `pkg-config --libs glib-2.0` -lncurses -lm

TARGETS = programa-principal programa-testes programa-interativo

# Encontra todos os ficheiros .c dentro de src e subpastas
SRC_FILES := $(shell find src -name '*.c')
OBJ_FILES := $(SRC_FILES:.c=.o)

all: $(TARGETS)

programa-principal: $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

programa-testes: $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

programa-interativo: $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

# Regra genérica para compilar .c → .o
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run_valgrind: programa-principal
	valgrind --leak-check=full ./programa-principal || true

# Gera a documentação HTML
docs:
	doxygen Doxyfile

clean:
	rm -f $(OBJ_FILES)
	rm -f $(TARGETS)
	rm -f resultados/*.txt resultados/*.csv resultados/*.psv resultados/*.tsv
	rm -rf html latex