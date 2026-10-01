#include <stdio.h>
#include <omp.h>

int main() {

    printf("Inicio: executado por 1 thread\n");

    #pragma omp parallel num_threads(6)
    {
        int id = omp_get_thread_num();
        int total = omp_get_num_threads();

        printf("Ola! Sou a thread %d de um total de %d threads\n", id, total);

        #pragma omp single
        {
            printf("Total de threads: %d\n", total);
        }
    }

    printf("Fim: de volta a 1 thread\n");

    return 0;
}

/*
EXERCICIO 1 - RESPOSTAS

Nas primeiras execucoes, sem utilizar num_threads(6), o programa
utilizou 2 threads no ambiente do Codespaces.

A ordem das mensagens pode mudar entre as execucoes porque as threads
da regiao paralela executam de forma concorrente. O OpenMP nao garante
qual thread executara primeiro o printf. Por isso, a ordem de exibicao
das threads pode variar de uma execucao para outra.

Nas execucoes realizadas com 2 threads, a ordem observada foi:
Thread 0
Thread 1

Mesmo que a ordem tenha se repetido nos testes realizados, ela nao e
garantida e poderia mudar em outras execucoes.

Depois foi utilizada a clausula num_threads(6).

Saida observada:

Inicio: executado por 1 thread
Ola! Sou a thread 1 de um total de 6 threads
Total de threads: 6
Ola! Sou a thread 4 de um total de 6 threads
Ola! Sou a thread 3 de um total de 6 threads
Ola! Sou a thread 2 de um total de 6 threads
Ola! Sou a thread 0 de um total de 6 threads
Ola! Sou a thread 5 de um total de 6 threads
Fim: de volta a 1 thread

Nesse teste foi possivel observar claramente que as threads nao
executaram em ordem numerica.

A diretiva #pragma omp single fez com que apenas uma das threads
executasse o printf que mostra o total de threads.
*/