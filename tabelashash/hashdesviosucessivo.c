#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE  10
#define BUCKET_SIZE 3

typedef struct pessoa {
    char *nome;
    int idade;
}pessoa;

typedef struct bucket {

    pessoa p [BUCKET_SIZE];
    int qtt_pessoas;

}bucket;

int hash(int chave, int tentativa) {
  int hash = 0;
  while (chave > 0) {
    hash += chave % 10;
    chave /= 10;
  }
  return (hash + tentativa) % TABLE_SIZE;
}


bool insere_na_tabela (bucket tabela[], pessoa p){
    int tentativa = 1;
    int posicao;
    do{    
        posicao = hash(p.idade,tentativa);
        printf("H:%d T:%d\n", posicao, tentativa);
        tentativa++;
    }while(tabela[posicao].qtt_pessoas == BUCKET_SIZE && tentativa < TABLE_SIZE);

    if (tabela[posicao].qtt_pessoas < BUCKET_SIZE){
        tabela[posicao].p[tabela[posicao].qtt_pessoas] = p;
        tabela[posicao].qtt_pessoas++;
    }
    
}
bool busca_na_tabela (bucket tabela[],int chave){
    int pos, tentativa, i;
    tentativa = 1;
    do {
        pos = hash(chave, tentativa);
        for (i = 0; i < BUCKET_SIZE; ++i){
            if (chave == tabela[pos].p[i].idade){
                printf ("Encontrado na posicao %d\n", pos);
                return true;
            } 
        }
        tentativa++;
    }while(tentativa < TABLE_SIZE);
    printf ("Valor %d nao encontrado\n", chave);
    return false;
}

void imprime (bucket tabela[]){
    printf("Imprime: \n");
    for(int i = 0; i < TABLE_SIZE; ++i){
        printf("[Pos %d] ",i);
        for (int j = 0; j < tabela[i].qtt_pessoas; ++j)
            printf("%d ", tabela[i].p[j].idade);
        printf("\n");
    }
    return;
}
int main (void){

    bucket tabela[TABLE_SIZE];
    pessoa p;
    int chave;
    
    for (int i = 0; i < TABLE_SIZE; i++)
        tabela[i].qtt_pessoas = 0;

    int i  = 0;
    while(i < 25){
        p.idade = i + rand() % 100;
        p.nome = "Teste";
        insere_na_tabela (tabela, p);
        imprime (tabela);
        i++;
    }
    printf("Digite -1 para sair da busca\n");
    while (chave != -1){
        printf("Valor a ser buscado: ");
        scanf("%d",&chave);
        busca_na_tabela (tabela, chave);
    }
}