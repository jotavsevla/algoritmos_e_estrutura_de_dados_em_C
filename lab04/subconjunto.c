/*Dado um natural n, e uma coleção W de subconjuntos de
S={0,1,2,...,n-1}, encontrar um Wlinha subcoleção de W, se existir,
tal que cada elemento de S aparece em precisamente um dos conjuntos
dentro de Wlinha.
Por exemplo, se n = 8, e W={A={0,1,2},B={0,2,4},C={1,2,5},D={2,4},
E={1,3,5},F={3,5,7},G={2,7},H={1,6},I={2,4,6,7}}. Então, uma
solução possível é Wlinha={B={0,2,4},F={3,5,7}, H={1,6}}.
A entrada dada representará um único caso de teste.  A primeira
linha da entrada contém um número natural n, representando o
tamanho do conjunto S.  A segunda linha contém um número natural m
representando o tamanho do conjunto W. As m linhas seguintes
conterão, cada uma delas, a representação de um elemento de W.
Cada elemento A de W será representado por uma linha que começa com
um número natural k, representando o número de elementos do
conjunto A, que é elemento de W. Em seguida, a linha representando
A conterá k números naturais, iguais aos elementos de A. Estes
número estarão ordenados.
Os casos de teste passados terão 0<n<=15 e 0<m<=15.
Caso a instância passada na entrada não tenha solução, seu programa
deve imprimir uma única linha contendo a palavra "Insoluvel" (sem
acentos).  Caso a instância passada na entrada tenha solução
Wlinha, seu programa deve imprimir uma linha contendo um natural R
igual ao número de elementos de Wlinha, seguida de R linhas, onde
cada linha representa um elemento de Wlinha. A representação de um
elemento A de Wlinha é igual àquela de elementos de W na entrada.

As entradas passadas ou i) não terão solução, ou ii) terão solução
única.

Por exemplo, o caso descrito no exemplo acima seria representado por
uma entrada com as seguintes linhas:

8
9
3  0 1 2
3  0 2 4
3  1 2 5
2  2 4
3  1 3 5
3  3 5 7
2  2 7
2  1 6
4  2 4 6 7

A saída para a entrada do exemplo acima seria:
3
3  0 2 4
3  3 5 7
2  1 6   */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>


typedef enum  {
    coberto = 1,
    conflito = -1,
    not_coberto = -2,
    sem_solucao = 0
}veracidade;
typedef struct thread_parameters{
    int* bitmask, tam_W, W_bitmask, profundidade, tam_n;
    bool pega;
    veracidade resultado;
}Parametros;

void* combine_thread (void* imensidao_da_memoria);

void imprime_insoluvel();

void quais_cobriram (int* bitmask, int W_bitmask, int tam_W, int limit_index_elements);

veracidade combine (int* bitmask, int tam_W, int W_bitmask, int profundidade, bool pega, int n);

bool conflito_bit_x(int valor1, int valor2, int j);

int coloca_um (int bitmask, int shift);

int main (void){
    int m, n;

    scanf("%d", &n);
    scanf("%d", &m);

    // este trecho do código fica responsável
    // por definir quaantos elementos terao em cada um dos subconjuntos
    // e, antes disso, quantos subconjuntos devem representar o conjunto S
    printf("\n");

    int qnt_elements = 0, valor = 0;
    int* subconjuntos = calloc (m, sizeof (int));

    for (int i = 0; i < m; i++){
        scanf("%d", &qnt_elements);

        for(int j = 0; j < qnt_elements; j++){
            scanf("%d", &valor);
            subconjuntos[i] = coloca_um (subconjuntos[i], valor);
        }

    }

//    bool pega = true;
//    int profundidade = 0;
//    int op1, op2;

    pthread_t thread1, thread2;

    Parametros parametros1;
    parametros1.bitmask = subconjuntos;
    parametros1.tam_W = m;
    parametros1.W_bitmask = 1;
    parametros1.profundidade = 0;
    parametros1.pega = true;
    parametros1.tam_n = n;

    Parametros parametros2;
    parametros2.bitmask = subconjuntos;
    parametros2.tam_W = m;
    parametros2.W_bitmask = 0;
    parametros2.profundidade = 0;
    parametros2.pega = false;
    parametros2.tam_n = n;
    
    clock_t time = clock();
    pthread_create (&thread1, NULL, combine_thread, &parametros1);
    pthread_create (&thread2, NULL, combine_thread, &parametros2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    time = clock() - time;

    printf("%d\n", (int)time);
  //  op1 = combine_thread(&parametros1);
  //  op2 = combine_thread(&parametros2);
//    op1 = combine (subconjuntos, m,  1, profundidade, pega, n);
//    op2 = combine (subconjuntos, m,  0, profundidade, !pega, n);

    if (parametros1.resultado == sem_solucao && parametros2.resultado == sem_solucao){
        imprime_insoluvel();
        return 0;
    }
    parametros1.resultado != sem_solucao ? quais_cobriram(subconjuntos, parametros1.resultado, m, n) : quais_cobriram(subconjuntos, parametros2.resultado, m, n);

    return 0;
}

void imprimebit(int bitmask){
    for (int i = 0; i < (sizeof(int) * 8); ++i){ // Itera entre todas as posições (bits) do int
        if (i > 7 && i % 8 == 0) printf(" ");   // Apenas para espaçar a cada 8 bits
        if((bitmask&(1<<i)) != 0) printf("1"); // Confere se há um bit 1 na posição i, se houver, imprime 1
        else printf("0");                     // Se não houver, imprime 0
    }
    printf("\n");
}


void* combine_thread (void* imensidao_da_memoria){
    Parametros* arg = (Parametros*) imensidao_da_memoria;
    arg->resultado = combine(arg->bitmask, arg->tam_W, arg->W_bitmask, arg->profundidade, arg->pega, arg->tam_n);
     return NULL;
}



void imprime_insoluvel(){
    printf("Insoluvel\n");
}


int coloca_um ( int bitmask, int shift){
    bitmask = bitmask|(1<<shift);
    return bitmask;
}


bool conflito_bit_x(int mascara1, int mascara2, int j){
    if((mascara1&(1<<j)) != 0 && (mascara2&(1<<j)) != 0)
        return true; //com conflito
    return false;    //sem conflito
}

/* está função é responsável por retornar um parâmetro que define, se ja existe conflito naquela
 montagem atual, se ainda nao existe conflito e ja tem resposta definida */

veracidade cobre(int W_bitmask, int* subconjunto, int tam_W, int tam_subconjunto){
    int acumulador = 0;
    //percorre cada um dos subconjuntos e verifica que estão inclusos na atual instancia
    for (int i = 0; i < tam_W; ++i){
        // verificar se este index(i) está incluso
        if((W_bitmask&(1<<i)) != 0){
            for(int j = 0; j < tam_subconjunto; ++j){
                if(conflito_bit_x(acumulador, subconjunto[i], j))
                    return conflito;
            }
            acumulador |= subconjunto[i];
        }
    }
    for (int i = 0; i < tam_subconjunto; ++i){
        if ((acumulador&(1<<i)) == 0)
            return not_coberto;
    }
    return coberto;
}


int combine (int* bitmask, int tam_W, int W_bitmask, int profundidade, bool pega, int tam_n){
    if (pega)
        W_bitmask = coloca_um(W_bitmask, profundidade);
    if( tam_W < profundidade)
        return sem_solucao;

    switch (cobre(W_bitmask, bitmask, tam_W, tam_n)) {
        case coberto:
            return W_bitmask;
        case conflito:
            return sem_solucao;
        default:
            break;
    }

    int res1 = combine (bitmask, tam_W,  W_bitmask, profundidade+1, pega, tam_n);
    int res2 = combine (bitmask, tam_W, W_bitmask, profundidade+1, !pega, tam_n);

    if (res1 != sem_solucao)
        return res1;
    return res2;
}
// esta função conta os elementos onde existe um subconjunto
void quais_cobriram (int* sub_conjuntos, int W_bitmask, int tam_W, int limit_index_elements){
    int contador_elementos;
    int contador_W = 0;

    for (int i = 0; i < tam_W; ++i)
        if ((W_bitmask&(1<<i)) != 0)
            ++contador_W;

    printf("%d\n", contador_W);

    for(int i = 0; i < tam_W; ++i){
        contador_elementos = 0;
        // no caso em que esteja, percorre ele 1 vez para saber quantos
        // elementos ele possui e imprime na tela, depois, percorre novamente
        // imprimindo as posiçoes respectivas onde ha um bit no vetor binário
        if((W_bitmask&(1<<i)) != 0){
            for(int j = 0; j < limit_index_elements; ++j){
                if((sub_conjuntos[i]&1<<j)!=0)
                    contador_elementos++;
            }
            printf("%d ", contador_elementos);
            for(int j = 0; j < limit_index_elements; ++j){
                if((sub_conjuntos[i]&1<<j)!= 0)
                    printf("%d ", j);
            }
            printf("\n");
        }
    }
}
