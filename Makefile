default: maze.c 
	gcc -g -Wall -O0 -o maze maze.c

clean:
	rm maze maze.o
