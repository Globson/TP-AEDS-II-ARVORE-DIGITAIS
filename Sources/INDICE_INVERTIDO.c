/*
   Josué Nunes Campos - 3465
   Mateus Coelho Santos - 3488
   Samuel Pedro Campos Sena - 3494
*/
#include <stdio.h>
#include <stdlib.h>
#include "INDICE_INVERTIDO.h"//Incluíndo o cabeçalho do TAD

void FLVazia(TipoLista *Lista){//Faz uma lista vazia
  Lista -> Primeiro = (TipoCelPoint) malloc(sizeof(TipoCelula));//Criando a célula cabeça da lista
  Lista -> Ultimo = Lista -> Primeiro;//Indicando o começo e o fim da lista
  Lista -> Primeiro -> Prox = NULL;//Apontador da célula cabeça aponta para NULL
}

void InsereIndice(TipoLista *Lista, int idDoc, int Qtde){//Insere uma célula na lista
  Lista -> Ultimo -> Prox = (TipoCelPoint) malloc(sizeof(TipoCelula));//Criando uma nova célula
  Lista -> Ultimo = Lista -> Ultimo -> Prox;//Indicando o novo final da lista
  Lista -> Ultimo -> IdDoc = idDoc;//Guardando a primeira chave (ID do documento)
  Lista -> Ultimo -> qtde = Qtde;//Guardando a segunda chave (Como é uma inserção a Qtde será igual a 1)
  Lista -> Ultimo -> Prox = NULL;//Apontador da nova célula criada aponta para NULL
}

int ProcuraIdDoc(TipoLista *Lista, int idDoc, TipoQtdeTermos *Ni){//Procura e compara se já existe o ID passado como parâmetro
  TipoCelPoint Aux;//Apontador auxiliar para percorrer a lista
  Aux = Lista -> Primeiro -> Prox;//Recebendo a primeira célula após a célula cabeça
  while (Aux != NULL && Aux->IdDoc != idDoc){//Condição de parada: Se for o final da lista ou o ID na célula ser igual ao procurado
    Aux = Aux -> Prox;//Avançando o ponteiro auxiliar
  }
  if(Aux != NULL){//Se o Apontador auxiliar apontar para uma célula, significa que o ID procurado pertence a lista
    Aux->qtde++;//Basta incrementar 1 na Quantidade de vezes que a palavra aparece nesse documento achado
    Ni->nTermsDist--;//Decrementando 1 no número de termos distintos do documento
    return 1;//Retorna 1 indicando que a procura teve sucesso
  }
  return 0;//Retorna 0 indicando que não há o ID procurado na lista, sendo necessário criar uma nova célula
}

void Imprime(TipoLista Lista){//Imprime a lista
  TipoCelPoint Aux;//Ponteiro auxiliar para percorrer a lista
  Aux = Lista.Primeiro -> Prox;//Recebendo a primeira célula após a célula cabeça
  while (Aux != NULL){//Condição de parada: Chegar ao final da lista
    printf("\n\t\t-------Inicio do indice-------\n");
    printf("\t\t->idDoc: %d\n", Aux->IdDoc);//Exibindo o ID do documento
    printf("\t\t->Qtde: %d\n", Aux->qtde);//Exibindo a quantidade de vezes que a palavra repete nesse documento
    printf("\t\t---------Fim do indice--------\n\n");
    Aux = Aux -> Prox;//Avançando o ponteiro auxiliar
  }
}

int ContaCelulaLista(TipoLista Lista){//Conta quantos documentos tem na lista
  TipoCelPoint Aux;//Ponteiro auxiliar para percorrer a lista
  int cont = 0;//Contador que terá a quantidade de células da lista
  Aux = Lista.Primeiro -> Prox;//Recebendo a primeira célula após a célula cabeça
  while (Aux != NULL) {//Condição de parada: Chegar ao final da lista
	  cont++;//Incrementando 1 no contador (Contou uma célula)
    Aux = Aux->Prox;//Avançando o ponteiro auxiliar
  }
  return cont;//Retornando a quantidade de células (de documentos) da lista
}

void RetornaQtdeEidDocs(TipoLista Lista, int *F, int *D){//Retorna as chaves de todas as células da lista
  TipoCelPoint Aux;//Ponteiro auxiliar para percorrer a lista
  int i=0;//Variável que será o índice do vetor de quantidades de vezes que a palavra repete e do vetor de IDs dessa lista
  Aux = Lista.Primeiro -> Prox;//Recebendo a primeira célula após a célula cabeça
  while (Aux != NULL) {//Condição de parada: Chegar ao final da lista
    F[i] = Aux->qtde;//Atribuíndo a posição i do vetor a quantidade de vezes que a palavra repete em um documento
    D[i] = Aux->IdDoc;//Atribuíndo a posição i do vetor o ID do documento que contém a palavra
    i++;//Incrementando 1 para avançar as posições dos vetores
    Aux = Aux->Prox;//Avançando o ponteiro auxiliar
  }
}
