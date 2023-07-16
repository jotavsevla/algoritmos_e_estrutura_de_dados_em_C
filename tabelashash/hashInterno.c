#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define BUCKET_SIZE 3
#define SEM_DESVIO -1


int index_prox_desvio_livre = (TABLE_SIZE / 2) - 1;

typedef struct bucket{
    int chave[BUCKET_SIZE];  // Vetor de chaves
    int qtt_chaves;  // Quantidade de chaves atualmente no bucket
    int desvio_index;  // Indice na tabela onde os próximos elementos de mesmo hash serão armazenados
} bucket;

void insere_na_tabela(int chave, int pos, bucket tabela[]);

void imprime (bucket tabela[]);

// Calcula o valor de hash de um dado elemento
// TODO: Modificar para retornar somente indexes até metade da tabela

int find_free_index(bucket tabela[]);

int hash(int chave){ return chave % (TABLE_SIZE/2); }

int main (void){
    bucket tabela[TABLE_SIZE];  // A tabela é um vetor de buckets

    // Inicializando a tabela
    for (int i = 0; i < TABLE_SIZE; ++i){
        tabela[i].qtt_chaves = 0;
        tabela[i].desvio_index = SEM_DESVIO;  // -1 indica que não há desvio (ainda)
    }

    int chave;
    while (true){
        scanf("%i", &chave);
        // chamar a funcao de inserir
        insere_na_tabela(chave, hash(chave), tabela);
        imprime(tabela);
    }

}

void insere_na_tabela(int chave, int pos, bucket tabela[]){             // Se, a quantidade de chaves for menor que 3, significa, que pode-se colocar a chave com índice de valor = à qtt_chaves;
    if (tabela[pos].qtt_chaves < BUCKET_SIZE){
        tabela[pos].chave[tabela[pos].qtt_chaves] = chave;
        tabela[pos].qtt_chaves++;
    } else {                                                            // Se não, eu verifico se essa posição da hash, não possui endereço de desvio(SEM_DESVIO = -1) e, caso nao tenha, prontifico a função que busca este index 
        if (tabela[pos].desvio_index == SEM_DESVIO)                     // para retornar o valor de [índice] passando seu valor para desvio_index para o endereço da tabela //respectiva, antes, da instância recursiva que servirá para o caso
            tabela[pos].desvio_index = find_free_index(tabela);         // em que ele ja tem um desvio configurado e para o caso em que precisa identificar um desvio
        insere_na_tabela(chave, tabela[pos].desvio_index, tabela);
    }
}
int find_free_index(bucket tabela[]){
    for (int i = TABLE_SIZE/2; i < TABLE_SIZE; ++i)
        if(tabela[i].qtt_chaves == 0) return i;
    printf ("Espaco insuficiente, seu programa sera encerrado\n");
    exit(1);
}
void imprime (bucket tabela[]){

    for(int i = 0; i < TABLE_SIZE; ++i){
        printf("[Pos %d] ",i);
        for (int j = 0; j < tabela[i].qtt_chaves; ++j)
            printf("%d ", tabela[i].chave[j]);
        printf("\n");
    }
    return;
}