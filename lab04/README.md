# Algoritmo de Exact Cover - Lab04

## Descrição do Problema
Implementação de uma solução para o problema conhecido como "Exact Cover" (Cobertura Exata):

> Dado um conjunto S = {0, 1, 2, ..., n-1} e uma coleção W de subconjuntos de S, encontrar uma subcoleção W' de W (se existir) tal que cada elemento de S aparece em exatamente um dos conjuntos dentro de W'.

Este é um problema NP-completo clássico com aplicações em quebra-cabeças como Sudoku, pentominos e tabuleiros de xadrez.

## Abordagem de Solução
A solução implementada utiliza:
1. **Backtracking recursivo**: para explorar o espaço de soluções
2. **Bitmasks**: para representação eficiente dos conjuntos
3. **Paralelismo**: divisão do problema em threads para processamento concorrente

## Estruturas e Conceitos Importantes

### Representação com Bitmasks
- Cada elemento de S é representado por um bit em um inteiro
- Um subconjunto é representado como uma máscara onde os bits 1 indicam elementos presentes
- Operações bit a bit são utilizadas para verificar conflitos e cobertura

### Enumeração de Estados
```c
typedef enum {
    coberto = 1,       // Todos os elementos estão cobertos
    conflito = -1,     // Existe conflito (elemento coberto mais de uma vez)
    not_coberto = -2,  // Há elementos não cobertos
    sem_solucao = 0    // Não foi encontrada solução
} veracidade;
```

### Estrutura para Paralelismo
```c
typedef struct thread_parameters {
    int* bitmask, tam_W, W_bitmask, profundidade, tam_n;
    bool pega;
    veracidade resultado;
} Parametros;
```

## Algoritmo Principal
O algoritmo utiliza uma função recursiva `combine()` que:
1. Tenta incluir ou excluir cada subconjunto de W
2. Verifica a cada passo se há conflitos ou se todos os elementos foram cobertos
3. Divide a busca inicial em duas threads paralelas para melhor desempenho

A função `cobre()` é crucial pois verifica se um dado subconjunto de W é uma cobertura válida:
```c
veracidade cobre(int W_bitmask, int* subconjunto, int tam_W, int tam_subconjunto) {
    // Acumula todos os elementos cobertos
    int acumulador = 0;
    
    // Percorre cada subconjunto selecionado
    for (int i = 0; i < tam_W; ++i) {
        if((W_bitmask&(1<<i)) != 0) {
            // Verifica se há conflito (elemento coberto duas vezes)
            for(int j = 0; j < tam_subconjunto; ++j) {
                if(conflito_bit_x(acumulador, subconjunto[i], j))
                    return conflito;
            }
            acumulador |= subconjunto[i];
        }
    }
    
    // Verifica se todos os elementos foram cobertos
    for (int i = 0; i < tam_subconjunto; ++i) {
        if ((acumulador&(1<<i)) == 0)
            return not_coberto;
    }
    return coberto;
}
```

## Complexidade
- **Tempo**: O(2^m) no pior caso, onde m é o número de subconjuntos
- **Espaço**: O(m) para armazenar os subconjuntos e a pilha de recursão

## Otimizações Implementadas
1. **Poda imediata** quando um conflito é detectado
2. **Paralelismo** dividindo o espaço de busca
3. **Representação eficiente** com bitmasks em vez de arrays
4. **Detecção antecipada** de estados sem solução

## Exemplo de Entrada/Saída
**Entrada:**
```
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
```

**Saída:**
```
3
3  0 2 4
3  3 5 7
2  1 6
```

## Aplicações
Este algoritmo pode ser aplicado a problemas como:
- Quebra-cabeças lógicos (Sudoku, Nonograms)
- Problemas de escalonamento
- Problemas de coloração de grafos
- Otimização de recursos com restrições
