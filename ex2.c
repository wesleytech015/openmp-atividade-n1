#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define TAM 20
#define MIN 1
#define MAX 100

int main() {

    int A[TAM];
    int B[TAM];
    char Operacao[TAM];
    float Resultado[TAM];
    int Thread[TAM];

    char ops[] = {'+', '-', '*', '/'};

    srand(time(NULL));

    // Preenchimento sequencial dos vetores
    for (int i = 0; i < TAM; i++) {
        A[i] = MIN + rand() % (MAX - MIN + 1);
        B[i] = MIN + rand() % (MAX - MIN + 1);

        int op = rand() % 4;
        Operacao[i] = ops[op];
    }

    // Processamento paralelo com 4 threads
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < TAM; i++) {

        Thread[i] = omp_get_thread_num();

        switch (Operacao[i]) {

            case '+':
                Resultado[i] = A[i] + B[i];
                break;

            case '-':
                Resultado[i] = A[i] - B[i];
                break;

            case '*':
                Resultado[i] = A[i] * B[i];
                break;

            case '/':
                Resultado[i] = (float) A[i] / B[i];
                break;
        }
    }

    // Exibicao da tabela
    printf("\nIndice\tA\tOperacao\tB\tResultado\tThread\n");

    for (int i = 0; i < TAM; i++) {

        printf("%d\t%d\t%c\t\t%d\t%.2f\t\t%d\n",
               i,
               A[i],
               Operacao[i],
               B[i],
               Resultado[i],
               Thread[i]);
    }

    return 0;
}

/*
EXERCICIO 2 - RESPOSTAS

Os vetores A e B foram preenchidos sequencialmente com
20 valores aleatorios entre 1 e 100.

O vetor Operacao tambem foi preenchido sequencialmente,
sorteando uma das quatro operacoes:
+, -, * ou /.

Depois do preenchimento, foi utilizado:

#pragma omp parallel for num_threads(4)

para dividir as 20 iteracoes entre 4 threads.

Cada thread realiza a operacao correspondente ao indice
processado e seu numero e armazenado no vetor Thread.

Na execucao com distribuicao estatica observada, as
20 posicoes foram divididas da seguinte forma:

Thread 0: indices 0, 1, 2, 3 e 4
Thread 1: indices 5, 6, 7, 8 e 9
Thread 2: indices 10, 11, 12, 13 e 14
Thread 3: indices 15, 16, 17, 18 e 19

Cada thread processou 5 posicoes.

Nao foi necessario utilizar critical ou atomic na escrita
dos vetores Resultado e Thread porque cada iteracao do
parallel for trabalha com um indice diferente.

Assim, cada posicao dos vetores e escrita apenas pela
thread responsavel por aquela iteracao, evitando que duas
threads alterem a mesma posicao ao mesmo tempo.

Tabela de distribuicao:

Thread | Indices processados     | Quantidade
0      | 0, 1, 2, 3, 4          | 5
1      | 5, 6, 7, 8, 9          | 5
2      | 10, 11, 12, 13, 14     | 5
3      | 15, 16, 17, 18, 19     | 5
*/