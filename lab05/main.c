#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//    Considere o problema de dados conjunto S com n objetos, com funções peso P:S->N e valor V:S->N, e um natural M,
//    encontrar um subconjunto X de S tal que a soma dos pesos dos elementos de X seja menor do que ou igual a M e cuja soma dos
//    valores dos elementos de X seja máxima. Dentre as múltiplas alternativas de máximos possíveis,
//    imprima aquela lexicograficamente menor, considerando lexicograficamente menor aqueles subconjuntos que
//    tenham elementos que aparecem antes na descrição de S.
//
//    A entrada será dada na entrada padrão. A primeira linha conterá dois naturais n e M (n <=20, M<=10^6).
//    As n linhas seguintes conterão 2 naturais cada, representando respectivamente o peso e o valor de um elemento de S.
//
//    A saída deve ser dada em duas linhas, descrevendo o conjunto X solução do problema.
//    A primeira linha conterá um natural representando a soma dos pesos de X, seguido de um natural descrevendo a soma dos valores de X.
//    A segunda linha começará com um inteiro k representando o tamanho de X, seguido de k naturais representando os índices,
//    começando em zero, em S dos elementos de X. Em caso de empate no valor de possíveis candidatos a X, o lexicograficamente menor deve
//    ser apresentando. Note que um conjunto X vazio é uma solução possível para o problema.
//
//    Exemplo de entrada:
//
//    n = 5 m = 100
//   0 30 1000
//   1 30 1100
//   1 30 1200
//   1 40 1500
//   0 40 1400
//
//    Exemplo de saída
//    100 3800
//    3 1 2 3

typedef struct {
    int peso;
    int valor;
}Objeto;
typedef struct mochila {
    Objeto soma_objetos;
    int mascara_obj;
}Mochila;


int entrada_quantidade_objetos ();

int entrada_capacidade_maxima ();

Objeto* entrada_conjunto_S (int quantidade_objetos);

Mochila mochila_mais_valiosa_aux (Mochila em_pauta, int n, Objeto* conjunto_S, bool pega);

Mochila mochila_mais_valiosa (Objeto* conjunto_S, int n, int capacidade_mochila);

void saida_mochila_preferida (Objeto* conjunto_S , Mochila preferida, int n, int capacidade_maxima);

int main() {
    int qnt_objetos = entrada_quantidade_objetos ();
    int capacidade_mochila = entrada_capacidade_maxima();
    Objeto* conjunto_S = entrada_conjunto_S (qnt_objetos);
    Mochila preferida = mochila_mais_valiosa(conjunto_S, qnt_objetos, capacidade_mochila);
    saida_mochila_preferida(conjunto_S, preferida, qnt_objetos, capacidade_mochila);
    return 0;
}

Mochila mochila_mais_valiosa (Objeto* conjunto_S, int n, int capacidade_mochila){
    Mochila candidata_1, candidata_2;
    candidata_1.mascara_obj = 0;
    candidata_2.mascara_obj = 0;
    candidata_1.soma_objetos.valor = 0;
    candidata_2.soma_objetos.valor = 0;
    candidata_1.soma_objetos.peso = capacidade_mochila;
    candidata_2.soma_objetos.peso = capacidade_mochila;
    candidata_1 = mochila_mais_valiosa_aux(candidata_1, n, conjunto_S, true);
    candidata_2 = mochila_mais_valiosa_aux(candidata_2, n, conjunto_S, false);

    return candidata_1.soma_objetos.valor > candidata_2.soma_objetos.valor ? candidata_1 : candidata_2;

}

Mochila mochila_mais_valiosa_aux (Mochila em_pauta, int n, Objeto* conjunto_S, bool pega){
    // caso base
    if (n == 0 || em_pauta.soma_objetos.peso == 0)
        return em_pauta;
    // esta condição serve para seleção dos casos que estão sendo considerados com o bool pega, onde
    // se ele estiver marcado como pega na instancia acima
    if (pega){
        if (em_pauta.soma_objetos.peso < conjunto_S[n-1].peso){
            em_pauta.soma_objetos.valor = -1; // maneira de retornar a descompensação daquele subconjunto de mochilas
            return em_pauta;
        }
        em_pauta.soma_objetos.peso -= conjunto_S[n-1].peso;
        em_pauta.soma_objetos.valor += conjunto_S[n-1].valor;
        em_pauta.mascara_obj |= (1<<(n-1));
    }
    Mochila resultado1 = mochila_mais_valiosa_aux(em_pauta, n - 1, conjunto_S, true);
    Mochila resultado2 = mochila_mais_valiosa_aux(em_pauta, n - 1, conjunto_S, false);
    return (resultado1.soma_objetos.valor > resultado2.soma_objetos.valor) ? resultado1 : resultado2;
}
// retorna o vetor do conjunto_S (objetos) definida por n
Objeto* entrada_conjunto_S (int n_quantidade_objetos){
    Objeto* conjunto_S = (Objeto*) calloc (sizeof (Objeto), n_quantidade_objetos);
    for (int i = 0; i < n_quantidade_objetos; ++i){
        scanf ("%d%d", &conjunto_S[i].peso, &conjunto_S[i].valor);
    }
    return conjunto_S;
}
int entrada_quantidade_objetos (){
    int n;
    scanf ("%d", &n);
    if (n < 0)
        return 0;
    return n;
}
int entrada_capacidade_maxima (){
    int mxN;
    scanf("%d", &mxN);
    return mxN;
}
void saida_mochila_preferida (Objeto* conjunto_S , Mochila preferida, int n, int capacidade_maxima){
    printf("%d %d\n", capacidade_maxima-preferida.soma_objetos.peso, preferida.soma_objetos.valor);

    int qnt_obj = 0;
    for (int i = 0; i < n; ++i)
        if ((preferida.mascara_obj&(1<<i)) != 0) ++qnt_obj;
    printf("%d", qnt_obj);

    for (int i = 0; i < n; ++i){
        if ((preferida.mascara_obj&(1<<i)) != 0)
            printf(" %d", i);
    }
    printf("\n");
}
