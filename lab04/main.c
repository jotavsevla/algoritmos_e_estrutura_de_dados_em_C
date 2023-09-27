#include "subconjunto.c"

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

    bool pega = true;
    int profundidade = 0;
    int op1, op2;

    op1 = combine (subconjuntos, m,  1, profundidade, pega, n);
    op2 = combine (subconjuntos, m,  0, profundidade, !pega, n);

    if (op1 == sem_solucao && op2 == sem_solucao)
        imprime_insoluvel();
    op1 != sem_solucao ? quais_cobriram(subconjuntos, op1, m, n) : quais_cobriram(subconjuntos, op2, m, n);

    return 0;
}