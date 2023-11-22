run: compile
	./exec

valgrind: compile
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./exec

clean:
	rm -rf *.o exec

compile: conjuntos.o main.o
	gcc conjuntos.o main.o -o exec   -g -Wall -Werror -Wextra

conjuntos.o: conjuntos.c conjuntos.h
	gcc conjuntos.c -c               -g -Wall -Werror -Wextra

main.o: main.c
	gcc main.c -c                    -g -Wall -Werror -Wextra
