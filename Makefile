CC=g++
CFLAGS=-c -Wall
all: csvreader

csvreader: csvreader.o
	$(CC) csvreader.o -o csvreader

csvreader.o: csvreader.cpp
	$(CC) $(CFLAGS) csvreader.cpp

clean:
	rm -rf *.o *.out csvreader
