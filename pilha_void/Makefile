all:
	gcc *.c -o exec -g

run: 
	./exec

clean:
	rm -rf *.o exec

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./exec
