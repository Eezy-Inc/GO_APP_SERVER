CC=clang
CFLAGS=-g

all: socket

socket: src/main.c
	$(CC) $(CFLAGS) -o socket src/main.c

clean:
	rm -rf *.dSYM socket
