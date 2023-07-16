#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TABLE_SIZE 15

typedef struct tipodado {
    int idade;
    char* nome;
    int cpf;
}tipodado;

typedef struct No{
    tipodado pessoa;
    struct No* prox;
}No, Lista*;

void inicializa_hash (Lista hash[]);

void inicializa_lista (Lista nova_lista);

No* insere_no (tipodado chave, No proximo, No antec);

void imprime (Lista hash[TABLE_SIZE]);

int main (void){
    Lista* hash = calloc (TABLE_SIZE, sizeof(Lista));
    int i;
    inicializa_hash(&hash);
    
    while(i != -1){
        
    }
    imprime (&hash);
    return 0;
}
void inicializa_hash(Lista* hash){
    for(Lista i = hash; i + TABLE_SIZE != hash + TABLE_SIZE; i++){
        No* novo_cabeca = malloc (sizeof(No));
        *i = novo_cabeca;
        incializa_lista (i);
    }
}
void inicializa_lista (Lista* nova_lista){
    (*nova_lista)->prox = (*nova_lista);
}
insere_na_tabela(No* atual, No* prox, No* )
void imprime (Lista hash[]){
    for (int i = 0; i < TABLE_SIZE; i++){
        printf ("posicao da tabela %i, nome %s, idade %d\n", i, hash[i]->prox.tipodado.nome, hash[i]->prox.tipodado.idade);
    }
}
