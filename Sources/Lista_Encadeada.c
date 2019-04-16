#include <string.h>
#include "../Headers/Lista_Encadeada.h"


//Inicalizacao//
void Inicia_Lista(TLista* pLista){  //Prepara lista para inserções.//
  pLista->pPrimeiro = (struct Celula*) malloc(sizeof(TCelula)); //Celula cabeça
  pLista->pUltimo = pLista->pPrimeiro;
  pLista->pPrimeiro->pProx= NULL;}


int Lista_Vazia(TLista* pLista){
  return(pLista->pPrimeiro == pLista->pUltimo);} //Retorna 1 para caso a lista esteja vazia e 0 caso não.//


int Insere_Lista(TLista* pLista, int Doc, int qt){             //Se inserido com sucesso retorna 1, se nao foi inserido por falta de memoria de malloc retorna 0.//
  TCelula *pAux,*pNovo;
  pNovo=(TCelula*)malloc(sizeof(TCelula));
  if(pNovo == NULL){return 0;}
  pNovo->idDoc = Doc;
  pNovo->qtde = qt;
  pNovo->pProx = NULL;
  pAux=pLista->pPrimeiro;
  while(pAux->pProx != NULL){
    pAux = pAux->pProx;}
  pAux->pProx = pNovo;
  if(pLista->pUltimo->pProx != NULL){
    pLista->pUltimo = pLista->pUltimo->pProx;
    pLista->pUltimo->pProx = NULL;}
  return 1;}

int Procura_Lista(TLista* pLista,TCelula* pAux_Celula,int Doc){  //A função devolve o endereço da celula (atravez do parametro TCelula*) que apresenta o idDoc correspondente na lista encadeada, logo salve uma variavel do tipo TCelula e passe o endereço para salvar uma copia da celula com idDoc por fora da função.
  TCelula* Aux;                                                 //Função retorna 1 caso celula com idDoc correspondente seja encontrada e 0 caso nao seja.//
  Aux= pLista->pPrimeiro->pProx;                                 //Nao sei se ira ser necessario esta funcao porem deixei criado msm assim.
  while(Aux != NULL && Aux->idDoc != Doc){
    Aux=Aux->pProx;}
  if(Aux != NULL){
    *pAux_Celula = *Aux;
    return 1;}
    else{return 0;}
    }

int Incrementa_qtde(TLista* pLista,int Doc){  //Passe por parametro lista encadeada em questao e numero identificador do documento.//
    TCelula* Aux;                             //Essa função tem como finalidade incrementar o contador "qtde" caso uma palavra ja inserida na arvore patricia seja inserida novamente de algum texto q ja se encontre com uma celula na lista encadeada.//
    Aux= pLista->pPrimeiro->pProx;
    while(Aux != NULL && Aux->idDoc != Doc){
      Aux=Aux->pProx;}
    if(Aux != NULL){
      Aux->qtde++;
      return 1;
    }
    else{
      return 0;
    }
  }




void Imprime_Lista(TLista* pLista){  //Função criada para teste.//
    TCelula* pAux;
    pAux = pLista->pPrimeiro->pProx;
    while(pAux != NULL){
      printf("\n\t\t-------Inicio da Celula-------\n");
      printf("\t\t->idDoc: %d\n",pAux->idDoc);
      printf("\t\t->Qtde: %d\n",pAux->qtde);
      printf("\t\t---------Fim da Celula--------\n\n");
      pAux=pAux->pProx;
    }
}
