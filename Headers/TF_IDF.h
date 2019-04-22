/*
   Josué Nunes Campos - 3465
   Mateus Coelho Santos - 3488
   Samuel Pedro Campos Sena - 3494
*/
#ifndef TF_IDF_H_INCLUDED
#define TF_IDF_H_INCLUDED

typedef struct TipoCel *TipoPoint;//Renomeação do ponteiro para a struct TipoCel

typedef struct TipoCel {//Célula da lista de pesos
  int iddoc;//ID do documento
  double Peso;//Peso da palavra nesse documento
  TipoPoint prox;//Apontador para a próxima célula da lista
} TipoCel;

typedef struct {//Struct contendo os apontadores de referência da lista
  TipoPoint primeiro, ultimo;//Ponteiros primeiro (aponta para o começo da lista) e último (aponta para o final da lista)
} TipoList;

typedef struct{//Struct dedicada ao Vetor de Relevâncias
  int IDdoc;//ID do documento
  double Relevancia;//Relevância desse documento
}TipoRelevancia;

typedef struct{//Struct dedicada ao Vetor de Elementos Distintos
  int iDdOc, nTermsDist;//ID do documento e número de termos distintos desse documento
}TipoQtdeTermos;

//Cabeçalhos das funções que manipulam a lista, calculam o peso de uma palavra e relevância de um documento e ordenam o vetor de relevâncias
void InicializaNdoc(int *N);//Inicializando o número de documentos na coleção
void FListVazia(TipoList *Lista);//Faz uma lista vazia
void InserePeso(TipoList *Lista, int idDoc, double peso);//Insere na lista o peso de uma palavra em um documento
double SomaPesos(TipoList Lista, int idDoc);//Soma todos os pesos referentes à um documento
double CalculaPeso(int numOc, int numDocCterm, int numDocTot);//Calcula o peso de uma palavra em um documento
double CalculaRelevancia(double pesoTotal, int nI);//Calcula a relevância de um documento
void Particao(int Esq, int Dir, int *i, int *j, TipoRelevancia *vetor);//Função auxiliadora do algoritmo Quick Sort
void Ordena(int Esq, int Dir, TipoRelevancia *vetor);//Função auxiliadora do algoritmo Quick Sort
void quick_sort(TipoRelevancia *vetor, int n);//Algoritmo de ordenação Quick Sort para o vetor de relevâncias
#endif
