EXEC = options

CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror

all: encode decode error entropy

encode: 
	$(CC) $(CFLAGS) -o encode encode.c  bm.c bv.c hamming.c -lm

decode: 
	$(CC) $(CFLAGS) -o decode decode.c  globalvar.c bm.c bv.c hamming.c -lm

error: 
	$(CC) $(CFLAGS) -o error error.c -lm

entropy: 
	$(CC) $(CFLAGS) -o entropy entropy.c -lm

clean:
	rm -f error entropy sorting encode decode *.o

format:
	clang-format -i -style=file *.c *.h

scan-build: clean
	scan-build make
