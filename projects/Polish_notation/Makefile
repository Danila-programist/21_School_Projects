CFLAGS = -Wextra -Werror -Wall -c
CC = gcc 

all : graph

graph : graph.o stack.o algorithm.o output.o
	$(CC) graph.o stack.o algorithm.o output.o -o graph

graph.o : graph.c
	$(CC) $(CFLAGS) graph.c 

output.o : output.c
	$(CC) $(CFLAGS) output.c

stack.o : stack.c
	$(CC) $(CFLAGS) stack.c

algorithm.o : algorithm.c
	$(CC) $(CFLAGS) algorithm.c

clean : 
	rm -rf *.o graph

rebuild : clean all
