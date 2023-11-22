OBJECTS = main.o llist.o

FLAGS  = -g -Wall -Werror -Wextra
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(OBJECTS)
	@gcc $(OBJECTS) -o exec $(FLAGS)

main.o: main.c llist.h
	@gcc main.c -c $(FLAGS)

llist.o: llist.c llist.h
	@gcc llist.c -c $(FLAGS)

run: all
	@./exec

valgrind: all
	@valgrind $(VFLAGS) ./exec

clean:
	@rm -rf *.o exec

zip:
	@zip llist.zip Makefile main.c llist.c llist.h
