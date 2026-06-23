CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2 -fsanitize=address -fno-omit-frame-pointer -g

programa: main.c problemaE.c problemaE.h
	$(CC) $(CFLAGS) -o programa main.c problemaE.c 
