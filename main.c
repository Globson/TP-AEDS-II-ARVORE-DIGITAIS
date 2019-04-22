/*
   Josué Nunes Campos - 3465
   Mateus Coelho Santos - 3488
   Samuel Pedro Campos Sena - 3494
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LEITURA.h"//Incluíndo o TAD que contém as funções necessárias

//Programa principal
int main(){
  TipoArvore P;//Ponteiro da Árvore PATRICIA
  TipoApontador Pt;//Ponteiro da Árvore TST
  TipoQtdeTermos *Ni;//Vetor de número de elementos distintos de cada documento
  int N;//Quantidade total de documentos
  InicializaNdoc(&N);//Inicializando o número de documentos na coleção
  InicializaPat(&P);//Inicializando o ponteiro da árvore PATRICIA
  Inicializa(&Pt);//Inicializando o ponteiro da árvore TST
  menu(&P, &Pt, &N, Ni);//Chamando o menu de escolhas
  printf("\n\t\t   Desenvolvedores:\n\t\t    Josue Campos - 3465\n\t\t    Mateus Coelho - 3488\n\t\t    Samuel Sena - 3494\n\n\t       OBRIGADO POR UTILIZAR O PROGRAMA!\n"); //Agradecimentos
  return 0;
}//Fim do programa principal
