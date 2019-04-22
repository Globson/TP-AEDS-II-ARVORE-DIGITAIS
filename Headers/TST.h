/*
   Josué Nunes Campos - 3465
   Mateus Coelho Santos - 3488
   Samuel Pedro Campos Sena - 3494
*/
#ifndef TST_H_INCLUDED
#define TST_H_INCLUDED

typedef struct TipoNoTST* TipoApontador;//Renomeando o ponteiro para struct TipoNoTST

typedef struct TipoNoTST{//Nó da árvore TST
    char Chave;//Caracter de uma palavra
    unsigned FimDeString: 1;//Verdadeiro se o caracter é o último caracter das palavras
    TipoApontador Esq, Meio, Dir;//Apontadores para a Esquerda, Direita e Meio
}TipoNoTST;

typedef struct TipoCelList *TipoApont;//Renomeando o ponteiro para struct TipoCelList

typedef struct TipoPalavrasTST {//Dados da lista de palavras com prefixo buscado
  char Chave[47];//Palavra que terá o prefixo buscado
  int numPalavra;//ID da palavra, como se fosse o índice de uma posição em um vetor
} TipoPalavrasTST;

typedef struct TipoCelList {//Célula da lista
  TipoPalavrasTST Item;//Conteúdo da célula, com o a palavra e seu ID
  TipoApont Proximo;//Apontador para a próxima célula
} TipoCelList;

typedef struct TipoListaTST {//Struct contendo os apontadores para o começo da lista e para o final da lista
  TipoApont pri, ult;//Ponteiros para o começo e fim da lista, respectivamente
} TipoListaTST;

//Cabeçalhos das funções que manipula a árvore TST
void Inicializa(TipoApontador *Raiz);//Inicializa o ponteiro da árvore
void Insercao(TipoApontador *Raiz, char *Palavra);//Insere uma nova palavra na árvore
void FLTSTVazia(TipoListaTST *lista);//Faz uma lista vazia
int VaziaLTST(TipoListaTST lista);//Verifica se a lista é vazia
void InserePalavra(char *x, TipoListaTST *lista, int *Contador);//Insere uma palavra com o prefixo buscado
void ImprimeLTST(TipoListaTST lista);//Imprime as palavras com o prefixo buscado
char *PesquisaLTST(TipoListaTST lista, int id);//Retorna a palavra que fora escolhida para a pesquisa
void Sufixo_Filhos(TipoApontador Raiz, char *Cache, char *Prefixo_salvo, int Nivel,int *Verificador, TipoListaTST *lista, int *idPalavra);//Funcao forma os sufixos dos filhos daquele prefixo e concatena com prefixo constante.//
void Busca_Filhos(TipoApontador Raiz, char *Prefixo_salvo, int *Verificador, TipoListaTST *lista, int *idPalavra); //Funcao para encontrar filhos de no de chave igual ao ultimo caractere do prefixo entrado pelo usuario.//
int Pesquisa_Prefixo(TipoApontador Raiz, char *Prefixo_Atual, char *Prefixo_salvo , int *Verificador, TipoListaTST *lista, int *idPalavra);//Navega pela TST ate encontrar no de chave igual ao ultimo caractere do prefixo entrado pelo usuario.//
char *AutoCompletar(TipoApontador Raiz);//Função criada para encapsular scanf() e passar parametro correto para função pesquisa prefixo, alem de gerenciar pesquisa de palavras em relevancia.//
#endif
