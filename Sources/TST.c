/*
   Josué Nunes Campos - 3465
   Mateus Coelho Santos - 3488
   Samuel Pedro Campos Sena - 3494
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/TST.h"//Incluíndo o Cabeçalho do TAD

void Inicializa(TipoApontador *Raiz){//Inicializa o ponteiro da árvore
  *Raiz = NULL;//Faz o ponteiro receber NULL
}

void Insercao(TipoApontador *Raiz, char *Palavra){//Função para inserir uma nova palavra na TST
    //Caso base: A árvore é vazia ou atingiu um apontador nulo
    if (*Raiz == NULL){
      *Raiz = (TipoApontador)malloc(sizeof(TipoNoTST));//Cria um espaço na memória para guardar esse novo nó
      (*Raiz)->Chave = *Palavra;//Guarda uma letra da palavra
      (*Raiz)->FimDeString = 0;//Indica que não é o fim da palavra ainda
      (*Raiz)->Esq = (*Raiz)->Meio = (*Raiz)->Dir = NULL;//Apontadores Esquerda, Direita e Meio do nó recebem NULL
    }
    /*Se a letra atual da palavra é menor que a letra da raiz,
      então insere esta palavra na esquerda da raiz*/
    if ((*Palavra) < (*Raiz)->Chave){
        Insercao(&((*Raiz)->Esq), Palavra);//Chama a inserção para o nó à esquerda
    }
    /*Se a letra atual da palavra é maior que a letra da raiz,
      então insere esta palavra na direita da raiz*/
    else if ((*Palavra) > (*Raiz)->Chave){
        Insercao(&((*Raiz)->Dir), Palavra);//Chama a inserção para o nó à direita
    }
    //Se a letra atual da palavra é a mesma da raiz, ou seja, a letra já está na árvore:
    else{
        if (*(Palavra+1) != '\0'){//Analisa se a letra atual não é a última da palavra
            Insercao(&((*Raiz)->Meio), Palavra+1);//Chama a inserção para a próxima letra
        }
        else{//Se a letra atual é a última da palavra:
            (*Raiz)->FimDeString = 1;//Marca como fim da palavra
        }
    }
}

void FLTSTVazia(TipoListaTST *lista){//Faz uma lista vazia
  lista->pri = (TipoApont) malloc(sizeof(TipoCelList));//Criação da célula cabeça da lista
  lista->ult = lista->pri;//Indicando o começo e o final da lista
  lista->pri->Proximo = NULL;//Ponteiro para a próxima célula (que não tem) recebe NULL
}

int VaziaLTST(TipoListaTST lista){//Verifica se a lista é vazia
  return (lista.pri == lista.ult);//Retorna 1 se a lista é vazia ou 0 se não for
}

void InserePalavra(char *x, TipoListaTST *lista, int *Contador){//Insere uma palavra com o prefixo buscado
  (*Contador)++;//Incrementando 1 no ID da palavra com o prefixo, para não haver IDs idênticos
  lista->ult->Proximo = (TipoApont) malloc(sizeof(TipoCelList));//Criando um espaço na memória para a nova célula
  lista->ult = lista->ult->Proximo;//Indicando o final da lista
  lista->ult->Item.numPalavra = *Contador;//Recebendo o ID da palavra
  strcpy(lista->ult->Item.Chave, x);//Recebendo a palavra com o prefixo buscado
  lista->ult->Proximo = NULL;//Ponteiro para a próxima célula (que não tem) recebe NULL
}

void ImprimeLTST(TipoListaTST lista){//Imprime as palavras com o prefixo buscado
  TipoApont Aux;//Apontador auxiliar para percorrer a lista
  Aux = lista.pri->Proximo;//Recebendo a primeira célula não vazia da lista
  while (Aux != NULL) {//Condição de parada: Chegar ao final da lista
    printf("%d -> %s\n", Aux->Item.numPalavra, Aux->Item.Chave);
    Aux = Aux->Proximo;//Avançando com o ponteiro auxiliar
  }
}

char *PesquisaLTST(TipoListaTST lista, int id){//Retorna a palavra que fora escolhida para a pesquisa
  TipoApont Aux;//Apontador auxiliar para percorrer a lista
  Aux = lista.pri->Proximo;//Recebendo a primeira célula não vazia da lista
  while (Aux != NULL) {//Condição de parada: Chegar ao final da lista ou achar a palavra escolhida
    if(id == Aux->Item.numPalavra){//Se o ID buscado for achado:
      return Aux->Item.Chave;//Retorna a palavra referente à esse ID
    }
    Aux = Aux->Proximo;//Avançando com o ponteiro auxiliar
  }
  return "00";//Retorna "00" se o ID buscado não for achado
}

void Sufixo_Filhos(TipoApontador Raiz, char *Cache, char *Prefixo_salvo, int Nivel,int *Verificador, TipoListaTST *lista, int *idPalavra){ //Funcao forma os sufixos dos filhos daquele prefixo e concatena com prefixo constante.//
    if(Raiz != NULL){ //Verifica se a arvore existe
        Sufixo_Filhos(Raiz->Esq, Cache, Prefixo_salvo, Nivel, Verificador, lista, idPalavra); //Chama recursivamente primeiro o nó a esquerda para manter ordem.//
        Cache[Nivel] = Raiz->Chave; //Formacao de sufixo, caractere a caractere.//
        if(Raiz->FimDeString == 1){//Caso chegue no fim de uma string.
            char *PalavraTemp;//Criação de um vetor de caracteres temporário apenas para a palavra ser guardada na lista
            PalavraTemp = (char *)malloc(47*sizeof(char));//Alocando um espaço na memória para esse vetor
            Cache[Nivel+1] = '\0'; // Atribui "\0" para indicar fim de string em variavel char*.//
            strcpy(PalavraTemp,Prefixo_salvo);//Copiando o prefixo digitado para o vetor temporário
            strcat(PalavraTemp,Cache);//Concatenando o prefixo e o resto da palavra achada
            InserePalavra(PalavraTemp,lista,idPalavra);//Insere essa nova palavra com o prefixo buscado
            *Verificador = 1;//Indicador que há uma palavra com esse prefixo
            free(PalavraTemp);//Apagando o conteúdo do vetor de caracteres temporário
        }
        Sufixo_Filhos(Raiz->Meio, Cache, Prefixo_salvo, Nivel+1, Verificador, lista, idPalavra);//Chama recursivamente em seguida o nó no meio para manter ordem.//
        Sufixo_Filhos(Raiz->Dir, Cache, Prefixo_salvo, Nivel, Verificador, lista, idPalavra); //Chama recursivamente em seguida nó a direita para manter ordem.//
      }
}

void Busca_Filhos(TipoApontador Raiz, char *Prefixo_salvo, int *Verificador, TipoListaTST *lista, int *idPalavra){ //Funcao para encontrar filhos de no de chave igual ao ultimo caractere do prefixo entrado pelo usuario.//
    char Cache[47]; //Variavel criada para auxiliar formacao de sufixos.//
    Sufixo_Filhos(Raiz, Cache, Prefixo_salvo, 0, Verificador, lista, idPalavra); //Chama funcao para formar os sufixos dos filhos daquele prefixo.//
}

int Pesquisa_Prefixo(TipoApontador Raiz, char *Prefixo_Atual, char *Prefixo_salvo , int *Verificador, TipoListaTST *lista, int *idPalavra){ //Navega pela TST ate encontrar no de chave igual ao ultimo caractere do prefixo entrado pelo usuario.//
    if (Raiz == NULL){ //Verifica se a arvore existe
        return 0;
    }
    if (*Prefixo_Atual < Raiz->Chave){ //Algoritmo realiza uma busca parcial entre os nos da arvore TST ate chegar no fim do prefixo entrado.
        return Pesquisa_Prefixo(Raiz->Esq, Prefixo_Atual, Prefixo_salvo, Verificador, lista, idPalavra);
      }
    else if (*Prefixo_Atual > (Raiz)->Chave){
        return Pesquisa_Prefixo(Raiz->Dir, Prefixo_Atual, Prefixo_salvo , Verificador, lista, idPalavra);
      }
    else{
        if (*(Prefixo_Atual+1) == '\0'){  //Ao encontrar ultimo digito do prefixo, chama a função Busca_Filhos para encontrar todos os filhos do prefixo entrado.
            Busca_Filhos(Raiz->Meio, Prefixo_salvo, Verificador, lista, idPalavra);
        }
        return Pesquisa_Prefixo(Raiz->Meio, (Prefixo_Atual+1), Prefixo_salvo, Verificador, lista, idPalavra); //Causo o proximo caractere do prefixo nao seja "\0" e o caractere seja igual ao do no atual, devemos avançar ao proximo no situado no meio.
    }
}

char *AutoCompletar(TipoApontador Raiz){  //Função criada para encapsular scanf() e passar parametro correto para função pesquisa prefixo, alem de gerenciar pesquisa de palavras em relevancia.//
  //Funções criadas a partir da Função TransverseTST hospedada em : ( https://www.geeksforgeeks.org/ternary-search-tree/ ) .//
  char *Prefixo_APesquisar;//Vetor de caracteres que receberá o prefixo digitado
  int Verifica = 0, idPalavra = 0;//Variáveis para funcionamento do procedimento
  TipoListaTST lista;//Fila de palavras com o prefixo digitado
  FLTSTVazia(&lista);//Criação de uma lista de palavras vazia
  Prefixo_APesquisar = (char *)malloc(47*sizeof(char));//Criação do vetor de caracteres que receberá o prefixo
  while(Verifica == 0){//Condição de parada: Achar alguma palavra com o prefixo digitado
    printf("\nEntre com o prefixo a ser pesquisado na arvore: ");
    scanf("%s",Prefixo_APesquisar);//Recebendo o prefixo que será pesquisado
    Pesquisa_Prefixo(Raiz,Prefixo_APesquisar,Prefixo_APesquisar,&Verifica, &lista, &idPalavra); //Atenção! nao mudar forma de passar parametros! parametros passados duplicadamente propositalmente!//
    if(Verifica == 0){//Se o verificador retornado é 0, significa que não foi encontrado nenhuma palavra com o prefixo digitado ou a palavra toda já fora digitada
      printf("\n--->Nenhuma palavra encontrada com esse prefixo ou palavra ja completa!<---\n");
    }
    else{//Se o verificador retornado é 1, significa que palavra(s) foram encontradas com o prefixo digitado
      while(Verifica == 1){//Condição de parada: Escolher uma palavra que esteja disponível
        printf("Qual palavra deseja escolher?\n");
        ImprimeLTST(lista);//Imprime as opções disponíveis
        printf("Entre com o numero correspondente a palavra:");
        scanf("%d", &idPalavra);//Recebendo o ID de escolha
        strcpy(Prefixo_APesquisar,PesquisaLTST(lista, idPalavra));//Pesquisando o ID e retornando o resultado da pesquisa para a variável
        if(strcmp(Prefixo_APesquisar,"00")==0){//Caso o ID digitado não esteja dentre as opções:
          printf("Opcao invalida!\n");//Mensagem de erro
        }//Repete até haver uma escolha válida
        else{//Caso a escolha seja válida:
          Verifica = 0;//Atinge a condição de parada
        }
      }//Fim do while
      return Prefixo_APesquisar;//Retorna a palavra escolhida para pesquisa
    }
  }//Fim do while
}
