OBJECTS = main.o bst.o

FLAGS  = -g -Wall -Werror -Wextra
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(OBJECTS)
	@gcc $(OBJECTS) -o exec $(FLAGS)

main.o: main.c bst.h
	@gcc main.c -c $(FLAGS)

bst.o: bst.c bst.h
	@gcc bst.c -c $(FLAGS)

run: all
	@./exec

valgrind: all
	@valgrind $(VFLAGS) ./exec

clean:
	@rm -rf *.o exec

zip:
	@zip bst.zip Makefile main.c bst.c bst.h
