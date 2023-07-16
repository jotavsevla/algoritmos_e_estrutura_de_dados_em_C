#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
/*
 * Implemente as seguintes funcoes utilizando uma lista circular
 * duplamente ligada com no cabeca.
 */


/* Inicializa a lista como lista vazia. */

void inicializa_lista(Lista * ap_lista){
    *ap_lista = (No*) calloc (1,sizeof(No));
    (*ap_lista)->antec = *ap_lista;
    (*ap_lista)->prox = *ap_lista;

}

No* cria_no(TipoDado valor, No* antec, No* prox){

   No* novo_no = (No*) malloc (sizeof(No));
   if (novo_no == NULL) exit(2);

   novo_no->antec = antec;
   novo_no->prox = prox;
   novo_no->valor.grau = valor.grau;
   novo_no->valor.coef = valor.coef;
   return novo_no;
}

/* Insere valor no fim da lista apontada por ap_lista. ap_lista aponta para o no cabeca da lista. */
void insere_fim(Lista ap_lista, TipoDado valor){
    
   No* novo_no = cria_no(valor, ap_lista->antec, ap_lista);

    novo_no->antec->prox = novo_no;
    ap_lista->antec = novo_no;
    return;
}

/* Insere valor no inicio da lista apontada por ap_lista. ap_lista aponta para o no cabeca da lista. */
void insere_inicio(Lista ap_lista, TipoDado valor){

    No* novo_no = cria_no(valor, ap_lista, ap_lista->prox);

    novo_no->prox->antec = novo_no;
    ap_lista->prox = novo_no;
    return;
}

/* Remove valor do fim da lista apontada por ap_lista e retorna este valor. */
TipoDado remove_fim(Lista ap_lista){
   No* no_penacova = ap_lista->antec;

   no_penacova->antec->prox = ap_lista;
   ap_lista->antec = no_penacova->antec;

   TipoDado valor = no_penacova->valor;

   free(no_penacova);

   return valor;
}

/* Remove valor do inicio da lista apontada por ap_lista e retorna este valor. */
TipoDado remove_inicio(Lista ap_lista){
   No* no_penacova = ap_lista->prox;

   no_penacova->prox->antec = ap_lista;
   ap_lista->prox = no_penacova->prox;
   
   TipoDado valor = no_penacova->valor;

   free(no_penacova);

   return valor;
}

/* Remove todas as ocorrencias de valor da lista apontada por ap_lista. 
 * Retorna o numero de ocorrencias removidas. */
int remove_ocorrencias(Lista ap_lista, TipoDado valor){

}

/* Busca elemento valor na lista. 
   Retorna a posição da primeira ocorrencia de valor na lista, comecando de 0=primeira posicao.
   Retorna -1 caso nao encontrado. */
int busca(Lista lista, TipoDado valor){
   No* em_analise = lista->prox;
   
   int indice = -1;

   while (em_analise->prox != lista || em_analise != lista){
      indice++;
      if ((em_analise->valor.coef == valor.coef) && (em_analise->valor.grau == valor.grau))
         return indice;
      em_analise = em_analise->prox;
   }
   return -1;
}

/* Retorna o campo coef do primeiro no que contenha grau igual ao parametro grau, 
   e 0 (zero) caso nao encontre um tal no.  */
int coeficiente_do_grau(Lista lista, int grau){

}

/* Imprime a lista na saida padrao, no formato:
   [(1,3),(2,3),(4,2),(3,1),(4,17)]
   em uma linha separada. */
void imprime(Lista lista){
   No* temp = lista;
   printf ("[");
   while (temp->prox != lista && temp == lista){
      temp = temp->prox;
      printf("(%i, %i)",temp->valor.grau,temp->valor.coef);
   }
   printf ("]");
   return;
}

/* Desaloca toda a memória alocada da lista.
 */
void desaloca_lista(Lista *ap_lista){

}