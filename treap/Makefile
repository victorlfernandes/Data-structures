OBJECTS = main.o treap.o str.o

FLAGS  = -g -Wall -Werror -Wextra
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(OBJECTS)
	@gcc $(OBJECTS) -o exec $(FLAGS)

main.o: main.c treap.h
	@gcc main.c -c $(FLAGS)

treap.o: treap.c treap.h
	@gcc treap.c -c $(FLAGS)

str.o: str.c str.h
	@gcc str.c -c $(FLAGS)

run: all
	@./exec

valgrind: all
	@valgrind $(VFLAGS) ./exec

clean:
	@rm -rf *.o exec

zip:
	@zip treap.zip Makefile main.c treap.c treap.h str.c str.h
