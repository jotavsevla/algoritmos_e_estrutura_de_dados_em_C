#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//Escreva um programa que leia uma única linha representando uma expressão aritmética.
// Esta expressão conterá somente os operadores +, -, *, /, % e sem parênteses em notação infixa.
// Todos os operandos desta linha serão números inteiros menores do que mil.
// Os operandos e operadores estarão separados por espaços.
// Após a leitura seu programa deve gerar uma árvore representando a expressão aritmética representada
// na linha, considerando a precedência de operadores: i) maior para * e / , ii) segunda maior
// para + e -, e iii) menor para %. Além disso, caso haja 2 operadores de mesma precedência em sequência,
// deve-se adotar associatividade à esquerda. Por exemplo, "10-5-7=(10-5)-7".
//Em seguida seu programa deve imprimir a expressão aritmética em notação prefixa em uma única linha,
// com espaço separando operandos e operadores. Em seguida, ele deve imprimi-la em notação pós-fixa em uma
// única linha, com espaço separando operandos e operadores. Finalmente, o valor calculado da expressão
// deve ser impresso na linha final da saída.
typedef struct dado{
    int operando;
    bool eh_operador;
    char operador;
}tipodado;

typedef struct no_aux {
    tipodado operandoOUoperador;
    struct no_aux* prox;
} no, *pilha;

void inicializa_pilha( pilha* ap_pilha);
void push(pilha* ap_pilha, tipodado valor);
void pop (pilha* ap_pilha);

int main() {
    tipodado* expressao = calloc (1000, sizeof(tipodado));
    int posicao_operando = 0, posicao_operador = 1;
    pilha* operadores;
    pilha*  sinais;
    inicializa_pilha(operadores);
    inicializa_pilha(sinais);
    while(2 == (scanf("%d %s", &expressao[posicao_operando].operando, &expressao[posicao_operador].operador))) {
        expressao[posicao_operador].eh_operador = true;
        posicao_operando += 2;
        posicao_operador += 2;
    }
    expressao[posicao_operador].operador = '\0';
    return 0;
}
void inicializa_pilha( pilha* ap_pilha){
    (*ap_pilha) = malloc(sizeof (pilha));
    (*ap_pilha)->prox = NULL;
}
void push (pilha* ap_pilha, tipodado valorOUsinal){
    no* novo_elemento = malloc (sizeof (no));
    novo_elemento->operandoOUoperador = valorOUsinal;

    if ((*ap_pilha)->prox == NULL)
        novo_elemento->prox = NULL;
    else
        novo_elemento->prox = *ap_pilha;

    *ap_pilha = novo_elemento;
}
tipodado pop (pilha* ap_pilha){
    // caso em que ja esteja vazio
    if((*ap_pilha)->prox == NULL) return;
    no* remover = (*ap_pilha)->prox;
    tipodado retorno = remover->operandoOUoperador;
    (*ap_pilha)->prox = remover->prox;
    free(remover);

}
