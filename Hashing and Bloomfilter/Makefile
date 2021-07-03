EXEC = options

CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror

all: banhammer

banhammer: 
	$(CC) $(CFLAGS) -o banhammer banhammer.c bf.c bv.c ht.c ll.c node.c parser.c speck.c -lm -g

clean:
	rm -f banhammer *.o

format:
	clang-format -i -style=file *.c *.h

scan-build: clean
	scan-build make
