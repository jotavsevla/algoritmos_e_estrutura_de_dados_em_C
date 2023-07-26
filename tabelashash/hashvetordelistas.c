#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 15

typedef struct{
    int idade;
    char nome[50];
    int cpf;
}tipodado;

typedef struct{
    tipodado pessoa;
    struct No* prox;
}No, *Lista;

void inicializa_hash (Lista* tabela[]);
void inicializa_lista (Lista* nova_lista);
No* cria_no (tipodado pessoa);
void insere_no (No* atual);
tipodado cria_ficha();
void insere_tabela (Lista* tabela[], tipodado); 
int hash (int chave);
bool busca_na_tabela(Lista* tabela[], int idade, char* nome, int cpf);

void imprime (Lista* tabela[TABLE_SIZE]);
int main (void){
    Lista* lista[TABLE_SIZE];
    int i;
    inicializa_hash(lista);
    printf("Digite 1 para inserir na tabela, 2 para imprimir toda a tabela\n");
    scanf ("%d",&i);
    switch(i){
        case  1: insere_tabela (lista, cria_ficha())
    }
    imprime (lista);
    return 0;
}
void inicializa_hash(Lista* tabela[]){    
    for(int i = 0; i != TABLE_SIZE; i++){
        inicializa_lista (&tabela[i]);
    }
}
void inicializa_lista (Lista* nova_lista){
    *nova_lista= NULL;    // poderia utilizar o NULL tambem
}
int hash (int chave){return chave % TABLE_SIZE;}
No* cria_no (tipodado pessoa){
    No* novo_no = malloc(sizeof(No));
    novo_no->pessoa = pessoa;
    return novo_no;
}
void insere_no (No* novo_no, No* atual){
    novo_no->prox = NULL;
    atual->prox = novo_no;
}
void insere_tabela (Lista* tabela[], tipodado pessoa){
    No* percorre = tabela[hash (pessoa->idade)];
    while (percorre != NULL)
        percorre = percorre->prox;
    insere_no (cria_no (pessoa), percorre);
    
}
tipodado* cria_ficha (){
    tipodado* nova_pessoa = malloc (sizeof(tipodado));
    printf ("Digite respectivamente, Nome,Idade,CPF.\n");
    fgets (nova_pessoa->nome);
    while ((getchar()) != '\n');
    scanf ("%i", nova_pessoa->idade);
    while ((getchar()) != '\n');
    scanf ("%i",nova_pessoa->cpf);

    return nova_pessoa;
}
void imprime (Lista* tabela[]){
    for (int i = 0; i < TABLE_SIZE; i++){
        for(No* atual = tabela[i]->prox; atual != NULL; atual = atual->prox)
            printf ("Nome: %s, Idade: %i, CPF: %i\n", atual.pessoa.nome, atual.pessoa.idade, atual.pessoa.cpf);
    }
}
