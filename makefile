CC = gcc
CFLAGS = -Wall -g -std=c99
TARGET = scanner
OBJ1 = main.o scanner.o
$(TARGET): $(OBJ1)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ1)
main.o: main.c scanner.h token.h
	$(CC) $(CFLAGS) -c main.c
scanner.o: scanner.c  scanner.h types.h
	$(CC) $(CFLAGS) -c scanner.c

clean:
	/bin/rm -f *.o  $(TARGET)

