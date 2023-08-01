CC = gcc
CFLAGS = -Wall -Werror -O3 
LDFLAGS = 
all: build run

bmp.o: bmp.c bmp.h
	$(CC) $(CFLAGS) -c bmp.c -o bmp.o

main.o: main.c bmp.h
	$(CC) $(CFLAGS) -c main.c -o main.o

main: main.o bmp.o
	$(CC) $(LDFLAGS) main.o bmp.o -o main

build: main

run:
	./main

clean:
	rm -rf main main.o bmp.o

