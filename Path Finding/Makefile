EXEC = options

CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror

all: tsp

tsp: tsp.o graph.o path.o stack.o globalvar.o

tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

path.o: path.c
	$(CC) $(CFLAGS) -c path.c

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
