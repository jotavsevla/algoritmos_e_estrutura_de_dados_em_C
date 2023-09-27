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

typedef enum  {
    coberto = 1,
    conflito = -1,
    not_coberto = -2,
    sem_solucao = 0
}veracidade;

void imprime_insoluvel();
void quais_cobriram (int* bitmask, int W_bitmask, int tam_W, int limit_index_elements);
veracidade combine (int* bitmask, int tam_W, int W_bitmask, int profundidade, bool pega, int n);
bool conflito_bit_x(int valor1, int valor2, int j);
int coloca_um (int bitmask, int shift);


void imprimebit(int bitmask){
    for (int i = 0; i < (sizeof(int) * 8); ++i){ // Itera entre todas as posições (bits) do int
        if (i > 7 && i % 8 == 0) printf(" ");   // Apenas para espaçar a cada 8 bits
        if((bitmask&(1<<i)) != 0) printf("1"); // Confere se há um bit 1 na posição i, se houver, imprime 1
        else printf("0");                     // Se não houver, imprime 0
    }
    printf("\n");
}


void imprime_insoluvel(){
    printf("Insoluvel\n");
}


int coloca_um ( int bitmask, int shift){
    bitmask = bitmask|(1<<shift);
    return bitmask;
}


bool conflito_bit_x(int valor1, int valor2, int j){
    imprimebit(valor1);
    imprimebit(valor2);
    if((valor1&(1<<j)) != 0 && (valor2&(1<<j)) != 0)
        return true; //com conflito
    return false;    //sem conflito
}

/* está função é responsável por retornar um parâmetro que define, se ja existe conflito naquela
 montagem atual, se ainda nao existe conflito e ja tem resposta definida */

veracidade cobre(int W_bitmask, int* subconjunto, int tam_W, int tam_subconjunto){
    int acumulador = 0;
    //percorre cada um dos index
    for (int i = 0; i < tam_W; ++i){
        // verificar se este index(i) está incluso
        if((W_bitmask&(1<<i)) != 0){
            printf("index %i está incluso\n", i); // TODO: REMOVER
            for(int j = 0; j < tam_subconjunto; ++j){
                if(conflito_bit_x(acumulador, subconjunto[i], j)) {
                    printf("conflito no bit %i\n", j); // TODO: REMOVER
                    return conflito;
                }
                acumulador = subconjunto[i] | (1<<i);

            }
        }
    }
    for (int i = 0; i < tam_subconjunto; ++i){
        if ((acumulador&(1<<i)) == 0)
            return not_coberto;
    }
    return coberto;
}


int combine (int* bitmask, int tam_W, int W_bitmask, int profundidade, bool pega, int tam_n){
    switch (cobre(W_bitmask, bitmask, tam_W, tam_n)) {
        default:
            break;
        case coberto:
            return W_bitmask;
            break;
        case conflito:
            return sem_solucao;
            break;
    }
    if( tam_W < profundidade)
        return sem_solucao;
    if (pega)
        W_bitmask = coloca_um(W_bitmask, profundidade);
    int res1 = combine (bitmask, tam_W,  W_bitmask, ++profundidade, pega, tam_n);
    int res2 = combine (bitmask, tam_W, W_bitmask,++profundidade , !pega, tam_n);

    if (res1 != 0)
        return res1;
    return res2;
}
// esta função conta os elementos onde existe um subconjunto
void quais_cobriram (int* sub_conjuntos, int W_bitmask, int tam_W, int limit_index_elements){
    int contador_elementos = 0;
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
            printf("%i ", contador_elementos);
            for(int j = 0; j < limit_index_elements; ++j){
                if((sub_conjuntos[i]&1<<j)!= 0)
                    printf("%i ", j);
            }
            printf("\n");
        }
    }
}
