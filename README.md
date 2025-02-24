# Algoritmos e Estruturas de Dados em C

Este repositório contém implementações de estruturas de dados fundamentais e algoritmos desenvolvidos durante o curso de Ciências da Computação no IFNMG, sob orientação do Prof. Alberto Miranda.

## Estruturas Implementadas

### Listas Encadeadas
- **Lab01**: Implementação de lista encadeada simples sem nó cabeça
  - Operações: inserção, remoção, busca, manipulação por posição
  
### Listas Circulares
- **Lab02**: Implementação de lista circular duplamente ligada com nó cabeça
  - Estrutura: grau e coeficiente para representação de dados
  - Operações: inserção, remoção, busca específica por grau

### Polinômios
- **Lab03**: TAD (Tipo Abstrato de Dados) para manipulação de polinômios
  - Operações: definição de coeficientes, soma, subtração
  - Implementação baseada em lista circular duplamente ligada

### Algoritmos de Backtracking
- **Lab04**: Problema de subconjuntos (Exact Cover)
  - Utilização de bitmasks para representação eficiente de conjuntos
  - Implementação com threads para solução paralela

### Problema da Mochila
- **Lab05**: Implementação do algoritmo para o problema da mochila (Knapsack Problem)
  - Abordagem recursiva com otimização
  - Uso de bitmasks para rastreamento de itens selecionados

### Tabelas Hash
- Implementações de diferentes estratégias de hash:
  - Hash com endereçamento interno
  - Hash com desvio sucessivo (tratamento de colisões)
  - Hash com vetor de listas (encadeamento separado)

## Conceitos Aplicados
- Alocação dinâmica de memória
- Ponteiros e estruturas de dados encadeadas
- Recursão e backtracking
- Manipulação de bits (bitmasks)
- Programação paralela (threads)
- Algoritmos de hashing
- Complexidade de tempo e espaço

## Habilidades Demonstradas
- Implementação de estruturas de dados eficientes
- Resolução de problemas algorítmicos clássicos
- Gerenciamento de memória em C
- Aplicação de conceitos teóricos em implementações práticas

## Como Compilar e Executar
Cada laboratório pode ser compilado individualmente:

```bash
gcc -o lab01 lab01.c
./lab01
```

## Tecnologias Utilizadas
- Linguagem C
- Bibliotecas padrão (stdio.h, stdlib.h, stdbool.h)
- Ponteiros e alocação dinâmica
- Threads (pthread.h)
