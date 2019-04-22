/*
   Josué Nunes Campos - 3465
   Mateus Coelho Santos - 3488
   Samuel Pedro Campos Sena - 3494
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "LEITURA.h"//Incluíndo o cabeçalho do TAD

void FFVazia(TipoFila *Fila){//Faz uma fila vazia
  Fila->Frente = (TipoFilPoint) malloc(sizeof(TipoCelulaFila));//Criando a célula cabeça da fila
  Fila->Tras = Fila->Frente;//Indicando o começo e o final da fila
  Fila->Frente->Prox = NULL;//Apontador da célula cabeça aponta para NULL
}

int Vazia(TipoFila Fila){//Verifica se a fila é vazia
  return (Fila.Frente == Fila.Tras);//Retorna 1 se for vazia e 0 se não for
}

void Enfileira(TipoFila *Fila, char Caract){//Adiciona um novo caracter à fila
  Fila->Tras->Prox = (TipoFilPoint) malloc(sizeof(TipoCelulaFila));//Criando uma nova célula
  Fila->Tras = Fila->Tras->Prox;//Indicando o final da fila
  Fila->Tras->letra = Caract;//Guardando a letra de uma palavra
  Fila->Tras->Prox = NULL;//Apontador da nova célula criada aponta para NULL
}

void Desenfileira(TipoFila *Fila, TipoChave Item){//Remove um caracter da fila
  TipoFilPoint q;//Ponteiro que receberá a célula a ser desenfileirada
  if (Vazia(*Fila)) {//Se a fila for vazia, não há célula para ser removida
    printf("Erro fila esta vazia\n");//Mensagem de erro
	  return;//Término da função
  }//Se a fila não for vazia:
  q = Fila->Frente;//Recebendo a célula a ser desenfileirada
  Fila->Frente = Fila->Frente->Prox;//Apontando para a próxima célula da fila
  *Item = Fila->Frente->letra;//Guardando o item removido
  free(q);//Apagando a célula removida da memória
}

int ContaCelula(TipoFila Fila){//Conta quantos caracteres tem uma palavra
  TipoFilPoint Aux;//Ponteiro auxiliar para percorrer a fila
  int cont = 0;//Contador usado para contar a quantidade de células da fila
  Aux = Fila.Frente->Prox;//Recebendo a primeira célula após a célula cabeça
  while (Aux != NULL) {//Condição de parada: Chegar ao final da fila
	  cont++;//Incrementando 1 no contador (Contou uma célula)
    Aux = Aux->Prox;//Avançando o ponteiro auxiliar
  }
  return cont;//Retornando a quantidade de células, ou seja, o tamanho da palavra a ser inserida
}

TipoQtdeTermos* Leitura(TipoArvore *t, TipoApontador *RaizTST, int *N){//Realiza a leitura dos arquivos retornando quantos elementos distintos possuem cada arquivo
  FILE *Arquivo = NULL;//Apontador para acessar os arquivos
	char caracter, caracter2;//Variáveis que receberão os caracteres das palavras
	TipoChave string;//Vetor de caracteres que receberá uma palavra do arquivo
	char NomeArq[13];//Vetor de carateres para guardar o nome do arquivo digitado
	TipoFila Fila;//Fila de caracteres que formarão uma palavra
  TipoQtdeTermos *NiAux = NULL;//Vetor que será retornado contendo o número de termos distintos de cada documento (arquivo)
	int i, j=0, TAMFila, idDoc, Verificador,Verificador2;//Váriaveis para funcionamento do procedimento
	FFVazia(&Fila);//Cria uma fila vazia
  do{//Começo da estrutura de repetição
    Verificador = 2;//Variável de controle usada para indicar o fim da leitura
    Verificador2 = 0;//Variável de controle usada para indicar se o nome do arquivo está escrito da forma correta
    while(Verificador2 == 0){//Condição de parada: Nome do arquivo escrito da forma correta
    	printf("\n\tEntre com o nome do arquivo da seguinte forma -> 'arquivo(N).txt': Em que (N > 0)!\n\n");
      printf("Entrada: ");
    	scanf("%s",NomeArq);//Recebe o nome do arquivo
      Arquivo = fopen(NomeArq, "r");//Realiza a abertura do arquivo em modo de leitura
      if(Arquivo == NULL){//Se a abertura do arquivo teve algum problema:
        printf("\n\tErro!Nao foi possivel abrir arquivo!\n");//Exibe a mensagem de erro
      }
      else{//Se a abertura do arquivo teve sucesso:
        Verificador2 = 1;//Variável de controle recebe 1 para sair do while
      }
    }//Fim do while
    (*N)++;//Incrementa 1 indicando que há um arquivo lido
    NiAux = (TipoQtdeTermos *)realloc(NiAux, (*N)*sizeof(TipoQtdeTermos));//Cria uma nova posição no vetor de elementos distintos
  	idDoc = ((int)NomeArq[7]) - 48;//Recebe o ID do documento que será lido    ------------------------------------******
    NiAux[j].iDdOc = idDoc;//Guarda no vetor de elementos distintos o ID desse documento
    NiAux[j].nTermsDist = 0;//Inicializa o número de termos distintos como 0 já que não há nenhuma palavra lida ainda
  	while(!feof(Arquivo)){//Condição de parada: Chegar ao fim do arquivo
  		fscanf(Arquivo,"%c", &caracter);//Realiza a leitura de um caracter do arquivo
  		while((caracter >= 65 && caracter <= 90) || (caracter >= 97 && caracter <= 122)){//Condição de parada: O caracter lido ser diferente de uma letra
  			Enfileira(&Fila,caracter);//Enfileira a letra na fila
  			fscanf(Arquivo,"%c", &caracter);//Lê o próximo caracter do arquivo
  		}//Fim do while
  		if(!Vazia(Fila)){//Se a fila de letras não for vazia
  			TAMFila = ContaCelula(Fila);//Recebe a quantidade de letras na fila, ou seja, o tamanho da palavra a ser inserida
        if(TAMFila > 2){ //Se o tamanho da palavra for maior que 2, ou seja, não é uma preposição ou interjeição:
          string = (TipoChave)malloc((TAMFila+1)*sizeof(char));//Cria o vetor de caracteres com o tamanho mais 1 (devido ao '\0') dessa fila
    			for(i=0; i<TAMFila; i++){//Repetição até a fila ficar vazia
    				Desenfileira(&Fila,&caracter2);//Desenfileira uma letra
            caracter2 = tolower(caracter2);//Converte essa letra para minúsculo
    				string[i] = caracter2;//Armazena essa letra no vetor de caracteres que será passado para a inserção na árvore
    			}//Fim do for
    			string[TAMFila] = '\0';//Marca o final da palavra
          NiAux[j].nTermsDist++;//Incrementa 1 no número de termos distintos do documento
          (*t) = Insere(string, &(*t), idDoc, &(NiAux[j]));//Insere a palavra recebida na árvore PATRICIA
          Insercao(&(*RaizTST), string);//Insere a palavra recebida na árvore TST
          free(string);//Apaga o conteúdo desse vetor, deixando-o disponível para a próxima palavra
        }
        else{//Se as letras que foram lidas são preposições ou interjeições:
          for(i=0; i<TAMFila; i++){//Repetição até a fila ficar vazia
    				Desenfileira(&Fila,&caracter2);//Desenfileira uma letra
    			}//Fim do for
        }
  		}
  	}
  	fclose(Arquivo);//Término da leitura, fechamento do arquivo
    while(Verificador != 1 && Verificador != 0){//Condição de parada: A opção digitada for alguma das disponíveis
      printf("\nDeseja adicionar textos de outro arquivo?\n\tSim - 1\n\tNao - 0\nEntre com a opcao desejada: ");
      scanf("%d", &Verificador);//Recebe a opção escolhida
      if(Verificador != 1 && Verificador != 0){//Se a opção digitada não satisfaz as disponíveis:
        printf("\nErro! Opcao invalida!\n");//Mensagem de erro
      }
    }//Fim do while
    j++;
  }while(Verificador != 0);//Condição de parada: Variável de controle ser igual a 0 (indicando que não há mais arquivos a serem inseridos)
  return NiAux;//Retorna o vetor com o número de elementos distintos em cada documento lido
}

void Busca(TipoArvore t, int N, TipoQtdeTermos *Ni, TipoApontador RaizTST){//Realiza a busca de palavras e exibe os documentos mais relevantes
  TipoArvore Aux;//Apontador auxiliar para receber um nó folha da árvore
  TipoList listaPeso;//Lista que conterá todos os pesos da(s) palavra(s) referentes à todo(s) arquivo(s) com a(s) palavra(s)
  TipoRelevancia *VetorRlva;//Vetor que conterá as relevâncias de cada documento que contém a(s) palavra(s) buscada(s)
  int d, i, nI, Verificador;//Variáveis para o funcionamento do procedimento
  int *f, *id;//Vetor para guardar o número de ocorrência de uma palavra em um documento e um vetor com seu ID, respectivamente
  char *str;//Vetor de caracteres que receberá a(s) palavra(s) digitada(s)
  double peso, PesoTotal;//Variáveis para guardar o peso de uma palavra e o peso total em um documento, respectivamente
  FListVazia(&listaPeso);//Cria um lista de pesos vazia
  VetorRlva = (TipoRelevancia *)malloc(N*sizeof(TipoRelevancia));//Criação do vetor de relevâncias com o tamanho sendo a quantidade de arquivos lidos
  str = (char *)malloc(47*sizeof(char));
  do{//Começo doWhile
    strcpy(str,AutoCompletar(RaizTST));//Recebendo a palavra escolhida
    Aux = PesquisaNO(str, t);//Realiza a pesquisa na árvore verificando se existe um nó folha com essa palavra
    if(Aux == NULL){//Caso o valor retornado pela função seja NULL, significa que não há essa palavra na árvore
      printf("Essa palavra nao existe em nenhum documento!\n");//Mensagem de erro
      free(str);//Apaga o conteúdo desse vetor, deixando-o disponível para a próxima palavra
    }
    else{//Caso o valor retornado pela função seja diferente de NULL, significa que há essa palavra na árvore
      printf("\t-->Palavra computada!<--\n");//Mensagem indicando ao usuário que a palavra foi encontrada
      free(str);//Apaga o conteúdo desse vetor, deixando-o disponível para a próxima palavra
      d = ContaCelulaLista(Aux->NO.Conteudo.Lista);//Recebe a quantidade de arquivos que essa palavra aparece
      f = (int *)malloc(d*sizeof(int));//Criando o vetor que guardará em cada posição a quantidade de vezes que a palavra repete em um documento
      id = (int *)malloc(d*sizeof(int));//Criando o vetor que guardará em cada posição o ID de um documento
      RetornaQtdeEidDocs(Aux->NO.Conteudo.Lista, f, id);//Chama a função que colocará nos vetores acima os valores que foram designados para receberem
      for(i=0; i<d; i++){//Calcula o peso para cada documento existente com essa palavra
        peso = CalculaPeso(f[i], d, N);//Retorna o peso calculado
        InserePeso(&listaPeso, id[i], peso);//insere na lista de pesos o peso calculado juntamente com o ID referente ao documento
      }
      free(f);//Apaga o conteúdo desse vetor, deixando-o disponível para as quantidades da próxima palavra
      free(id);//Apaga o conteúdo desse vetor, deixando-o disponível para os IDs de documento da próxima palavra
    }
    Verificador = 3; //Garantindo a entrada no while abaixo.
    while(Verificador != 1 && Verificador != 0){//Condição de parada: A opção digitada for alguma das disponíveis
    printf("\nDeseja buscar mais palavras?\n\tSim - 1\n\tNao - 0\nEntre com a opcao desejada: ");
    scanf("%d", &Verificador);//Recebe a opção que o usuário deseja, 1 para buscar mais palavras ou 0 caso não queira
    if(Verificador != 1 && Verificador != 0){//Se a opção digitada não satisfaz as disponíveis:
      printf("\nErro! Opcao invalida!\n");//Mensagem de erro
     }
    }//Fim do while
  }while(Verificador != 0);//Condição de parada: Variável de controle ser igual a 0, ou seja, usuário não quer digitar mais palavras
  for(i=0; i<N; i++){//Já que não há mais palavras para serem buscadas, as funções referentes ao cálculo da relevância são chamadas
    PesoTotal = SomaPesos(listaPeso,  Ni[i].iDdOc);//Recebe a soma de todos os pesos do documento i
    VetorRlva[i].IDdoc = Ni[i].iDdOc;//Guarda no vetor de relevâncias o ID de cada documento já ordenado
        nI = Ni[i].nTermsDist;//Recebe o número de termos distintos nesse documento
    VetorRlva[i].Relevancia = CalculaRelevancia(PesoTotal, nI);//Recebe a relevância calculada do documento i
  }//Fim do for mais externo
  quick_sort(VetorRlva, N);//Ordena o vetor de relevâncias para exibir os documentos na ordem correta
  printf("A partir do TF-IDF, os documentos mais relevantes sao:\n");
  if(N == 1){
    printf("\t-->Apenas 1 documento inserido, logo e o unico relevante!<--\n");
  }
  else{
    for(i=0; i<N; i++){//Repetição para exibir os documentos mais relevantes a partir do cálculo do TF-IDF
      if(VetorRlva[i].Relevancia == 0.0){//Se a relevância de um documento é 0:
        break;//Significa que não há mais documentos a serem exibidos, já que o vetor está ordenado decrescentemente
      }//Se não, exibe os textos relevantes para essa busca
      printf("\t-->Texto %d: (arquivo%d.txt)<--\n", VetorRlva[i].IDdoc, VetorRlva[i].IDdoc);
    }
  }
  free(VetorRlva);//Apaga o conteúdo desse vetor, liberando espaço para outras execuções
}

void menu(TipoArvore *P, TipoApontador *Pt, int *N, TipoQtdeTermos *Ni){//Menu contendo as opções de uso do programa
	int escolha=4;//Variável de controle para a escolha de uma opção
	while(escolha != 0){//Condição de parada: Usuário desejar sair do programa
    printf("---------------- Menu ----------------\n");
    printf("| 1 - Inserir Arquivos               |\n");
    printf("| 2 - Imprimir Palavras Inseridas    |\n");
    printf("| 3 - Buscar Palavra(s)              |\n");
    printf("| 0 - Sair                           |\n");
    printf("--------------------------------------\n");
		printf("\nQual a opcao a ser executada?: ");
		scanf("%d", &escolha);//Recebendo a opção desejada
		switch(escolha){
			case 0://Opção de sair do programa
				return;//Fim do procedimento
			break;
			case 1://Opção de inserir arquivos
				Ni = Leitura(P, Pt, N);//Chamando a leitura que retornará o vetor de elementos distintos de cada documento
			break;
			case 2://Opção de imprimir as palavras e o índice invertido de cada uma
				ImprimePat(*P);//Chama o procedimento para imprimir a árvore PATRICIA
			break;
			case 3://Opção de buscar uma palavra para o cálculo da relevância de textos
				Busca(*P, *N, Ni, *Pt);//Chamando a busca de palavras
			break;
			default://Padrão que é verdadeiro caso uma escolha feita não pertença ao menu
				printf("Valor escolhido invalido, digite outro!\n");
			break;
		}//Fim switch case
	}//Fim while
	return;
}
