OBJECTS = main.o dllist.o

FLAGS  = -g -Wall -Werror -Wextra
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(OBJECTS)
	@gcc $(OBJECTS) -o exec $(FLAGS)

main.o: main.c dllist.h
	@gcc main.c -c $(FLAGS)

dllist.o: dllist.c dllist.h
	@gcc dllist.c -c $(FLAGS)

run: all
	@./exec

valgrind: all
	@valgrind $(VFLAGS) ./exec

clean:
	@rm -rf *.o exec

zip:
	@zip dllist.zip Makefile main.c dllist.c dllist.h
