#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
void inicializa_lista(Lista * ap_lista){
    (*ap_lista) = malloc (sizeof(No));

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
    printf("[");
    if (lista->prox == lista){
        printf("]\n");
        return;
    }
    No* percorre = lista->prox;
    printf("(%i,%i)", percorre->valor.grau, percorre->valor.coef);
    percorre = percorre->prox;
    
    while (percorre != lista){
        printf (",(%i,%i)", percorre->valor.grau, percorre->valor.coef);
        percorre = percorre->prox;
    }
    printf ("]\n");
    return;
}
/* Remove valor do fim da lista apontada por ap_lista e retorna este valor. */
TipoDado remove_fim(Lista ap_lista){
    if (ap_lista == ap_lista->prox){
        TipoDado vaLinexistente;
        vaLinexistente.coef = vaLinexistente.grau = -1;
        return vaLinexistente;
    }
    No* remover = ap_lista->antec;
    TipoDado valremovido = remover->valor;

    remover->antec->prox = ap_lista;
    ap_lista->antec = remover->antec;
    free(remover);

    return valremovido;
}

/* Remove valor do inicio da lista apontada por ap_lista e retorna este valor. */
TipoDado remove_inicio(Lista ap_lista){
    if (ap_lista == ap_lista->prox){
        TipoDado vaLinexistente;
        vaLinexistente.coef = vaLinexistente.grau = -1;
        return vaLinexistente;
    }
    No* remover = ap_lista->prox;
    TipoDado valremovido = remover->valor;

    remover->prox->antec = ap_lista;
    ap_lista->prox = remover->prox;
    free(remover);

    return valremovido;
    
}

/* Remove todas as ocorrencias de valor da lista apontada por ap_lista. 
 * Retorna o numero de ocorrencias removidas. */
int remove_ocorrencias(Lista ap_lista, TipoDado valor){
    if (ap_lista->prox == ap_lista) return 0;
    int count = 0;
    No* procura = ap_lista->prox;
    while(procura != ap_lista){
        if(procura->valor.grau == valor.grau && procura->valor.coef == valor.coef){
            count++;
            No* remove = procura;
            procura = procura->prox;
            remove->antec->prox = procura;
            procura->antec = remove->antec;
            procura = procura->antec;
            free(remove);
        }
        else
        procura = procura->prox;
    }
    if (ap_lista->prox->valor.coef == valor.coef 
    && ap_lista->prox->valor.grau == valor.grau
    && ap_lista->prox != ap_lista){
        No* remove = procura;
        procura = procura->prox;
        remove->antec->prox = procura;
        procura->antec = remove->antec;
        free(remove);

        return count++;
    } 
    return count;
}

/* Busca elemento valor na lista. 
   Retorna a posição da primeira ocorrencia de valor na lista, comecando de 0=primeira posicao.
   Retorna -1 caso nao encontrado. */
int busca(Lista lista, TipoDado valor){
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
    if (lista == lista->prox) return 0;
    No* tmpGrau = lista->prox;
    while (tmpGrau != lista && tmpGrau->valor.grau != grau) tmpGrau = tmpGrau->prox;
    if(grau != tmpGrau->valor.grau) return 0;
    return tmpGrau->valor.coef;
}

/* Desaloca toda a memória alocada da lista.
 */
void desaloca_lista(Lista *ap_lista){
    No* percorre = (*ap_lista)->prox;
    while (percorre != (*ap_lista)){
        No* remove = percorre;
        percorre = percorre->prox;
        free (percorre);
    }
    return;
}
