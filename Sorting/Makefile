EXEC = options

CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror

all: sorting

sorting: set.o sorting.o bubble.o queue.o quick.o shell.o stack.o globalvar.o

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

set.o: set.c
	$(CC) $(CFLAGS) -c set.c

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c
globalvar.o: globalvar.c
	$(CC) $(CFLAGS) -c globalvar.c 


clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *.c *.h

scan-build: clean
	scan-build make
