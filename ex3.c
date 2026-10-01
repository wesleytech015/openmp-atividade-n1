#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <omp.h>

#define TAM 1000000
#define MIN 1
#define MAX 10000

int main() {

    int vetor[TAM];
    long long soma = 0;
    int maior = INT_MIN;
    int menor = INT_MAX;

    // Inicializa o gerador de numeros aleatorios
    srand(time(NULL));

    // Preenchimento sequencial do vetor
    for (int i = 0; i < TAM; i++) {
        vetor[i] = MIN + rand() % (MAX - MIN + 1);
    }

    // Calcula soma, maior e menor valor em um unico laco paralelo
    #pragma omp parallel for reduction(+:soma) reduction(max:maior) reduction(min:menor)
    for (int i = 0; i < TAM; i++) {

        soma += vetor[i];

        if (vetor[i] > maior) {
            maior = vetor[i];
        }

        if (vetor[i] < menor) {
            menor = vetor[i];
        }
    }

    printf("Somatorio: %lld\n", soma);
    printf("Maior valor: %d\n", maior);
    printf("Menor valor: %d\n", menor);

    return 0;
}

/*
EXERCICIO 3 - RESPOSTAS

Foi criado um vetor com 1.000.000 de posicoes e preenchido
com valores aleatorios entre 1 e 10.000.

Foi utilizado um unico laco com #pragma omp parallel for
para calcular ao mesmo tempo o somatorio, o maior valor
e o menor valor do vetor.

Foram utilizadas tres operacoes de reduction:

reduction(+:soma)
Utilizada para combinar as somas parciais realizadas pelas
threads e gerar o somatorio final.

reduction(max:maior)
Utilizada para encontrar o maior valor entre os valores
processados pelas threads.

reduction(min:menor)
Utilizada para encontrar o menor valor entre os valores
processados pelas threads.

A clausula reduction permite que cada thread trabalhe com
uma copia local das variaveis utilizadas na reducao. Ao final
do processamento, o OpenMP combina os resultados parciais
para obter os valores finais.

Dessa forma, evitamos que varias threads alterem diretamente
as mesmas variaveis ao mesmo tempo, evitando condicoes de
corrida durante os calculos.
*/