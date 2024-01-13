CC=gcc
CFLAGS=-I.

corewars: ./src/main.c ./src/core.c
	$(CC) -o corewars main.c core.c $(CFLAGS)