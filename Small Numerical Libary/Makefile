CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror

all: mathlib-test

mathlib-test:
	$(CC) $(CFLAGS) -o mathlib-test mathlib-test.c  mathlib.c -lm

clean:
	rm -f mathlib-test mathlib-test.o mathlib.o

scan-build: clean
	scan-build make
