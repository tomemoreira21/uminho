CC = gcc 
LDFLAGS = 
CFLAGS = -Wall -c 

all: main 

main: main.o stack.o node.o
	$(CC) main.o stack.o node.o $(LDFLAGS) -o main

main.o: main.c 
	$(CC) $(CFLAGS) main.c -o main.o

stack.o: stack.c 
	$(CC) $(CFLAGS) stack.c -o stack.o

node.o: node.c 
	$(CC) $(CFLAGS) node.c -o node.o

clean:
	rm -f stack.o main.o node.o main