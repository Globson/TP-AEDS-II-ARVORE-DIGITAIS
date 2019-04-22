all: main.c Sources/INDICE_INVERTIDO.c Sources/LEITURA.c Sources/PATRICIA.c Sources/TST.c Sources/TF_IDF.c
	gcc main.c -o EXEC Sources/INDICE_INVERTIDO.c Sources/LEITURA.c Sources/PATRICIA.c Sources/TST.c Sources/TF_IDF.c -lm

run: EXEC
	./EXEC

clear: EXEC
	rm EXEC
