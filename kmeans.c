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
// * Matrícula: 2024104505   0480                              *
// * Avaliação 04: Trabalho Final                          *
// * 04.505.23 - 2024.2 - Prof. Daniel Ferreira            *
// * Compilador: gcc (MinGW.org GCC-6.3.0-1) 6.3.0         *
// *********************************************************
#include <stdio.h>
#include "kmeans.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "imagem.h"

#define MAX_ITER 100
#define NIVEIS_CINZA 256

void calcularHistograma(PGM *pgm, int *histograma) {
    memset(histograma, 0, NIVEIS_CINZA * sizeof(int));

    for (int i = 0; i < pgm->largura * pgm->altura; i++) {
        histograma[pgm->imagem[i]]++;
    }
}

void escolherCentroides(int *centroides, int k, int *histograma) {
    int indicesEscolhidos = 0;
    for (int i = 0; i < NIVEIS_CINZA && indicesEscolhidos < k; i++) {
        if (histograma[i] > 0) {
            centroides[indicesEscolhidos++] = i;
        }
    }

    // Se não conseguiu preencher k centroides, preenche aleatoriamente
    srand(time(NULL));
    while (indicesEscolhidos < k) {
        centroides[indicesEscolhidos++] = rand() % NIVEIS_CINZA;
    }
}

void kmeans(PGM *pgm, int k, int *clusters) {
    int *centroides = (int *)malloc(k * sizeof(int));
    int *soma = (int *)malloc(k * sizeof(int));
    int *count = (int *)malloc(k * sizeof(int));

    if (centroides == NULL || soma == NULL || count == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    
    // Calcula histograma antes de iniciar o k-means
    int histograma[NIVEIS_CINZA];
    calcularHistograma(pgm, histograma);

    // Inicializa os centroides com os valores mais frequentes do histograma
    escolherCentroides(centroides, k, histograma);
    
    for (int iter = 0; iter < MAX_ITER; iter++) {
        memset(soma, 0, k * sizeof(int));
        memset(count, 0, k * sizeof(int));

        int *centroides_antigos = (int *)malloc(k * sizeof(int));
        if (centroides_antigos == NULL) {
            printf("Erro ao alocar memória para centroides antigos.\n");
            free(centroides);
            free(soma);
            free(count);
            return;
        }
        memcpy(centroides_antigos, centroides, k * sizeof(int));

        // Atribui os pixels a clusters
        for (int i = 0; i < pgm->largura * pgm->altura; i++) {
            int pixel = pgm->imagem[i];
            int cluster = 0, min_dist = abs(pixel - centroides[0]);

            for (int c = 1; c < k; c++) {
                int dist = abs(pixel - centroides[c]);
                if (dist < min_dist) {
                    min_dist = dist;
                    cluster = c;
                }
            }
            clusters[i] = cluster;
            soma[cluster] += pixel;
            count[cluster]++;
        }

        // Atualiza os centroides
        for (int c = 0; c < k; c++) {
            centroides[c] = count[c] ? soma[c] / count[c] : centroides[c];
        }

        // Verifica se os centroides mudaram
        int centroides_iguais = 1;
        for (int c = 0; c < k; c++) {
            if (centroides[c] != centroides_antigos[c]) {
                centroides_iguais = 0;
                break;
            }
        }

        if (centroides_iguais) {
            free(centroides_antigos);
            break;
        }

        free(centroides_antigos);
    }

    free(centroides);
    free(soma);
    free(count);
}