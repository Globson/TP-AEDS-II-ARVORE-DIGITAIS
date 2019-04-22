/*
   Josué Nunes Campos - 3465
   Mateus Coelho Santos - 3488
   Samuel Pedro Campos Sena - 3494
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../Headers/TF_IDF.h"//Incluíndo o cabeçalho do TAD

void InicializaNdoc(int *N){//Inicializando o número de documentos na coleção
  *N = 0;//Inicializando o número de documentos
}

void FListVazia(TipoList *Lista){//Faz uma lista vazia
  Lista -> primeiro = (TipoPoint) malloc(sizeof(TipoCel));//Criando a célula cabeça da lista
  Lista -> ultimo = Lista -> primeiro;//Indicando o começo e o fim da lista
  Lista -> primeiro -> prox = NULL;//Apontador da célula cabeça aponta para NULL
}

void InserePeso(TipoList *Lista, int idDoc, double peso){//Insere na lista o peso de uma palavra em um documento
  Lista -> ultimo -> prox = (TipoPoint) malloc(sizeof(TipoCel));//Criando uma nova célula
  Lista -> ultimo = Lista -> ultimo -> prox;//Indicando o final da lista
  Lista -> ultimo -> iddoc = idDoc;//Guardando o ID do documento
  Lista -> ultimo -> Peso = peso;//Guardando o peso da palavra referente à esse documento
  Lista -> ultimo -> prox = NULL;//Apontador da nova célula criada aponta para NULL
}

double SomaPesos(TipoList Lista, int idDoc){//Soma todos os pesos referentes à um documento
  TipoPoint Aux;//Apontador auxiliar para percorrer a lista
  double cont = 0.0;//Contador para somar os pesos de um documento
  Aux = Lista.primeiro -> prox;//Recebendo a primeira célula após a célula cabeça
  while (Aux != NULL) {//Condição de parada: Chegar ao final da lista
    if(Aux->iddoc == idDoc){//Se o ID da célula for igual ao procurado:
      cont += Aux->Peso;//Soma o peso de uma palavra referente à esse documento
    }
    Aux = Aux->prox;//Avançando o ponteiro auxiliar
  }
  return cont;//Retornando a soma dos pesos referente ao documento procurado
}

double CalculaPeso(int numOc, int numDocCterm, int numDocTot){//Calcula o peso de uma palavra em um documento
  double w;//Váriavel contendo o peso calculado
  double a = (log10(numDocTot))/(log10(2));//Realizando a mudança de base do logaritmo da fórmula (da base 10 para base 2)
  w = (numOc) * ((a)/(numDocCterm));//Realizando o cálculo através da fórmula
  return w;//Retornando o peso calculado
}

double CalculaRelevancia(double pesoTotal, int nI){//Calcula a relevância de um documento
  return (pesoTotal/nI);//Retornando a relevância de um documento calculada
}

void Particao(int Esq, int Dir, int *i, int *j, TipoRelevancia *vetor){//Função auxiliadora do algoritmo Quick Sort
  TipoRelevancia pivo, aux;//Variável que guarda o pivô da partição e variável auxiliar para a troca
  *i = Esq;//Apontador que é deslocado da esquerda para a direita da partição
  *j = Dir;//Apontador que é deslocado da direita para a esquerda da partição
  pivo = vetor[(*i + *j)/2];//Guardando o pivô da partição
  do{
    while(pivo.Relevancia < vetor[*i].Relevancia){//Deslocando o apontador da esquerda para a direita até achar um elemento menor que o pivô
      (*i)++;//Incrementando 1 para deslocar
    }
    while(pivo.Relevancia > vetor[*j].Relevancia){//Deslocando o apontador da direita para a esquerda até achar um elemento maior que o pivô
      (*j)--;//Decrementando 1 para deslocar
    }
    if(*i <= *j){//Caso haja elementos nas partições em que não deveriam estar, realiza a troca desses elementos
      aux = vetor[*i];//Auxiliar recebe o primeiro elemento
      vetor[*i] = vetor[*j];//O segundo elemento é passado para a posição do primeiro
      vetor[*j] = aux;//O primeiro elemento é passado para a posição do segundo
      (*i)++;//Avança com o ponteiro para a direita
      (*j)--;//Avança com o ponteiro para a esquerda
    }
  }while(*i <= *j);//Condição de parada: Os dois apontadores se cruzarem
}

void Ordena(int Esq, int Dir, TipoRelevancia *vetor){//Função auxiliadora do algoritmo Quick Sort
  int i, j;//Váriaveis que serão usadas como apontadores
  Particao(Esq, Dir, &i, &j, vetor);//Chamando a função que arruma as partições
  if(Esq < j){//Caso o apontador da direita não tenha chegado ao começo do vetor:
    Ordena(Esq, j, vetor);//Repete o procedimento para a partição à esquerda
  }
  if(i < Dir){//Caso o apontador da esquerda não tenha chegado ao final do vetor:
    Ordena(i, Dir, vetor);//Repete o procedimento para a partição à direita
  }
}

void quick_sort(TipoRelevancia *vetor, int n){//Algoritmo de ordenação Quick Sort para o vetor de relevâncias
  Ordena(0, n-1, vetor);//Chamando o procedimento que ordenará o vetor, de fato
}
