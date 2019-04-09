all: main.c
	gcc main.c -o EXEC

clang: main.c
	clang main.c -o EXEC

clear: main.c
	rm EXEC

run: main.c
	./EXEC
