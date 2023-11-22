OBJECTS = main.o btree.o

FLAGS  = -g -Wall -Werror -Wextra
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(OBJECTS)
	@gcc $(OBJECTS) -o exec $(FLAGS)

main.o: main.c btree.h
	@gcc main.c -c $(FLAGS)

btree.o: btree.c btree.h
	@gcc btree.c -c $(FLAGS)

run: all
	@./exec

valgrind: all
	@valgrind $(VFLAGS) ./exec

clean:
	@rm -rf *.o exec

zip:
	@zip btree.zip Makefile main.c btree.c btree.h
