#include <stdio.h>
#include <omp.h>

#define N 20

int main() {

    int A[N], B[N];
    char Operacao[N];
    double Resultado[N];
    int Thread[N];

    for (int i = 0; i < N; i++) {
        A[i] = i + 1;
        B[i] = (i % 5) + 1;

        if (i % 4 == 0)
            Operacao[i] = '+';
        else if (i % 4 == 1)
            Operacao[i] = '-';
        else if (i % 4 == 2)
            Operacao[i] = '*';
        else
            Operacao[i] = '/';
    }

    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < N; i++) {

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
                Resultado[i] = (double) A[i] / B[i];
                break;
        }
    }

    printf("\nIndice\tA\tOperacao\tB\tResultado\tThread\n");

    for (int i = 0; i < N; i++) {
        printf("%d\t%d\t%c\t\t%d\t%.2f\t\t%d\n",
               i, A[i], Operacao[i], B[i],
               Resultado[i], Thread[i]);
    }

    return 0;
}

/*
EXERCICIO 2 - RESPOSTAS

O programa utilizou 4 threads para processar 20 indices.

Distribuicao observada:

Thread 0: indices 0, 1, 2, 3 e 4
Thread 1: indices 5, 6, 7, 8 e 9
Thread 2: indices 10, 11, 12, 13 e 14
Thread 3: indices 15, 16, 17, 18 e 19

Cada thread processou 5 indices.

O #pragma omp parallel for dividiu as iteracoes do laco entre
as 4 threads.

Nao foi necessario utilizar critical ou atomic para escrever nos
vetores Resultado e Thread porque cada iteracao do for trabalha
com um indice diferente. Assim, cada posicao do vetor e escrita
por apenas uma thread, evitando disputa pela mesma posicao.

Tabela observada:

Thread | Indices processados     | Quantidade
0      | 0, 1, 2, 3, 4          | 5
1      | 5, 6, 7, 8, 9          | 5
2      | 10, 11, 12, 13, 14     | 5
3      | 15, 16, 17, 18, 19     | 5
*/