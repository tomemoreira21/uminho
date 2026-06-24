CC = gcc 
LDFLAGS = 
CFLAGS = -Wall -c 

all: main 

main: main.o deque.o node.o
	$(CC) main.o deque.o node.o $(LDFLAGS) -o main

main.o: main.c 
	$(CC) $(CFLAGS) main.c -o main.o

deque.o: deque.c 
	$(CC) $(CFLAGS) deque.c -o deque.o

node.o: node.c 
	$(CC) $(CFLAGS) node.c -o node.o

clean:
	rm -f deque.o main.o node.o main