/*
   Josué Nunes Campos - 3465
   Mateus Coelho Santos - 3488
   Samuel Pedro Campos Sena - 3494
*/
#ifndef LEITURA_H_INCLUDED
#define LEITURA_H_INCLUDED

#include "PATRICIA.h"//Incluíndo o TAD que contém a árvore PATRICIA
#include "TST.h"//Incluíndo o TAD que contém a árvore TST

typedef struct TipoCelulaFila *TipoFilPoint;//Renomeando o ponteiro para a struct TipoCelulaFila

typedef struct TipoCelulaFila {//Célula da fila de caracteres
  char letra;//Caracter da palavra que será lida
  TipoFilPoint Prox;//Apontador para a próxima célula da fila
} TipoCelulaFila;

typedef struct TipoFila {//Struct contendo os apontadores de referência da fila
  TipoFilPoint Frente, Tras;//Ponteiros frente (aponta para o começo da fila) e trás (aponta para o final da fila)
} TipoFila;

void FFVazia(TipoFila *Fila);//Faz uma fila vazia
int Vazia(TipoFila Fila);//Verifica se a fila é vazia
void Enfileira(TipoFila *Fila, char Caract);//Adiciona um novo caracter à fila
void Desenfileira(TipoFila *Fila, TipoChave Item);//Remove um caracter da fila
int ContaCelula(TipoFila Fila);//Conta quantos caracteres tem uma palavra
TipoQtdeTermos* Leitura(TipoArvore *t, TipoApontador *RaizTST, int *N);//Realiza a leitura dos arquivos retornando quantos elementos distintos possuem cada arquivo
void Busca(TipoArvore t, int N, TipoQtdeTermos *Ni, TipoApontador RaizTST);//Realiza a busca de palavras e exibe os documentos mais relevantes
void menu(TipoArvore *P, TipoApontador *Pt, int *N, TipoQtdeTermos *Ni);//Menu contendo as opções de uso do programa
#endif
