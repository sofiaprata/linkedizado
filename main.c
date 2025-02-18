// *********************************************************
// * Aluno:  Sofia Freitas Batista Prata                   *
// * Matrícula: 20241045050448                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
// * Aluno: Pedro Felipe Monteiro Ventura                  *
// * Matrícula: 20241045050294                             *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
// * Aluno: Miguel Antonio Florencio Felix                 *
// * Matrícula: 2024104505 0480                                *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
 
#include <stdio.h>
#include <time.h>
#include "processamento.h"

int main() {
    clock_t begin = clock();

    // Caminho genérico, ajustado para ser mais portátil
    const char *inputPath = "dataset"; // Diretório relativo
    const char *outputPath = "teste"; // Diretório relativo de saída

    // Processar imagens
    processarImagens(inputPath, outputPath);

    // Calcular o tempo de execução
    clock_t end = clock();
    double tempo = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo total: %.2lf segundos\n", tempo);

    return 0;
}