OBJECTS = main.o avl.o

FLAGS  = -g -Wall -Werror -Wextra
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(OBJECTS)
	@gcc $(OBJECTS) -o exec $(FLAGS)

main.o: main.c avl.h
	@gcc main.c -c $(FLAGS)

avl.o: avl.c avl.h
	@gcc avl.c -c $(FLAGS)

run: all
	@./exec

valgrind: all
	@valgrind $(VFLAGS) ./exec

clean:
	@rm -rf *.o exec

zip:
	@zip avl.zip Makefile main.c avl.c avl.h
