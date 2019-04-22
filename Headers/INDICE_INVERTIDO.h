/*
   Josué Nunes Campos - 3465
   Mateus Coelho Santos - 3488
   Samuel Pedro Campos Sena - 3494
*/
#ifndef INDICE_INVERTIDO_H_INCLUDED
#define INDICE_INVERTIDO_H_INCLUDED

#include "TF_IDF.h"//Incluíndo o TAD que faz o cálculo da relevância de um documento

typedef struct TipoCelula *TipoCelPoint;//Renomeação do ponteiro para a struct TipoCelula

typedef struct TipoCelula {//Célula da Lista de índices invertidos
  int IdDoc, qtde;//As chaves são o ID do documento e a quantidade de vezes da palavra no documento
  TipoCelPoint Prox;//Ponteiro para a próxima célula
} TipoCelula;

typedef struct {//Struct contendo os ponteiros de referência da lista
  TipoCelPoint Primeiro, Ultimo;//Ponteiros primeiro (aponta para o começo da lista) e último (aponta para o fim da lista)
} TipoLista;

//Cabeçalhos das funções que manipulam a lista
void FLVazia(TipoLista *Lista);//Faz uma lista vazia
void InsereIndice(TipoLista *Lista, int idDoc, int Qtde);//Insere uma célula na lista
int ProcuraIdDoc(TipoLista *Lista, int idDoc, TipoQtdeTermos *Ni);//Procura e compara se já existe o ID passado como parâmetro
void Imprime(TipoLista Lista);//Imprime a lista
int ContaCelulaLista(TipoLista Lista);//Conta quantos documentos tem na lista
void RetornaQtdeEidDocs(TipoLista Lista, int *F, int *D);//Retorna as chaves de todas as células da lista
#endif
