#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
void inicializa_lista(Lista * ap_lista){
    (*ap_lista) = NULL;
}
void insere_fim(Lista * ap_lista, int valor){
    No* novo_no = malloc (sizeof(No));
    novo_no->valor = valor;
    novo_no->proximo = NULL;
    if ((*ap_lista) == NULL){
        insere_inicio (ap_lista, valor);
        return;
    }
    No* percorre = (*ap_lista);
    while (percorre->proximo != NULL) percorre = percorre->proximo;
    percorre->proximo = novo_no;

}
void insere_inicio(Lista * ap_lista, int valor){
    No* novo_no = malloc (sizeof(No));
    novo_no->valor = valor;

    novo_no->proximo = (*ap_lista);
    *ap_lista = novo_no;
    return;
}
int remove_inicio(Lista * ap_lista){
    if ((*ap_lista) == NULL) return -1;
    No* remove = (*ap_lista);
    int val;
    if ((*ap_lista)->proximo == NULL){
        val = (*ap_lista)->valor;
        (*ap_lista) = NULL;
        free(remove);
        return val;
    }
    (*ap_lista) = (*ap_lista)->proximo;
    val = remove->valor;
    
    free (remove);
    return val;
}
int remove_fim(Lista * ap_lista){
    if ((*ap_lista) == NULL) return -1;
    if ((*ap_lista)->proximo == NULL){
        No* remove = (*ap_lista);
        int val = remove->valor;
        (*ap_lista) = NULL;
        free (remove);
        return val;
    }
    No* anterior;
    anterior = (*ap_lista);
    No* atual = (*ap_lista)->proximo;

    while (atual->proximo != NULL){
        anterior = atual;
        atual = atual->proximo;
    }
    anterior->proximo = NULL;
    int val = atual->valor;
    free (atual);
    return val;

}
bool remove_i_esimo(Lista * ap_lista, int i){
    if((*ap_lista) == NULL) return false;   
    No* remove = (*ap_lista);
    if(i == 1 && remove->proximo == NULL){
        free(remove);
        (*ap_lista) = NULL;
        return true;
    }
    if (i == 1){
        *ap_lista = (*ap_lista)->proximo;
        free (remove);
        return true;
    }
    remove = remove->proximo;
    int index = 2;
    No* antec;
    while(remove->proximo != NULL && i != index){
        antec = remove;
        remove = remove->proximo;
        index++;
    } 
    if (i == index){
        antec->proximo = remove->proximo;
        free(remove);
        return true;
    }
    return false;

}
int recupera_i_esimo(Lista lista, int i){
    if(lista == NULL) return -1;
    No* procura = lista;
    int index;
    int val = procura->valor;
    for (index = 1; procura != NULL && index != i; index++) {
        val = procura->valor;
        procura = procura->proximo;
    }
    if (index != i) return -1;
    return procura->valor;
}
int tamanho(Lista lista){
    int index_count = 0;
    No* percorre = lista;
    while (percorre != NULL){
        percorre = percorre->proximo;
        index_count++;
    }
    return index_count;
}
int remove_ocorrencias(Lista *ap_lista, int valor){
    if (*ap_lista == NULL) return 0;
    int i = 0;
    No* tmp = *ap_lista;
    while(tmp != NULL && tmp->proximo != NULL){
        if (tmp->proximo->valor == valor){
        printf("%i\n", valor); 
        No* apagar = tmp->proximo;
        tmp->proximo = tmp->proximo->proximo;
        free (apagar);
        i++;
      } else{
         tmp = tmp->proximo;
      }
    }
    if(tmp->valor == valor){
        No* apagar = tmp;
        *ap_lista = tmp->proximo;
        free (apagar);
        i++;
    }
    return i;
}
int busca(Lista lista, int valor){
    if (lista == NULL) return -1;
    int i = 0;
    No* percorre = lista;
    while (percorre != NULL && percorre->valor != valor){
        percorre = percorre->proximo;
        i++;
    }
    if (percorre->valor != valor) return -1;
    return i;
    
}
void imprime(Lista lista){
    if(lista == NULL) {
        printf("Lista vazia\n");
        return;
    }
    No* percorre = lista;
    printf ("(%i", percorre->valor);
    percorre = percorre->proximo;
    while (percorre != NULL){
        printf (",%i", percorre->valor);
        percorre = percorre->proximo;
    }
    printf (")\n");
    return;
}
void desaloca_lista(Lista *ap_lista){
    No* percorre = (*ap_lista);
    while (percorre != NULL){
        No* remove = percorre;
        percorre = percorre->proximo;
        free(remove);
    }
}