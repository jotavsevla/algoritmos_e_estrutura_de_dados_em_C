# TAD Polinômios - Lab03

## Descrição
Implementação de um Tipo Abstrato de Dados (TAD) para manipulação de polinômios com coeficientes inteiros. A representação utiliza uma lista circular duplamente ligada com nó cabeça, mantendo os coeficientes sempre ordenados por grau.

## Funcionalidades
- **Inicialização**: Criação de um polinômio vazio
- **Definição de Coeficientes**: Adição ou modificação de termos do polinômio
- **Operações Aritméticas**:
  - Soma de polinômios
  - Subtração de polinômios
- **Utilitários**:
  - Impressão formatada dos polinômios
  - Zeragem de polinômios (desalocação de memória)

## Estruturas de Dados
```c
typedef struct {
  int grau;
  int coef;
} TipoDado;

typedef struct No_aux {
  TipoDado valor;
  struct No_aux * antec;  
  struct No_aux * prox;
} No, *Lista;

typedef Lista Polinomio;
```

## Implementação das Operações Principais

### Definição de Coeficiente
```c
void define_coeficiente(Polinomio pol, int grau, int coef);
```
- Insere ou atualiza um termo do polinômio, mantendo a ordem por grau
- Complexidade: O(n) onde n é o número de termos no polinômio

### Soma de Polinômios
```c
void soma(Polinomio res, Polinomio a, Polinomio b);
```
- Realiza a adição entre dois polinômios, salvando o resultado em um terceiro
- Implementação eficiente que percorre os polinômios simultaneamente
- Complexidade: O(m + n) onde m e n são os números de termos nos polinômios

### Subtração de Polinômios
```c
void subtrai(Polinomio res, Polinomio a, Polinomio b);
```
- Similar à soma, mas subtraindo os termos correspondentes
- Trata casos especiais como termos que se anulam

## Exemplo de Uso
```c
Polinomio A, B, C;

inicializa_polinomio(&A);
inicializa_polinomio(&B);
inicializa_polinomio(&C);

// Definindo polinômio A = 2 + 3x^2
define_coeficiente(A, 0, 2);
define_coeficiente(A, 2, 3);

// Definindo polinômio B = -1 + x^1 + x^3
define_coeficiente(B, 0, -1);
define_coeficiente(B, 1, 1);
define_coeficiente(B, 3, 1);

// Calculando C = A + B
soma(C, A, B);
// C = 1 + x^1 + 3x^2 + x^3

// Imprimindo o resultado
imprime(C);
// [(0,1),(1,1),(2,3),(3,1)]

// Liberando memória
desaloca_polinomio(&A);
desaloca_polinomio(&B);
desaloca_polinomio(&C);
```

## Considerações
Esta implementação aplica conceitos fundamentais de:
- Listas duplamente encadeadas
- Ordenação implícita durante inserção
- Gerenciamento eficiente de memória
- Algoritmos para manipulação de polinômios
