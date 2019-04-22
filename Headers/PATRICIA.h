/*
   Josué Nunes Campos - 3465
   Mateus Coelho Santos - 3488
   Samuel Pedro Campos Sena - 3494
*/
#ifndef PATRICIA_H_INCLUDED
#define PATRICIA_H_INCLUDED

#include "INDICE_INVERTIDO.h"//Incluíndo o TAD que contém a lista de índice invertido

typedef enum{//Enumeração usada para indicar qual tipo é o Nó
  Interno, Externo//Enumeração Interno para Nó Interno e enumeração Externo para Nó Externo
}TipoNo;

typedef struct TipoPatNo* TipoArvore;//Renomeando o ponteiro para struct TipoPatNo
typedef char* TipoChave;//Renomeando o ponteiro para Char

typedef struct{//Dados que estarão contidos no nó externo (nó folha)
  TipoLista Lista;//Lista de índice invertido
  TipoChave Chave;//Palavra de um documento
}TipoDados;

typedef struct TipoPatNo{//Struct que define a árvore PATRICIA
  TipoNo TipoDoNo;//Tipo que o Nó será
  union{//Utilização da Union para economia de memória ao dividir para Nó interno ou externo
    struct{//Dados que estarão contidos no nó interno
      int Index;//Posição que difere nas comparações entre duas palavras
      char LetraComp;//Menor letra que difere nas comparações entre duas palavras
      TipoArvore Esq, Dir;//Apontadores para a Esquerda e para a Direita
    }NInterno;
    TipoDados Conteudo;//Variável do tipo de dado que contém o que o nó externo guarda
  }NO;//Fim da Union
}TipoPatNo;

//Cabeçalhos das funções que manipulam a árvore PATRICIA
void InicializaPat(TipoArvore *t);//Inicializa o ponteiro da árvore
int CalculaIndice(TipoChave k, TipoChave Palavra, int N);//Retorna qual índice que difere entre duas palavras
int ComparaChaves(TipoChave k, TipoChave Palavra, int TAM1, int TAM2);//Encapsula a função acima de acordo com os tamanhos das duas palavras
int ComparaLetra(int i, char Letra, TipoChave Palavra);//Retorna 0 se a letra da palavra a ser inserida é menor ou igual a da chave no nó folha ou 1 se for maior
int EExterno(TipoArvore p);//Verifica se o nó passado como parâmetro é externo, retornando 1 se for ou 0 se não for
TipoArvore CriaNoInt(int i, TipoArvore *Esq, TipoArvore *Dir, char letra);//Realiza a criação de um nó interno
TipoArvore CriaNoExt(TipoChave Palavra, int idDoc);//Realiza a criação de um nó externo
//void PesquisaPat(TipoChave Palavra, TipoArvore t);//Pesquisa uma dada chave na árvore
TipoArvore PesquisaNO(TipoChave Palavra,TipoArvore t);//Pesquisa uma dada chave na árvore, retornando o endereço de seu Nó se encontrar ou NULL se não encontrar
char AchaLetra(TipoArvore *p, int i, TipoChave Palavra);//Retorna a menor letra entre duas palavras
TipoArvore InsereEntre(TipoChave Palavra, TipoArvore *t, int i, int idDoc);//Insere entre dois nós quando preciso
TipoArvore *AchaNoFolha(TipoArvore *ap);//Retorna um nó externo contendo a chave para ser comparada com a palavra a ser inserida
TipoArvore Insere(TipoChave Palavra, TipoArvore *t, int idDoc, TipoQtdeTermos *Ni);//Encapsulamento da função acima, chamando-a quando já há um ou mais nós criados
void ImprimePat(TipoArvore t);//Imprime a árvore PATRICIA
#endif
