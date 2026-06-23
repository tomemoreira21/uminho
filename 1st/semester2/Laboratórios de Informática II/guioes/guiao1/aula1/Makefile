#Compilador utilizado 
CC = gcc 

#Flags necessárias 
CFLAGS = -ggdb 

#Ficheiros .c para compilar 
OBJS = main.c quad.c 

#Bibliotecas necessárias 
LIBS = -lm 

#Nome do executável 
TARGET = programa 

#Compilação conjunta
$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

#Compilação separada 
main.o : main.c 
	$(CC) $(CFLAGS) -c main.c 

quad.o : quad.c 
	$(CC) $(CFLAGS) -c quad.c 

