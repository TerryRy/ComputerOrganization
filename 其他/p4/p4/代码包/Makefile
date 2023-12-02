CC = gcc
CFLAGS = -g -std=c99 -Wall

all: linker assembler

linker: clean
	$(CC) $(CFLAGS) -o linker linker.c my_assembler_utils.c my_linker_utils.c -L. -lP4

assembler: clean
	$(CC) $(CFLAGS) -o assembler assembler.c my_assembler_utils.c -L. -lP4

clean:
	rm -f *.o linker assembler
