OBJECTS = main.o skipl.o str.o

FLAGS  = -g -Wall -Werror -Wextra
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(OBJECTS)
	@gcc $(OBJECTS) -o exec $(FLAGS)

main.o: main.c skipl.h
	@gcc main.c -c $(FLAGS)

skipl.o: skipl.c skipl.h
	@gcc skipl.c -c $(FLAGS)

str.o: str.c str.h
	@gcc str.c -c $(FLAGS)

run: all
	@./exec

valgrind: all
	@valgrind $(VFLAGS) ./exec

clean:
	@rm -rf *.o exec

zip:
	@zip skipl.zip Makefile main.c skipl.c skipl.h str.c str.h
