//
// Created by João on 27/09/23.
//

#include "subconjunto.c"

void print_result(veracidade resultado){
    if (resultado == conflito)
         printf("conflito\n");
     if (resultado == not_coberto)
         printf("not_coberto\n");
     if (resultado == coberto)
         printf("coberto\n");
     printf("----------------\n");
}
// necessário comentar/desativar a main do arquivo subconjunto.c para utilização deste caso de testes
int main(){
    // int W_bitmask, int* subconjunto, int tam_W, int tam_subconjunto
    int tam_W, tam_subconjunto = 9;
    int subconjunto[tam_subconjunto];

    // pos 0 a 2 = (int)5 -> 101
    subconjunto[0] = 11;
    subconjunto[1] = 0;
    subconjunto[2] = 14;
    // pos 3 a 5 = (int)56 -> 000111
    subconjunto[3] = 11;
    subconjunto[4] = 0;
    subconjunto[5] = 2;
    // pos 6 a 8 = (int)448 -> 000000111
    subconjunto[6] = 11;
    subconjunto[7] = 0;
    subconjunto[8] = 0;

    veracidade resultado;
    // Teste da função cobre:
    // Coberto:
    printf("Primeiro caso:\n");
    resultado = cobre(5, subconjunto, 9, 4);
    print_result(resultado);

    // Com conflito:
    printf("Segundo caso:\n");
    resultado = cobre(56, subconjunto, 9, 4);
    print_result(resultado);

    // Sem conflito, mas nao cobre:
    printf("Terceiro caso:\n");
    resultado = cobre(448, subconjunto, 9, 4);
    print_result(resultado);
    // Teste da função xyz:

}
