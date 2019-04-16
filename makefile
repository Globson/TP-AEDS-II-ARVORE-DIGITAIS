all: main.c Sources/Patricia.c Sources/Lista_Encadeada.c
	gcc main.c -o EXEC Sources/Patricia.c Sources/Lista_Encadeada.c

clear: main.c
	rm EXEC

run: main.c
	./EXEC
