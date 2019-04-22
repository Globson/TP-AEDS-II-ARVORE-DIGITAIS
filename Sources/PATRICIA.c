/*
   Josué Nunes Campos - 3465
   Mateus Coelho Santos - 3488
   Samuel Pedro Campos Sena - 3494
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PATRICIA.h"//Incluíndo o cabeçalho do TAD

void InicializaPat(TipoArvore *t){//Inicializa o ponteiro da árvore
  *t = NULL;//Faz o ponteiro receber NULL
}

int CalculaIndice(TipoChave k, TipoChave Palavra, int N){//Retorna qual índice que difere entre duas palavras
  int i;//Variável que será retornada
  for(i=0; i<N; i++){//Repete até achar as letras que diferem de uma palavra para outra
    if(Palavra[i] != k[i]){//Se as letras são diferentes:
      return i;//Retorna a posição que difere
    }
  }//Caso nenhuma letra seja diferente, as palavras são iguais
  return i;//Retorna essa posição
}

int ComparaChaves(TipoChave k, TipoChave Palavra, int TAM1, int TAM2){//Encapsula a função acima de acordo com os tamanhos das duas palavras
  if(TAM2 < TAM1){//Se o tamanho da palavra que será inserida é maior do que a da chave:
    return CalculaIndice(k, Palavra, TAM2);//Calcula o índice até a última letra da palavra que será inserida
  }
  else if(TAM1 < TAM2){//Se o tamanho da palavra que será inserida é menor do que a da chave:
    return CalculaIndice(k, Palavra, TAM1);//Calcula o índice até a última letra da chave
  }
  return CalculaIndice(k, Palavra, TAM1);//Se não, as palavras possuem mesmo tamanho, logo, o tamanho da chave foi definido para ser passado
}

int ComparaLetra(int i, char Letra, TipoChave Palavra){//Retorna 0 se a letra da palavra a ser inserida é menor ou igual a da chave no nó folha ou 1 se for maior
  if(Palavra[i] <= Letra){//Se a letra da palavra que será inserida é menor ou igual a da chave:
    return 0;//Retorna 0
  }//Se a letra da palavra que será inserida é maior do que a da chave:
  return 1;//Retorna 1
}

int EExterno(TipoArvore p){//Verifica se o nó passado como parâmetro é externo, retornando 1 se for ou 0 se não for
  return (p->TipoDoNo == Externo);//Retorna 1 se o tipo do nó é externo ou 0 se o tipo do nó for interno
}

TipoArvore CriaNoInt(int i, TipoArvore *Esq, TipoArvore *Dir, char letra){//Realiza a criação de um nó interno
  TipoArvore p;//Apontador auxiliar que será retornado com o nó interno criado
  p = (TipoArvore)malloc(sizeof(TipoPatNo));//Criação de um espaço na memória que conterá o nó interno
  p->TipoDoNo = Interno;//Atribui ao tipo do nó a enumeração "Interno"
  p->NO.NInterno.Esq = *Esq;//Apontador da esquerda recebe o endereço que foi passado como parâmetro
  p->NO.NInterno.Dir = *Dir;//Apontador da direita recebe o endereço que foi passado como parâmetro
  p->NO.NInterno.Index = i;//Atribui o índice ao qual as letras das palavras se diferem
  p->NO.NInterno.LetraComp = letra;//Atribui a menor letra que difere entre as palavras
  return p;//Retorna o ponteiro com o nó interno criado
}

TipoArvore CriaNoExt(TipoChave Palavra, int idDoc){//Realiza a criação de um nó externo
  TipoArvore p;//Apontador auxiliar que será retornado com o nó externo criado
  p = (TipoArvore)malloc(sizeof(TipoPatNo));//Criação de um espaço na memória que conterá o nó externo
  p->TipoDoNo = Externo;//Atribui ao tipo do nó a enumeração "Externo"
  p->NO.Conteudo.Chave = (TipoChave)malloc(strlen(Palavra)*sizeof(char));//Criação do vetor de caracteres que conterá a palavra a ser inserida
  FLVazia(&(p->NO.Conteudo.Lista));//Criando a lista de índice invertido para essa nova chave
  strcpy(p->NO.Conteudo.Chave, Palavra);//Copia para o espaço alocado criado destinado ao vetor de caracteres a palavra que será inserida
  InsereIndice(&(p->NO.Conteudo.Lista), idDoc, 1);//Insere na lista criada o ID do documento ao qual essa palavra pertence
  return p;//Retorna o ponteiro com nó externo criado
}

TipoArvore PesquisaNO(TipoChave Palavra,TipoArvore t){//Pesquisa uma dada chave na árvore, retornando o endereço de seu Nó se encontrar ou NULL se não encontrar
  if(EExterno(t)){//Verifica se o nó é externo
    if(strcmp(Palavra, t->NO.Conteudo.Chave) == 0){//Caso seja, verifica se a chave desse nó é igual à palavra procurada
     return t;//Caso seja, retorna o endereço desse nó
    }
    else{//Caso as palavras forem diferentes:
      return NULL;//Retorna NULL
    }
  }
  if(ComparaLetra(t->NO.NInterno.Index, t->NO.NInterno.LetraComp, Palavra) == 0){//Caso a letra da palavra na posição do índice do nó interno seja 0:
    return PesquisaNO(Palavra, t->NO.NInterno.Esq);//Avança para a esquerda, significando que a letra da palavra é menor ou igual à letra do nó interno
  }
  else{//Caso a letra da palavra na posição do índice do nó interno seja 1:
    return PesquisaNO(Palavra, t->NO.NInterno.Dir);//Avança para a direita, significando que a letra da palavra é maior do que a letra do nó interno
  }
}

char AchaLetra(TipoArvore *p, int i, TipoChave Palavra){//Retorna a menor letra entre duas palavras
  while(!EExterno(*p)){//Condição de parada: Encontrar um nó externo
    if(ComparaLetra((*p)->NO.NInterno.Index, (*p)->NO.NInterno.LetraComp, Palavra) == 1){//Se a letra, na posição Index, da palavra que será inserida é maior que a do nó interno:
      p = &(*p)->NO.NInterno.Dir;//Avança para o nó a direita
    }
    else{//Se a letra, na posição Index, da palavra que será inserida é menor ou igual à do nó interno:
      p = &(*p)->NO.NInterno.Esq;//Avança para o nó a esquerda
    }
  }//Fim do while
  if(ComparaLetra(i, (*p)->NO.Conteudo.Chave[i], Palavra) == 1){//Se a letra na posição i da palavra a ser inserida é maior do que a da chave:
    return (*p)->NO.Conteudo.Chave[i];//Retorna a letra da chave, já que é a maior
  }
  else{//Caso contrário, a menor letra é a da palavra a ser inserida
    return Palavra[i];//Retorna a letra da palavra a ser inserida
  }
}

TipoArvore InsereEntre(TipoChave Palavra, TipoArvore *t, int i, int idDoc){//Insere entre dois nós quando preciso
  TipoArvore p;//Apontador auxiliar que receberá o endereço do nó externo criado para a palavra a ser inserida
  if(EExterno(*t) || i < (*t)->NO.NInterno.Index){//Verifica se o nó é externo ou se o índice da letra que difere é menor que o índice do nó interno atual
    p = CriaNoExt(Palavra, idDoc);//Caso seja, o nó externo para a palavra a ser inserida é criado
    if(EExterno(*t)){//Se o nó é externo:
      if(ComparaLetra(i, (*t)->NO.Conteudo.Chave[i], Palavra) == 1){//Caso a letra da palavra a ser inserida na posição i seja maior que a da chave:
        return (CriaNoInt(i, t, &p, (*t)->NO.Conteudo.Chave[i]));//Cria o nó interno com a letra da chave na posição i (já que é a menor)
      }
      else{//Caso a letra da palavra a ser inserida na posição i seja menor que a da chave:
        return (CriaNoInt(i, &p, t, Palavra[i]));//Cria o nó interno com a letra da palavra que será inserida na posição i (já que é a menor)
      }
    }
    else{//Caso o nó seja interno:
      if(AchaLetra(t, i, Palavra) == Palavra[i]){//Verifica se a letra da palavra a ser inserida é a menor
        return (CriaNoInt(i, &p, t, Palavra[i]));//Retorna o nó interno criado com o nó externo da palavra a ser inserida na esquerda
      }
      else{//Se a letra da chave do nó folha encontrado é a menor:
        return (CriaNoInt(i, t, &p, AchaLetra(t, i, Palavra)));//Retorna o nó interno criado com o nó externo da palavra a ser inserida na direita
      }
    }
  }
  else{//Caso o nó seja interno:
    if(ComparaLetra((*t)->NO.NInterno.Index, (*t)->NO.NInterno.LetraComp, Palavra) == 1){//Se a letra, na posição Index, da palavra que será inserida é maior que a do nó interno:
      (*t)->NO.NInterno.Dir = InsereEntre(Palavra, &(*t)->NO.NInterno.Dir, i, idDoc);//Avança para o nó a direita
    }
    else{//Se a letra, na posição Index, da palavra que será inserida é menor ou igual à do nó interno:
      (*t)->NO.NInterno.Esq = InsereEntre(Palavra, &(*t)->NO.NInterno.Esq, i, idDoc);//Avança para o nó a esquerda
    }
    return (*t);//Faz o retorno da árvore final
  }
}

TipoArvore *AchaNoFolha(TipoArvore *ap){//Retorna um nó externo contendo a chave para ser comparada com a palavra a ser inserida
  while(!EExterno(*ap)){//Condição de parada: Encontrar um nó externo
    ap = &(*ap)->NO.NInterno.Esq;//Avança para o nó a direita
  }//Fim do while
  return ap;//Retorna o endereço desse nó
}

TipoArvore Insere(TipoChave Palavra, TipoArvore *t, int idDoc, TipoQtdeTermos *Ni){//Encapsulamento da função acima, chamando-a quando já há um ou mais nós criados
  TipoArvore *p;//Ponteiro para ponteiro auxiliar usado para percorrer a árvore
  int i, TAM1, TAM2;//Variáveis para funcionamento do procedimento
  TAM2 = strlen(Palavra);//Guarda o tamanho da palavra que será inserida
  if(*t == NULL){//Se o ponteiro da árvore é NULL:
    return (CriaNoExt(Palavra, idDoc));//Cria um nó externo para a primeira palavra a ser inserida
  }
  else{//Caso o ponteiro seja diferente de NULL
    p = t;//Ponteiro auxiliar recebe o endereço do ponteiro da árvore
    while(!EExterno(*p)){//Condição de parada: Encontrar um nó externo
      if(TAM2 < (*p)->NO.NInterno.Index){//Caso a palavra seja menor que o índice do nó interno:
        p = AchaNoFolha(p);//Acha um nó folha correspondente à esse nó interno para comparar a chave desse nó com a palavra a ser inserida
      }//Nota: Tanto faz o nó folha retornado desse nó interno já que a palavra a ser inserida é menor que todas as palavras abaixo do nó
      else{//Se a palavra é maior ou igual ao índice do nó interno:
        if(ComparaLetra((*p)->NO.NInterno.Index, (*p)->NO.NInterno.LetraComp, Palavra) == 1){//Se a letra, na posição Index, da palavra que será inserida é maior que a do nó interno:
          p = &(*p)->NO.NInterno.Dir;//Avança para o nó a direita
        }
        else{//Se a letra, na posição Index, da palavra que será inserida é menor ou igual à do nó interno:
          p = &(*p)->NO.NInterno.Esq;//Avança para o nó a esquerda
        }
      }
    }//Fim do while
    TAM1 = strlen((*p)->NO.Conteudo.Chave);//Guarda o tamanho da chave do nó folha
    i = ComparaChaves((*p)->NO.Conteudo.Chave, Palavra, TAM1, TAM2);//Recebe a posição em que há letras diferentes entre as duas palavras
    if(TAM1 == TAM2){//Se as duas palavras tiverem tamanhos iguais:
      if(i == TAM1){//Se não há nenhuma letra que difere entre as duas palavras:
        printf("Atencao: Chave (%s) ja esta na arvore!\n", (*p)->NO.Conteudo.Chave);//Mensagem de aviso
        int Verifica;//Variável usada para receber 0 se o documento referente à essa palavra não pertence à lista dela ou receber 1 se já pertence
        Verifica = ProcuraIdDoc(&(*p)->NO.Conteudo.Lista, idDoc, Ni);//Recebe um dos flags acima
        if(Verifica == 0){//Se for 0, significa que o documento referente à essa palavra não foi inserido na lista de índice invertido ainda
          InsereIndice(&(*p)->NO.Conteudo.Lista, idDoc, 1);//Insere esse novo documento na lista
        }
        return (*t);//Faz o retorno da árvore final
      }
      else{//Caso as duas palavras tenham tamanhos iguais, mas não sejam iguais, significa que a nova palavra deve ser inserida na árvore
        return (InsereEntre(Palavra, t, i, idDoc));//Chama a função para inserir essa nova palavra
      }
    }
    else{//Se as duas palavras tiverem tamanhos variados, significa que elas são palavras diferentes
      return (InsereEntre(Palavra, t, i, idDoc));//Chama a função para inserir essa nova palavra
    }
  }
}

void ImprimePat(TipoArvore t){//Imprime a árvore PATRICIA
  if(t == NULL){ //Verificacao se arvore esta criada.//
    printf("\n\t-->Arvore Vazia!<--\n\n");
    return;
  }
  if(EExterno(t)){//Verifica se o nó é externo, significando que uma chave deve ser mostrada
    printf("\nPalavra -> %s :", t->NO.Conteudo.Chave);//Imprime a palavra
    Imprime(t->NO.Conteudo.Lista);//Imprime a lista de índice invertido referente à essa palavra
  }
  else{//Se o nó for interno, significa que a árvore ainda deve ser percorrida
    if(t->NO.NInterno.Esq != NULL){//Verifica se o nó a esquerda não é vazio
      ImprimePat(t->NO.NInterno.Esq);//Avança para a esquerda primeiro (Para garantir a ordem alfabética)
    }
    if(t->NO.NInterno.Dir != NULL){//Verifica se o nó a direita não é vazio
      ImprimePat(t->NO.NInterno.Dir);//Avança para a direita por último (Para garantir a ordem alfabética)
    }
  }
}
