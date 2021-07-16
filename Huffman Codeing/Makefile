EXEC = options

CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror

all: encode decode entropy

encode: 
	$(CC) $(CFLAGS) -o encode encode.c code.c huffman.c io.c node.c pq.c stack.c globalvar.c -lm

decode: 
	$(CC) $(CFLAGS) -o decode decode.c code.c huffman.c io.c node.c pq.c stack.c globalvar.c -lm

entropy: 
	$(CC) $(CFLAGS) -o entropy entropy.c -lm

clean:
	rm -f error entropy sorting encode decode *.o

format:
	clang-format -i -style=file *.c *.h

scan-build: clean
	scan-build make
