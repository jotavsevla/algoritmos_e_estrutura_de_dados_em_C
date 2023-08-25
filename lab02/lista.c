#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
void inicializa_lista(Lista * ap_lista){
    Lista no_cabeca = malloc (sizeof(No));

    (*ap_lista)->antec = (*ap_lista);
    (*ap_lista)->prox = (*ap_lista);
    (*ap_lista)->valor.grau = (*ap_lista)->valor.coef = 0;
}
void insere_fim(Lista ap_lista, TipoDado valor){
    No* novo_no = malloc (sizeof(No));
    novo_no->valor = valor;

    novo_no->prox = ap_lista;
    novo_no->antec = ap_lista->antec;

    ap_lista->antec->prox = novo_no;
    ap_lista->antec = novo_no;

    return;
}
void insere_inicio(Lista ap_lista, TipoDado valor){
    
    No* novo_no = malloc (sizeof(No));
    novo_no->valor = valor;

    novo_no->antec = ap_lista;
    novo_no->prox = ap_lista->prox;

    ap_lista->prox->antec = novo_no;
    ap_lista->prox = novo_no;

    return;
}
void imprime(Lista lista){
    if (lista->prox == lista){
        printf("Lista vazia\n");
        return;
    }
    No* percorre = lista->prox;
    printf("[");
    printf("(%i,%i)", percorre->valor.coef, percorre->valor.grau);
    percorre = percorre->prox;
    
    while (percorre != lista){
        printf (",(%i,%i)",percorre->valor.coef, percorre->valor.grau);
        percorre = percorre->prox;
    }
    printf ("]\n");
    return;
}
/* Remove valor do fim da lista apontada por ap_lista e retorna este valor. */
TipoDado remove_fim(Lista ap_lista){
    TipoDado tmp;
    tmp.coef = tmp.grau = 0;
    return tmp;
}

/* Remove valor do inicio da lista apontada por ap_lista e retorna este valor. */
TipoDado remove_inicio(Lista ap_lista){
    TipoDado tmp;
    tmp.coef = tmp.grau = 0;
    return tmp;
}

/* Remove todas as ocorrencias de valor da lista apontada por ap_lista. 
 * Retorna o numero de ocorrencias removidas. */
int remove_ocorrencias(Lista ap_lista, TipoDado valor){
    if (ap_lista->prox == ap_lista) return 0;
    No* procura = ap_lista->prox;
    while(procura != ap_lista){
        if(procura->valor.grau == valor.grau){
            No* remove = procura;

        }
        procura = procura->prox;
    }
    return 0;
}

/* Busca elemento valor na lista. 
   Retorna a posição da primeira ocorrencia de valor na lista, comecando de 0=primeira posicao.
   Retorna -1 caso nao encontrado. */
int busca(Lista lista, TipoDado valor){
    printf ("entrei em busca\n");
    if (lista->prox == lista) return -1;
    int count = -1;
    No* busca = lista->prox;
    while (busca != lista && busca->valor.grau != valor.grau){
        busca = busca->prox;
        count++;
    } 
    if (busca->valor.grau != valor.grau) return count;
    return -1;
}

/* Retorna o campo coef do primeiro no que contenha grau igual ao parametro grau, 
   e 0 (zero) caso nao encontre um tal no.  */
int coeficiente_do_grau(Lista lista, int grau){
    return 0;
}

/* Desaloca toda a memória alocada da lista.
 */
void desaloca_lista(Lista *ap_lista){
    return;
}
