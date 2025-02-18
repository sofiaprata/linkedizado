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

// Inicializa centroides de forma distribuída ao longo do histograma
void inicializarCentroides(int *centroides, int k, int *histograma) {
    int valores[NIVEIS_CINZA], n = 0;

    // Coletando valores únicos presentes na imagem
    for (int i = 0; i < NIVEIS_CINZA; i++) {
        if (histograma[i] > 0) {
            valores[n++] = i;
        }
    }

    if (n < k) {
        fprintf(stderr, "Aviso: Menos tons distintos do que k. Ajustando...\n");
        for (int i = 0; i < k; i++) {
            centroides[i] = valores[i % n];
        }
        return;
    }

    // Distribuir centroides uniformemente
    for (int i = 0; i < k; i++) {
        centroides[i] = valores[(n * i) / k];
    }
}

void kmeans(PGM *pgm, int k, int *clusters) {
    int *centroides = (int *)malloc(k * sizeof(int));
    int *soma = (int *)malloc(k * sizeof(int));
    int *count = (int *)malloc(k * sizeof(int));

    if (!centroides || !soma || !count) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        return;
    }

    int histograma[NIVEIS_CINZA];
    calcularHistograma(pgm, histograma);
    inicializarCentroides(centroides, k, histograma);

    for (int iter = 0; iter < MAX_ITER; iter++) {
        memset(soma, 0, k * sizeof(int));
        memset(count, 0, k * sizeof(int));

        int centroides_antigos[k];
        memcpy(centroides_antigos, centroides, k * sizeof(int));

        // Atribui cada pixel ao cluster mais próximo
        for (int i = 0; i < pgm->largura * pgm->altura; i++) {
            int pixel = pgm->imagem[i];
            int cluster = 0;
            int min_dist = abs(pixel - centroides[0]);

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

        // Atualiza os centroides com média aritmética exata
        for (int c = 0; c < k; c++) {
            if (count[c] > 0) {
                centroides[c] = soma[c] / count[c];
            }
        }

        // Verifica se os centroides mudaram
        int convergiu = 1;
        for (int c = 0; c < k; c++) {
            if (centroides[c] != centroides_antigos[c]) {
                convergiu = 0;
                break;
            }
        }

        if (convergiu) break;
    }

    // Atualiza os pixels para os valores exatos dos centroides
    for (int i = 0; i < pgm->largura * pgm->altura; i++) {
        pgm->imagem[i] = centroides[clusters[i]];
    }

    free(centroides);
    free(soma);
    free(count);
}
