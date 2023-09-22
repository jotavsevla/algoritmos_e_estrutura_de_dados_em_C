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
2  1 6*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum veracidade {
    coberto = 1,
    conflito = -1,
    not_coberto= -2,
    sem_solucao = 0
};
bool conflito_bit_x(int valor1, int valor2, int j);
bool cobre_ou_nao(int W_bitmask);
int shift ( int bitmask, int shift);
int main (void){
    int m = 16; int n =16;
    while (n >= 15 && m >=15){
        scanf("%i", &n);
        printf("\n");
        scanf("%i", &m);
    }
    // este trecho do código fica responsável
    // por definir quaantos elementos terao em cada um dos subconjuntos
    // e, antes disso, quantos subconjuntos devem representar o conjunto S
    int qnt_elements = 0, valor = 0;
    int* bitmask = calloc (m, sizeof (int));
    for (int i = 0; i < m; i++){
        scanf("%i", &qnt_elements);
        for(int j = 0; j < qnt_elements; j++){
            scanf("%i", &valor);
            bitmask[i] = shift(bitmask[i], valor);
        }
    }
    combine (bitmask, n,  m, profundidade, pega, n);
    combine (bitmask, n,  m, profundidade, !pega, n);
}
int shift ( int bitmask, int shift){
    bitmask = bitmask|(1<<shift);
    return bitmask;
}
bool conflito_bit_x(int valor1, int valor2, int j){
    if((valor1&(1<<j)) != 0 && (valor2&(1<<j)) != 0)
        return true; //com conflito
    return false;     //sem conflito
}

/* está função é responsável por retornar um parâmetro que define, se ja existe conflito naquela
 montagem atual, se ainda nao existe conflito e ja tem resposta definida */

int cobre(int W_bitmask, int* bitmask, int tam_W, int n){
    int acumulador = 0;
    //percorre cada um dos index
    for (int i = 0; i < tam_W; ++i){
        //verificar se este index(i) está incluso
        if((W_bitmask&(1<<i)) != 0){
            for(int j = 0; j < n; ++j){
                if(conflito_bit_x(acumulador, bitmask[i], j))
                    return conflito;
                acumulador = bitmask[i] | (1<<i);

            }
        }
    }
    for (int i = 0; i < n; ++i){
        if ((acumulador&(1<<i)) == 0)
            return not_coberto;
    }
    return coberto;
}
int  combine (int* bitmask, int tam_W, int W_bitmask, int profundidade, bool pega, int n){
    switch (cobre(W_bitmask, bitmask, tam_W, n)) {
        case coberto:
            return W_bitmask;
            break;
        case conflito:
            return sem_solucao;
            break;
    }
    if( tam_W < profundidade)
        return 0;
    if (pega)
        W_bitmask = shift(W_bitmask, profundidade);
    int res1 = combine (bitmask, tam_W,  W_bitmask, ++profundidade, pega, n);
    int res2 = combine(bitmask, tam_W, W_bitmask,++profundidade , !pega, n);

    if (res1 != 0)
        return res1;
    return res2;
}
