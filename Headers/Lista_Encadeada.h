#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H
#include <stdio.h>
#include <stdlib.h>
typedef struct Celula{
  int idDoc;
  int qtde;
  struct Celula* pProx;
}TCelula;//Nome TipoCelula para substituir a struct//
typedef struct Lista{
  struct Celula* pPrimeiro;
  struct Celula* pUltimo;
}TLista; //Nome TipoLista para substituir a struct//     //pLista é um ponteiro para o tipo TLista.//
void Inicia_Lista(TLista* pLista); //Passando por parametro ponteiro do tipo da struct TipoLista para acessar structs//
int Lista_Vazia(TLista* pLista); //Função para verificar se lista encontra-se vazia.//
int Insere_Lista(TLista* pLista,int Doc, int qt);
int Procura_Lista(TLista* pLista,TCelula* pAux_Celula,int Doc);
int Incrementa_qtde(TLista* pLista,int Doc);
void Imprime_Lista(TLista* pLista);
#endif
